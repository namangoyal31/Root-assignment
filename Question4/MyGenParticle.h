#ifndef MyGenParticle_h
#define MyGenParticle_h

#include <TObject.h>

class MyGenParticle : public TObject {
public:

    Float_t px;
    Float_t py;
    Float_t pz;
    Float_t pt;
    Float_t eta;
    Float_t phi;

    Int_t charge;
    Int_t pdgId;

    MyGenParticle() {}

    MyGenParticle(
        Float_t px_,
        Float_t py_,
        Float_t pz_,
        Float_t pt_,
        Float_t eta_,
        Float_t phi_,
        Int_t charge_,
        Int_t pdgId_
    )
        : px(px_),
          py(py_),
          pz(pz_),
          pt(pt_),
          eta(eta_),
          phi(phi_),
          charge(charge_),
          pdgId(pdgId_)
    {}

    ClassDef(MyGenParticle, 1);
};

#endif