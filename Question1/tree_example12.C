//Example using TLorentzVector
#include "TLorentzVector.h"
#include <vector>

void tree_example12() {

  TH2F *h_etaVsPhi = new TH2F("h_etaVsPhi", "eta vs phi", 100, -2.5, 2.5, 100, -3.14, 3.14);
  TH1F *h_mass = new TH1F("h_mass", "mass", 100, 40., 140.);

  TFile *f = new TFile("ntuple_array.root");
  TTree *t1 = (TTree*)f->Get("ntupleProducer/tree");

  Int_t nElectron;
  Float_t electronPx[3], electronPy[3], electronPz[3];
  t1->SetBranchAddress("nElectron",&nElectron);  
  t1->SetBranchAddress("electronPx",&electronPx);
  t1->SetBranchAddress("electronPy",&electronPy);
  t1->SetBranchAddress("electronPz",&electronPz);

  Int_t nentries = (Int_t)t1->GetEntries(); 
  cout << "No. of entries is: " << nentries << endl;

  for (Int_t i = 0; i<nentries; i++) {
  //for (Int_t i = 0; i<1000; i++) {
    t1->GetEntry(i);

    std::vector<TLorentzVector> *electrons = new std::vector<TLorentzVector>();
    electrons->clear();

    //Compute electron eta, phi and fill them. 
    if(nElectron>0){

      //cout << "No. of electrons is: " << nElectron << endl;
      
      for(Int_t j = 0; j < nElectron; j++){
	float electronE = sqrt(electronPx[j]*electronPx[j] + electronPy[j]*electronPy[j] + electronPz[j]*electronPz[j]);
	TLorentzVector e(electronPx[j], electronPy[j], electronPz[j], electronE);

	//apply pT cut
	//if(e.Pt() < 20) continue;

	h_etaVsPhi->Fill(e.Eta(), e.Phi());

	electrons->push_back(e);
      }
    }
    //Fill mass if there are two electrons
    if(electrons->size() >= 2){
      TLorentzVector dielectron = (*electrons)[0]+(*electrons)[1];
      h_mass->Fill(dielectron.M());
    }

    delete electrons;
  }
  
  TCanvas *c1 = new TCanvas();
  h_etaVsPhi->Draw("colz");
  c1->SaveAs("tree_example12_etaVsphi_electrons.png");
  
  c1->Update();
  h_mass->Draw();
  c1->SaveAs("tree_example12_dielectronMass.png");

  f->Close();
}
