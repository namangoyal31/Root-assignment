#ifdef __CLING__

#pragma link C++ class MyGenParticle+;
#pragma link C++ class MyElectron+;
#pragma link C++ class MyMuon+;

#pragma link C++ class std::vector<MyGenParticle>+;
#pragma link C++ class std::vector<MyElectron>+;
#pragma link C++ class std::vector<MyMuon>+;

#endif