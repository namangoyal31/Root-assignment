#include "TFile.h"
#include "TTree.h"

#include <iostream>
#include <vector>

#include "MyGenParticle.h"
#include "MyElectron.h"
#include "MyMuon.h"

void readParticleTree() {

    // Open the new file
    TFile *f = TFile::Open("particleTree.root");

    if (!f || f->IsZombie()) {
        std::cout << "Error opening particleTree.root" << std::endl;
        return;
    }

    // Get the tree
    TTree *T = (TTree*)f->Get("T");

    if (!T) {
        std::cout << "Error: tree T not found" << std::endl;
        return;
    }

    // Pointers to the vectors stored in the tree
    std::vector<MyGenParticle> *genParticles = nullptr;
    std::vector<MyElectron> *electrons = nullptr;
    std::vector<MyMuon> *muons = nullptr;

    // Connect tree branches to our vectors
    T->SetBranchAddress("genParticles", &genParticles);
    T->SetBranchAddress("electrons", &electrons);
    T->SetBranchAddress("muons", &muons);

    Long64_t nentries = T->GetEntries();

    std::cout << "No. of entries is: " << nentries << std::endl;

    // Read the first event as a test
    T->GetEntry(0);

    std::cout << "Event 0:" << std::endl;
    std::cout << "  Generated particles = "
              << genParticles->size() << std::endl;
    std::cout << "  Electrons = "
              << electrons->size() << std::endl;
    std::cout << "  Muons = "
              << muons->size() << std::endl;

    // Print one generated particle if present
    if (!genParticles->empty()) {
        const MyGenParticle &p = genParticles->at(0);

        std::cout << "\nFirst generated particle:" << std::endl;
        std::cout << "  px = " << p.px << std::endl;
        std::cout << "  py = " << p.py << std::endl;
        std::cout << "  pz = " << p.pz << std::endl;
        std::cout << "  charge = " << p.charge << std::endl;
        std::cout << "  pdgId = " << p.pdgId << std::endl;
    }

    f->Close();
    delete f;
}