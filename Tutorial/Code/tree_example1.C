void tree_example1() {

  TFile *f = new TFile("myfile_example1.root", "RECREATE");
  TTree *T = new TTree("T","simple tree");
  TRandom r;
  Float_t px,py,pt;
  Double_t random;
  UShort_t i;
  T->Branch("px",&px,"px/F");
  T->Branch("py",&py,"py/F");
  T->Branch("pt",&pt,"pt/F");
  T->Branch("random",&random,"random/D");

  for (i = 0; i < 10000; i++) {
    r.Rannor(px,py);
    pt = std::sqrt(px*px + py*py);
    random = r.Rndm();
    T->Fill();
  }

  f->Write();
  f->Close();
}
