//Tree with vector<MyEvent> as branch
#include <vector>
#include "MyEvent.h"

void tree_example10() {

  TFile *f = new TFile("myfile_example10.root", "RECREATE");
  TTree *T = new TTree("T","tree with vector");
  TRandom r;
  std::vector<MyEvent> *events = new std::vector<MyEvent>();

  T->Branch("Events", "std::vector<MyEvent>", &events);

  for (Int_t i = 0; i < 1000; i++) {

    //clean vectors for each event
    events->clear();
    //Fill vectors for each event
    Float_t px, py;
    Int_t np = (Int_t)(r.Rndm()*10);
    for(Int_t j = 0; j < np; j++){
      r.Rannor(px, py);
      Float_t pt = std::sqrt(px*px + py*py);
      MyEvent event;
      event.setPx(px);
      event.setPy(py);
      event.setPt(pt);
      events->push_back(event);
    }
    T->Fill();
  }
  
  f->Write();
  f->Close();

  delete events;
}

