//Tree with vectors
#include <vector>

void tree_example6() {

  TFile *f = new TFile("myfile_example6.root", "RECREATE");
  TTree *T = new TTree("T","tree with fixed array");
  TRandom r;
  std::vector<Float_t> px, py, pt;
  Int_t np;

  T->Branch("px", "std::vector<Float_t>", &px);
  T->Branch("py", "std::vector<Float_t>", &py);
  T->Branch("pt", "std::vector<Float_t>", &pt);

  for (Int_t i = 0; i < 1000; i++) {

    //clean vectors for each event
    px.clear(); py.clear(); pt.clear();
    //Fill vectors for each event
    Float_t x, y;
    np = (Int_t)(r.Rndm()*10);
    for(Int_t j = 0; j < np; j++){
      r.Rannor(x, y);
      px.push_back(x);
      py.push_back(y);
      pt.push_back(std::sqrt(x*x + y*y));
    }
    T->Fill();
  }
  
  f->Write();
  f->Close();
}
