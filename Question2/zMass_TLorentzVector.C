// Generated and reconstructed Z mass using TLorentzVector

#include "TLorentzVector.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include <cmath>

void zMass_TLorentzVector() {

  TH1F *h_genMass = new TH1F(
      "h_genMass",
      "Generated Z mass using TLorentzVector;M_{ee} [GeV];Events",
      100, 40., 140.
  );

  TH1F *h_recoMass = new TH1F(
      "h_recoMass",
      "Reconstructed Z mass using TLorentzVector;M_{ee} [GeV];Events",
      100, 40., 140.
  );

  TFile *f = new TFile("../ntuple_array.root");
  TTree *t1 = (TTree*)f->Get("ntupleProducer/tree");


  // Generated particles


  Int_t nGenParticle;

  Float_t genParticlePx[100];
  Float_t genParticlePy[100];
  Float_t genParticlePz[100];

  Int_t genParticleCharge[100];
  Int_t genParticlePdgId[100];

  t1->SetBranchAddress("nGenParticle", &nGenParticle);
  t1->SetBranchAddress("genParticlePx", genParticlePx);
  t1->SetBranchAddress("genParticlePy", genParticlePy);
  t1->SetBranchAddress("genParticlePz", genParticlePz);
  t1->SetBranchAddress("genParticleCharge", genParticleCharge);
  t1->SetBranchAddress("genParticlePdgId", genParticlePdgId);


  // Reconstructed electrons


  Int_t nElectron;

  Float_t electronPx[100];
  Float_t electronPy[100];
  Float_t electronPz[100];

  Int_t electronCharge[100];

  t1->SetBranchAddress("nElectron", &nElectron);
  t1->SetBranchAddress("electronPx", electronPx);
  t1->SetBranchAddress("electronPy", electronPy);
  t1->SetBranchAddress("electronPz", electronPz);
  t1->SetBranchAddress("electronCharge", electronCharge);

  Int_t nentries = (Int_t)t1->GetEntries();

  cout << "No. of entries is: " << nentries << endl;


  // Event loop


  for (Int_t i = 0; i < nentries; i++) {

    t1->GetEntry(i);

    // ============================================================
    // GENERATED Z
    // ============================================================

    Int_t iGenElectron1 = -1;
    Int_t iGenElectron2 = -1;

    // Find two generated electrons/positrons
    // with opposite charge
    for (Int_t j = 0; j < nGenParticle; j++) {

      // PDG ID: electron = 11, positron = -11
      if (std::abs(genParticlePdgId[j]) != 11)
        continue;

      for (Int_t k = j + 1; k < nGenParticle; k++) {

        if (std::abs(genParticlePdgId[k]) != 11)
          continue;

        if (genParticleCharge[j] * genParticleCharge[k] != -1)
          continue;

        iGenElectron1 = j;
        iGenElectron2 = k;

        break;
      }

      if (iGenElectron1 != -1)
        break;
    }

    // Construct generated four-vectors
    if (iGenElectron1 != -1 && iGenElectron2 != -1) {

      Float_t genElectronE1 =
          sqrt(
              genParticlePx[iGenElectron1] *
              genParticlePx[iGenElectron1] +

              genParticlePy[iGenElectron1] *
              genParticlePy[iGenElectron1] +

              genParticlePz[iGenElectron1] *
              genParticlePz[iGenElectron1]
          );

      Float_t genElectronE2 =
          sqrt(
              genParticlePx[iGenElectron2] *
              genParticlePx[iGenElectron2] +

              genParticlePy[iGenElectron2] *
              genParticlePy[iGenElectron2] +

              genParticlePz[iGenElectron2] *
              genParticlePz[iGenElectron2]
          );

      TLorentzVector genElectron1(
          genParticlePx[iGenElectron1],
          genParticlePy[iGenElectron1],
          genParticlePz[iGenElectron1],
          genElectronE1
      );

      TLorentzVector genElectron2(
          genParticlePx[iGenElectron2],
          genParticlePy[iGenElectron2],
          genParticlePz[iGenElectron2],
          genElectronE2
      );

      // Generated Z boson
      TLorentzVector genZ = genElectron1 + genElectron2;

      h_genMass->Fill(genZ.M());
    }

    // ============================================================
    // RECONSTRUCTED Z
    // ============================================================

    Int_t iElectron1 = -1;
    Int_t iElectron2 = -1;

    // Find two reconstructed electrons
    // with opposite charge
    for (Int_t j = 0; j < nElectron; j++) {

      for (Int_t k = j + 1; k < nElectron; k++) {

        if (electronCharge[j] * electronCharge[k] != -1)
          continue;

        iElectron1 = j;
        iElectron2 = k;

        break;
      }

      if (iElectron1 != -1)
        break;
    }

    // Construct reconstructed four-vectors
    if (iElectron1 != -1 && iElectron2 != -1) {

      Float_t electronE1 =
          sqrt(
              electronPx[iElectron1] *
              electronPx[iElectron1] +

              electronPy[iElectron1] *
              electronPy[iElectron1] +

              electronPz[iElectron1] *
              electronPz[iElectron1]
          );

      Float_t electronE2 =
          sqrt(
              electronPx[iElectron2] *
              electronPx[iElectron2] +

              electronPy[iElectron2] *
              electronPy[iElectron2] +

              electronPz[iElectron2] *
              electronPz[iElectron2]
          );

      TLorentzVector electron1(
          electronPx[iElectron1],
          electronPy[iElectron1],
          electronPz[iElectron1],
          electronE1
      );

      TLorentzVector electron2(
          electronPx[iElectron2],
          electronPy[iElectron2],
          electronPz[iElectron2],
          electronE2
      );

      // Reconstructed Z boson
      TLorentzVector recoZ = electron1 + electron2;

      h_recoMass->Fill(recoZ.M());
    }
  }


  // Draw generated Z mass


  TCanvas *c1 = new TCanvas();

  h_genMass->Draw();

  c1->SaveAs("zMass_generated_TLorentzVector.png");


  // Draw reconstructed Z mass


  TCanvas *c2 = new TCanvas();

  h_recoMass->Draw();

  c2->SaveAs("zMass_reconstructed_TLorentzVector.png");

  f->Close();
}