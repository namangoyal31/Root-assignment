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

void reconstructedZ_custom() {

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
    std::vector<MyElectron> *electrons = nullptr;

    T->SetBranchAddress("electrons", &electrons);

    // Z mass histogram
    TH1F *h_mass = new TH1F(
        "h_mass",
        "Reconstructed Z boson mass;M_{Z} [GeV];Events",
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
        for (size_t j = 0; j < electrons->size(); j++) {

            for (size_t k = j + 1; k < electrons->size(); k++) {

                // Must have opposite charge
                if (electrons->at(j).charge *
                    electrons->at(k).charge != -1)
                    continue;

                // Four-momentum of electron 1
                Float_t px1 = electrons->at(j).px;
                Float_t py1 = electrons->at(j).py;
                Float_t pz1 = electrons->at(j).pz;

                Float_t E1 = std::sqrt(
                    px1 * px1 +
                    py1 * py1 +
                    pz1 * pz1
                );

                TLorentzVector p1(px1, py1, pz1, E1);

                // Four-momentum of electron 2
                Float_t px2 = electrons->at(k).px;
                Float_t py2 = electrons->at(k).py;
                Float_t pz2 = electrons->at(k).pz;

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
        "Reconstructed Z Mass",
        800,
        600
    );

    h_mass->Draw();

    c1->SaveAs("Question4/reconstructedZ_custom_mass.png");

    f->Close();
}