//Example of reading Tree using MyEvent Class 
#include "MyEvent.h"

void tree_example9() {

  TH2F *h_pxpy = new TH2F("h_pxpy", "py Vs px", 100, -2.0, 2.0, 100, -2.0, 2.0);
  TH1F *h_pt = new TH1F("h_pt", "pt", 100, 0., 5.0);

  TFile *f = new TFile("myfile_example8.root");
  TTree *t1 = (TTree*)f->Get("T");

  Float_t px,py,pt;
  MyEvent *event = new MyEvent();
  
  t1->SetBranchAddress("Event", &event);

  Int_t nentries = (Int_t)t1->GetEntries(); 
  
  for (Int_t i = 0; i<nentries; i++) {
    t1->GetEntry(i);

    h_pxpy->Fill(event->getPx(), event->getPy());
    h_pt->Fill(event->getPt());
    
  }
  
  TCanvas *c1 = new TCanvas();
  h_pxpy->Draw("colz");
  c1->SaveAs("tree_example9_pxpy.png");
  
  c1->Update();
  h_pt->Draw();
  c1->SaveAs("tree_example9_pt.png");

  f->Close();
}


