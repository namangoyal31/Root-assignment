#ifndef MyMuon_h
#define MyMuon_h

#include <TObject.h>

class MyMuon : public TObject {
public:

    Float_t px;
    Float_t py;
    Float_t pz;
    Float_t pt;
    Float_t eta;
    Float_t phi;

    Float_t dz;
    Float_t dxy;

    Int_t charge;

    MyMuon() {}

    MyMuon(
        Float_t px_,
        Float_t py_,
        Float_t pz_,
        Float_t pt_,
        Float_t eta_,
        Float_t phi_,
        Float_t dz_,
        Float_t dxy_,
        Int_t charge_
    )
        : px(px_),
          py(py_),
          pz(pz_),
          pt(pt_),
          eta(eta_),
          phi(phi_),
          dz(dz_),
          dxy(dxy_),
          charge(charge_)
    {}

    ClassDef(MyMuon, 1);
};

#endif