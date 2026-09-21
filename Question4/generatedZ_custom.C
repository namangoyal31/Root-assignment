#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLorentzVector.h"
#include "TSystem.h"

#include <vector>
#include <iostream>
#include <cmath>

#include "MyGenParticle.h"
#include "MyElectron.h"
#include "MyMuon.h"

void generatedZ_custom() {

    // Load dictionary for custom particle classes
    if (gSystem->Load("Question4/libMyParticles.so") < 0) {
        std::cout << "Error loading libMyParticles.so" << std::endl;
        return;
    }

    // Open the new tree
    TFile *f = TFile::Open("Question4/particleTree.root");

    if (!f || f->IsZombie()) {
        std::cout << "Error opening particleTree.root" << std::endl;
        return;
    }

    TTree *T = (TTree*)f->Get("T");

    if (!T) {
        std::cout << "Error: tree T not found" << std::endl;
        f->Close();
        return;
    }

    // Vector stored in the tree
    std::vector<MyGenParticle> *genParticles = nullptr;

    T->SetBranchAddress("genParticles", &genParticles);

    // Z mass histogram
    TH1F *h_mass = new TH1F(
        "h_mass",
        "Generated Z boson mass;M_{Z} [GeV];Events",
        100,
        40.,
        140.
    );

    Long64_t nentries = T->GetEntries();

    std::cout << "No. of entries is: "
              << nentries << std::endl;

    for (Long64_t i = 0; i < nentries; i++) {

        T->GetEntry(i);

        bool foundPair = false;

        // Look for an opposite-charge electron pair
        for (size_t j = 0; j < genParticles->size(); j++) {

            // Only electrons / positrons
            if (std::abs(genParticles->at(j).pdgId) != 11)
                continue;

            for (size_t k = j + 1; k < genParticles->size(); k++) {

                // Only electrons / positrons
                if (std::abs(genParticles->at(k).pdgId) != 11)
                    continue;

                // Must have opposite charge
                if (genParticles->at(j).charge *
                    genParticles->at(k).charge != -1)
                    continue;

                // Four-momentum of particle 1
                Float_t px1 = genParticles->at(j).px;
                Float_t py1 = genParticles->at(j).py;
                Float_t pz1 = genParticles->at(j).pz;

                Float_t E1 = std::sqrt(
                    px1 * px1 +
                    py1 * py1 +
                    pz1 * pz1
                );

                TLorentzVector p1(px1, py1, pz1, E1);

                // Four-momentum of particle 2
                Float_t px2 = genParticles->at(k).px;
                Float_t py2 = genParticles->at(k).py;
                Float_t pz2 = genParticles->at(k).pz;

                Float_t E2 = std::sqrt(
                    px2 * px2 +
                    py2 * py2 +
                    pz2 * pz2
                );

                TLorentzVector p2(px2, py2, pz2, E2);

                // Z boson four-momentum
                TLorentzVector Z = p1 + p2;

                // Fill invariant mass
                h_mass->Fill(Z.M());

                // Only one pair per event
                foundPair = true;
                break;
            }

            if (foundPair)
                break;
        }
    }

    // Draw histogram
    TCanvas *c1 = new TCanvas(
        "c1",
        "Generated Z Mass",
        800,
        600
    );

    h_mass->Draw();

    c1->SaveAs("Question4/generatedZ_custom_mass.png");

    f->Close();
}