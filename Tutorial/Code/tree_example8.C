//Example of Tree using MyEvent Class 
#include "MyEvent.h"

void tree_example8() {

  TFile *f = new TFile("myfile_example8.root", "RECREATE");
  TTree *T = new TTree("T","tree with class");
  TRandom r;
  Float_t px,py,pt;

  MyEvent *event = new MyEvent();
  T->Branch("Event", "MyEvent", &event);

  for (Int_t i = 0; i < 10000; i++) {
    r.Rannor(px,py);
    pt = std::sqrt(px*px + py*py);
    
    event->setPx(px);
    event->setPy(py);
    event->setPt(pt);

    T->Fill();
  }
  
  f->Write();
  f->Close();
}


