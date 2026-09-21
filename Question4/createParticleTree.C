#include "TFile.h"
#include "TTree.h"
#include "vector"

#include "MyGenParticle.h"
#include "MyElectron.h"
#include "MyMuon.h"

void createParticleTree() {

    TFile *f = new TFile("particleTree.root", "RECREATE");

    TTree *T = new TTree(
        "T",
        "Tree containing custom particle classes"
    );

    std::vector<MyGenParticle> *genParticles =
        new std::vector<MyGenParticle>();

    std::vector<MyElectron> *electrons =
        new std::vector<MyElectron>();

    std::vector<MyMuon> *muons =
        new std::vector<MyMuon>();

    // Create branches
    T->Branch("genParticles", &genParticles);
    T->Branch("electrons", &electrons);
    T->Branch("muons", &muons);

    // For Q4(b), we are only creating the tree structure.
    // Q4(c) will fill these vectors with events.

    T->Write();

    f->Close();

    delete genParticles;
    delete electrons;
    delete muons;
}