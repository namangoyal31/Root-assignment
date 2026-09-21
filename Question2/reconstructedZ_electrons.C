// Generated Z -> e+e- invariant mass
#include "TLorentzVector.h"
#include <cmath>

void reconstructedZ_electrons() {

  TH1F *h_mass = new TH1F("h_mass", "Generated Z mass;M_{ee} [GeV];Events", 100, 40., 140.);

  TFile *f = new TFile("../ntuple_array.root");
  TTree *t1 = (TTree*)f->Get("ntupleProducer/tree");

  Int_t nElectron, electronCharge[100];
  Float_t electronPx[100], electronPy[100], electronPz[100];

  t1->SetBranchAddress("nElectron", &nElectron);
  t1->SetBranchAddress("electronPx", electronPx);
  t1->SetBranchAddress("electronPy", electronPy);
  t1->SetBranchAddress("electronPz", electronPz);
  t1->SetBranchAddress("electronCharge", electronCharge);

  Int_t nentries = (Int_t)t1->GetEntries();
  cout << "No. of entries is: " << nentries << endl;

  for (Int_t i = 0; i < nentries; i++) {

    t1->GetEntry(i);

    Int_t iElectron1 = -1;
    Int_t iElectron2 = -1;

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

    if (iElectron1 != -1 && iElectron2 != -1) {

      Float_t electronE1 =
          sqrt(electronPx[iElectron1] * electronPx[iElectron1] +
               electronPy[iElectron1] * electronPy[iElectron1] +
               electronPz[iElectron1] * electronPz[iElectron1]);

      Float_t electronE2 =
          sqrt(electronPx[iElectron2] * electronPx[iElectron2] +
               electronPy[iElectron2] * electronPy[iElectron2] +
               electronPz[iElectron2] * electronPz[iElectron2]);

      TLorentzVector e1(
          electronPx[iElectron1],
          electronPy[iElectron1],
          electronPz[iElectron1],
          electronE1
      );

      TLorentzVector e2(
          electronPx[iElectron2],
          electronPy[iElectron2],
          electronPz[iElectron2],
          electronE2
      );

      TLorentzVector dielectron = e1 + e2;

      h_mass->Fill(dielectron.M());
    }
  }

  TCanvas *c1 = new TCanvas();
  h_mass->Draw();
  c1->SaveAs("reconstructedZ_electrons_mass.png");

  f->Close();
}