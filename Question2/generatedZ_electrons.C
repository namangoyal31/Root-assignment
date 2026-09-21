// Generated Z -> e+e- invariant mass
#include "TLorentzVector.h"
#include <cmath>

void generatedZ_electrons() {

  TH1F *h_mass = new TH1F("h_mass", "Generated Z mass;M_{ee} [GeV];Events", 100, 40., 140.);

  TFile *f = new TFile("../ntuple_array.root");
  TTree *t1 = (TTree*)f->Get("ntupleProducer/tree");

  Int_t nGenParticle, genParticleCharge[100], genParticlePdgId[100];
  Float_t genParticlePx[100], genParticlePy[100], genParticlePz[100];

  t1->SetBranchAddress("nGenParticle", &nGenParticle);
  t1->SetBranchAddress("genParticlePx", genParticlePx);
  t1->SetBranchAddress("genParticlePy", genParticlePy);
  t1->SetBranchAddress("genParticlePz", genParticlePz);
  t1->SetBranchAddress("genParticleCharge", genParticleCharge);
  t1->SetBranchAddress("genParticlePdgId", genParticlePdgId);

  Int_t nentries = (Int_t)t1->GetEntries();
  cout << "No. of entries is: " << nentries << endl;

  for (Int_t i = 0; i < nentries; i++) {

    t1->GetEntry(i);

    Int_t iElectron1 = -1;
    Int_t iElectron2 = -1;

    for (Int_t j = 0; j < nGenParticle; j++) {

      if (std::abs(genParticlePdgId[j]) != 11)
        continue;

      for (Int_t k = j + 1; k < nGenParticle; k++) {

        if (std::abs(genParticlePdgId[k]) != 11)
          continue;

        if (genParticleCharge[j] * genParticleCharge[k] != -1)
          continue;
        iElectron1 = j;
        iElectron2 = k;
        break;
      }

      if (iElectron1 != -1)
        break;
    }

    if (iElectron1 != -1 && iElectron2 != -1) {

      Float_t electronE1 =
          sqrt(genParticlePx[iElectron1] * genParticlePx[iElectron1] +
               genParticlePy[iElectron1] * genParticlePy[iElectron1] +
               genParticlePz[iElectron1] * genParticlePz[iElectron1]);

      Float_t electronE2 =
          sqrt(genParticlePx[iElectron2] * genParticlePx[iElectron2] +
               genParticlePy[iElectron2] * genParticlePy[iElectron2] +
               genParticlePz[iElectron2] * genParticlePz[iElectron2]);

      TLorentzVector e1(
          genParticlePx[iElectron1],
          genParticlePy[iElectron1],
          genParticlePz[iElectron1],
          electronE1
      );

      TLorentzVector e2(
          genParticlePx[iElectron2],
          genParticlePy[iElectron2],
          genParticlePz[iElectron2],
          electronE2
      );

      TLorentzVector dielectron = e1 + e2;

      h_mass->Fill(dielectron.M());
    }
  }

  TCanvas *c1 = new TCanvas();
  h_mass->Draw();
  c1->SaveAs("generatedZ_electrons_mass.png");

  f->Close();
}