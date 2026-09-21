// Truth-matched reconstructed Z -> e+e- invariant mass
#include "TLorentzVector.h"
#include <cmath>

void truthMatchedZ_electrons() {

  // Truth-matching requirement
  const Float_t deltaRMax = 0.01;

  TH1F *h_mass = new TH1F(
      "h_mass",
      "Truth-matched reconstructed Z mass;M_{ee} [GeV];Events",
      100, 40., 140.
  );

  TH1F *h_deltaR = new TH1F(
      "h_deltaR",
      "Reco-gen #DeltaR;#DeltaR;Matched reconstructed electrons",
      100, 0., deltaRMax
  );

  TFile *f = new TFile("../ntuple_array.root");
  TTree *t1 = (TTree*)f->Get("ntupleProducer/tree");

  
  // Reconstructed electrons
  

  Int_t nElectron;

  Float_t electronPx[100];
  Float_t electronPy[100];
  Float_t electronPz[100];
  Float_t electronEta[100];
  Float_t electronPhi[100];

  Int_t electronCharge[100];

  t1->SetBranchAddress("nElectron", &nElectron);
  t1->SetBranchAddress("electronPx", electronPx);
  t1->SetBranchAddress("electronPy", electronPy);
  t1->SetBranchAddress("electronPz", electronPz);
  t1->SetBranchAddress("electronEta", electronEta);
  t1->SetBranchAddress("electronPhi", electronPhi);
  t1->SetBranchAddress("electronCharge", electronCharge);

  
  // Generated particles
  

  Int_t nGenParticle;

  Float_t genParticleEta[100];
  Float_t genParticlePhi[100];

  Int_t genParticlePdgId[100];

  t1->SetBranchAddress("nGenParticle", &nGenParticle);
  t1->SetBranchAddress("genParticleEta", genParticleEta);
  t1->SetBranchAddress("genParticlePhi", genParticlePhi);
  t1->SetBranchAddress("genParticlePdgId", genParticlePdgId);

  Int_t nentries = (Int_t)t1->GetEntries();

  cout << "No. of entries is: " << nentries << endl;

  Int_t totalMatches = 0;
  Int_t acceptedMatches = 0;

  
  // Loop over events
  

  for (Int_t i = 0; i < nentries; i++) {

    t1->GetEntry(i);

    // matchedGenIndex[j] = generated particle matched
    // to reconstructed electron j
    Int_t matchedGenIndex[100];

    for (Int_t j = 0; j < nElectron; j++) {
      matchedGenIndex[j] = -1;
    }

    // Keep track of generated electrons already used
    Bool_t genUsed[100];

    for (Int_t j = 0; j < nGenParticle; j++) {
      genUsed[j] = false;
    }

    // ----------------------------------------------------------
    // Truth matching using Delta R
    // ----------------------------------------------------------

    for (Int_t j = 0; j < nElectron; j++) {

      Float_t minDeltaR = 1e9;
      Int_t bestGenIndex = -1;

      // Search over generated particles
      for (Int_t k = 0; k < nGenParticle; k++) {

        // Only generated electrons/positrons
        if (std::abs(genParticlePdgId[k]) != 11)
          continue;

        // Don't use the same generated particle twice
        if (genUsed[k])
          continue;

        Float_t dEta =
            electronEta[j] - genParticleEta[k];

        Float_t dPhi =
            electronPhi[j] - genParticlePhi[k];

        // Put Delta Phi in [-pi, pi]
        if (dPhi > TMath::Pi())
          dPhi -= 2.0 * TMath::Pi();

        if (dPhi < -TMath::Pi())
          dPhi += 2.0 * TMath::Pi();

        Float_t deltaR =
            sqrt(dEta * dEta + dPhi * dPhi);

        // Find the closest generated electron
        if (deltaR < minDeltaR) {
          minDeltaR = deltaR;
          bestGenIndex = k;
        }
      }

      // --------------------------------------------------------
      // Apply Delta R threshold
      // --------------------------------------------------------

      if (bestGenIndex != -1) {

        totalMatches++;

        if (minDeltaR < deltaRMax) {

          matchedGenIndex[j] = bestGenIndex;
          genUsed[bestGenIndex] = true;

          h_deltaR->Fill(minDeltaR);

          acceptedMatches++;
        }
      }
    }

    // ----------------------------------------------------------
    // Find two truth-matched reconstructed electrons
    // with opposite charge
    // ----------------------------------------------------------

    Int_t iElectron1 = -1;
    Int_t iElectron2 = -1;

    for (Int_t j = 0; j < nElectron; j++) {

      // Electron must have passed truth matching
      if (matchedGenIndex[j] == -1)
        continue;

      for (Int_t k = j + 1; k < nElectron; k++) {

        // Electron must have passed truth matching
        if (matchedGenIndex[k] == -1)
          continue;

        // Require opposite reconstructed charge
        if (electronCharge[j] * electronCharge[k] != -1)
          continue;

        iElectron1 = j;
        iElectron2 = k;

        break;
      }

      if (iElectron1 != -1)
        break;
    }

    // ----------------------------------------------------------
    // Construct reconstructed four-vectors
    // and calculate invariant mass
    // ----------------------------------------------------------

    if (iElectron1 != -1 && iElectron2 != -1) {

      Float_t electronE1 =
          sqrt(
              electronPx[iElectron1] * electronPx[iElectron1] +
              electronPy[iElectron1] * electronPy[iElectron1] +
              electronPz[iElectron1] * electronPz[iElectron1]
          );

      Float_t electronE2 =
          sqrt(
              electronPx[iElectron2] * electronPx[iElectron2] +
              electronPy[iElectron2] * electronPy[iElectron2] +
              electronPz[iElectron2] * electronPz[iElectron2]
          );

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

  
  // Print matching information
  

  cout << "Total nearest matches = "
       << totalMatches << endl;

  cout << "Accepted matches (Delta R < "
       << deltaRMax << ") = "
       << acceptedMatches << endl;

  if (totalMatches > 0) {
    cout << "Matching efficiency = "
         << 100.0 * acceptedMatches / totalMatches
         << " %" << endl;
  }

  
  // Draw reconstructed Z mass
  

  TCanvas *c1 = new TCanvas();

  h_mass->Draw();

  c1->SaveAs("truthMatchedZ_electrons_mass.png");

  
  // Draw Delta R diagnostic
  

  TCanvas *c2 = new TCanvas();

  h_deltaR->Draw();

  c2->SaveAs("truthMatchedZ_electrons_deltaR.png");

  f->Close();
}