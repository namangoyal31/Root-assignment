#include "TSystem.h"
#include "TFile.h"
#include "TTree.h"

#include <vector>
#include <iostream>

#include "MyGenParticle.h"
#include "MyElectron.h"
#include "MyMuon.h"

void fillParticleTree() {
    if (gSystem->Load("Question4/libMyParticles.so") < 0) {
        std::cerr << "Error: could not load libMyParticles.so" << std::endl;
        return;
    }

    TFile *fIn = TFile::Open("ntuple_array.root");

    if (!fIn || fIn->IsZombie()) {
        std::cerr << "Error: could not open ntuple_array.root" << std::endl;
        return;
    }

    TTree *tIn = nullptr;
    fIn->GetObject("ntupleProducer/tree", tIn);

    if (!tIn) {
        std::cerr << "Error: ntupleProducer/tree not found" << std::endl;
        fIn->Close();
        delete fIn;
        return;
    }

    Int_t nGenParticle;

    Float_t genParticlePx[100];
    Float_t genParticlePy[100];
    Float_t genParticlePz[100];
    Float_t genParticlePt[100];
    Float_t genParticleEta[100];
    Float_t genParticlePhi[100];

    Int_t genParticleCharge[100];
    Int_t genParticlePdgId[100];

    tIn->SetBranchAddress("nGenParticle", &nGenParticle);

    tIn->SetBranchAddress("genParticlePx", genParticlePx);
    tIn->SetBranchAddress("genParticlePy", genParticlePy);
    tIn->SetBranchAddress("genParticlePz", genParticlePz);
    tIn->SetBranchAddress("genParticlePt", genParticlePt);
    tIn->SetBranchAddress("genParticleEta", genParticleEta);
    tIn->SetBranchAddress("genParticlePhi", genParticlePhi);

    tIn->SetBranchAddress("genParticleCharge", genParticleCharge);
    tIn->SetBranchAddress("genParticlePdgId", genParticlePdgId);

    Int_t nElectron;

    Float_t electronPx[100];
    Float_t electronPy[100];
    Float_t electronPz[100];
    Float_t electronPt[100];
    Float_t electronEta[100];
    Float_t electronPhi[100];

    Float_t electronDxy[100];
    Float_t electronDz[100];

    Int_t electronCharge[100];

    tIn->SetBranchAddress("nElectron", &nElectron);

    tIn->SetBranchAddress("electronPx", electronPx);
    tIn->SetBranchAddress("electronPy", electronPy);
    tIn->SetBranchAddress("electronPz", electronPz);
    tIn->SetBranchAddress("electronPt", electronPt);
    tIn->SetBranchAddress("electronEta", electronEta);
    tIn->SetBranchAddress("electronPhi", electronPhi);

    tIn->SetBranchAddress("electronDxy", electronDxy);
    tIn->SetBranchAddress("electronDz", electronDz);

    tIn->SetBranchAddress("electronCharge", electronCharge);

    Int_t nMuon;

    Float_t muonPx[100];
    Float_t muonPy[100];
    Float_t muonPz[100];
    Float_t muonPt[100];
    Float_t muonEta[100];
    Float_t muonPhi[100];

    Float_t muonDz[100];
    Float_t muonDxy[100];

    Int_t muonCharge[100];

    tIn->SetBranchAddress("nMuon", &nMuon);

    tIn->SetBranchAddress("muonPx", muonPx);
    tIn->SetBranchAddress("muonPy", muonPy);
    tIn->SetBranchAddress("muonPz", muonPz);
    tIn->SetBranchAddress("muonPt", muonPt);
    tIn->SetBranchAddress("muonEta", muonEta);
    tIn->SetBranchAddress("muonPhi", muonPhi);

    tIn->SetBranchAddress("muonDz", muonDz);
    tIn->SetBranchAddress("muonDxy", muonDxy);

    tIn->SetBranchAddress("muonCharge", muonCharge);

    TFile *fOut = TFile::Open(
        "Question4/particleTree.root",
        "RECREATE"
    );

    if (!fOut || fOut->IsZombie()) {
        std::cerr << "Error: could not create Question4/particleTree.root"
                  << std::endl;
        fIn->Close();
        delete fIn;
        return;
    }

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

    T->Branch("genParticles", &genParticles);
    T->Branch("electrons", &electrons);
    T->Branch("muons", &muons);

    Long64_t nentries = tIn->GetEntries();

    std::cout << "No. of entries is: "
              << nentries << std::endl;

    for (Long64_t i = 0; i < nentries; i++) {

        tIn->GetEntry(i);

        genParticles->clear();
        electrons->clear();
        muons->clear();

        for (Int_t j = 0; j < nGenParticle; j++) {

            MyGenParticle particle(
                genParticlePx[j],
                genParticlePy[j],
                genParticlePz[j],
                genParticlePt[j],
                genParticleEta[j],
                genParticlePhi[j],
                genParticleCharge[j],
                genParticlePdgId[j]
            );

            genParticles->push_back(particle);
        }

        for (Int_t j = 0; j < nElectron; j++) {

            MyElectron electron(
                electronPx[j],
                electronPy[j],
                electronPz[j],
                electronPt[j],
                electronEta[j],
                electronPhi[j],
                electronDxy[j],
                electronDz[j],
                electronCharge[j]
            );

            electrons->push_back(electron);
        }

        for (Int_t j = 0; j < nMuon; j++) {

            MyMuon muon(
                muonPx[j],
                muonPy[j],
                muonPz[j],
                muonPt[j],
                muonEta[j],
                muonPhi[j],
                muonDz[j],
                muonDxy[j],
                muonCharge[j]
            );

            muons->push_back(muon);
        }

        T->Fill();
    }

    T->Write();

    fOut->Close();
    fIn->Close();

    delete fOut;
    delete fIn;

    delete genParticles;
    delete electrons;
    delete muons;

    std::cout << "New tree written to Question4/particleTree.root"
              << std::endl;
}