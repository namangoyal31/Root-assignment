//Example using TLorentzVector
#include "TLorentzVector.h"
#include <vector>

void tree_example12() {

  TH2F *h_etaVsPhi = new TH2F("h_etaVsPhi", "eta vs phi", 100, -2.5, 2.5, 100, -3.14, 3.14);
  TH1F *h_mass = new TH1F("h_mass", "mass", 100, 40., 140.);

  TFile *f = new TFile("ntuple_array.root");
  TTree *t1 = (TTree*)f->Get("ntupleProducer/tree");

  Int_t nMuon;
  Float_t muonPx[3], muonPy[3], muonPz[3];
  t1->SetBranchAddress("nMuon",&nMuon);  
  t1->SetBranchAddress("muonPx",&muonPx);
  t1->SetBranchAddress("muonPy",&muonPy);
  t1->SetBranchAddress("muonPz",&muonPz);

  Int_t nentries = (Int_t)t1->GetEntries(); 
  cout << "No. of entries is: " << nentries << endl;

  for (Int_t i = 0; i<nentries; i++) {
  //for (Int_t i = 0; i<1000; i++) {
    t1->GetEntry(i);

    std::vector<TLorentzVector> *muons = new std::vector<TLorentzVector>();
    muons->clear();

    //Compute muon eta, phi and fill them. 
    if(nMuon>0){

      //cout << "No. of muons is: " << nMuon << endl;
      
      for(Int_t j = 0; j < nMuon; j++){
	float muonE = sqrt(muonPx[j]*muonPx[j] + muonPy[j]*muonPy[j] + muonPz[j]*muonPz[j]);
	TLorentzVector mu(muonPx[j], muonPy[j], muonPz[j], muonE);

	//apply pT cut
	//if(mu.Pt() < 20) continue;

	h_etaVsPhi->Fill(mu.Eta(), mu.Phi());

	muons->push_back(mu);
      }
    }
    //Fill mass if there are two muons
    if(muons->size() >= 2){
      TLorentzVector dimuon = (*muons)[0]+(*muons)[1];
      h_mass->Fill(dimuon.M());
    }

    delete muons;
  }
  
  TCanvas *c1 = new TCanvas();
  h_etaVsPhi->Draw("colz");
  c1->SaveAs("tree_example12_etaVsphi.png");
  
  c1->Update();
  h_mass->Draw();
  c1->SaveAs("tree_example12_dimuonMass.png");

  f->Close();
}
