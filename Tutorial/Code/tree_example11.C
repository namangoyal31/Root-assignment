//Read Tree with vector<MyEvent> as branch
#include <vector>
#include "MyEvent"

void tree_example11() {

  TH2F *h_pxpy = new TH2F("h_pxpy", "py Vs px", 100, -2.0, 2.0, 100, -2.0, 2.0);
  TH1F *h_pt = new TH1F("h_pt", "pt", 100, 0., 5.0);

  TFile *f = new TFile("myfile_example10.root");
  TTree *t1 = (TTree*)f->Get("T");

  std::vector<MyEvent> *events = new std::vector<MyEvent>(); 

  t1->SetBranchAddress("Events", &events);

  Int_t nentries = (Int_t)t1->GetEntries(); 
  
  for (Int_t i = 0; i<nentries; i++) {
    t1->GetEntry(i);

    //Find the object with highest pt and fill its distributions
    Float_t hPt = 0; 
    Int_t h_index = -1;
    if(events->size() > 0){
      for(Int_t j = 0; j < events->size(); j++){
	MyEvent event = events->at(j);
	if(event.getPt() > hPt){
	  hPt = event.getPt();
	  h_index = j;
	}
      }

      MyEvent event =events->at(h_index);
      h_pxpy->Fill(event.getPx(), event.getPy());
      h_pt->Fill(event.getPt());
    }
    
  }
  
  TCanvas *c1 = new TCanvas();
  h_pxpy->Draw("colz");
  c1->SaveAs("tree_example11_pxpy.png");
  
  c1->Update();
  h_pt->Draw();
  c1->SaveAs("tree_example11_pt.png");

  f->Close();

  delete events;
}


