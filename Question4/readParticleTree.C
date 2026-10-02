#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"

#include <iostream>
#include <vector>

#include "MyGenParticle.h"
#include "MyElectron.h"
#include "MyMuon.h"

void readParticleTree() {

    if (gSystem->Load("Question4/libMyParticles.so") < 0) {
        std::cerr << "Error: could not load libMyParticles.so"
                  << std::endl;
        return;
    }

    TFile *f = TFile::Open("Question4/particleTree.root");

    if (!f || f->IsZombie()) {
        std::cerr << "Error opening Question4/particleTree.root"
                  << std::endl;
        return;
    }

    TTree *T = nullptr;
    f->GetObject("T", T);

    if (!T) {
        std::cerr << "Error: tree T not found" << std::endl;
        f->Close();
        delete f;
        return;
    }

    std::vector<MyGenParticle> *genParticles = nullptr;
    std::vector<MyElectron> *electrons = nullptr;
    std::vector<MyMuon> *muons = nullptr;

    T->SetBranchAddress("genParticles", &genParticles);
    T->SetBranchAddress("electrons", &electrons);
    T->SetBranchAddress("muons", &muons);

    Long64_t nentries = T->GetEntries();

    std::cout << "No. of entries is: "
              << nentries << std::endl;

    if (nentries == 0) {
        std::cerr << "Error: tree contains no entries" << std::endl;
        f->Close();
        delete f;
        return;
    }

    T->GetEntry(0);

    std::cout << "Event 0:" << std::endl;
    std::cout << "  Generated particles = "
              << genParticles->size() << std::endl;
    std::cout << "  Electrons = "
              << electrons->size() << std::endl;
    std::cout << "  Muons = "
              << muons->size() << std::endl;

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