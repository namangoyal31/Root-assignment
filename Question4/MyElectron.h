#ifndef MyElectron_h
#define MyElectron_h

#include <TObject.h>

class MyElectron : public TObject {
public:

    Float_t px;
    Float_t py;
    Float_t pz;
    Float_t pt;
    Float_t eta;
    Float_t phi;

    Float_t dxy;
    Float_t dz;

    Int_t charge;

    MyElectron() {}

    MyElectron(
        Float_t px_,
        Float_t py_,
        Float_t pz_,
        Float_t pt_,
        Float_t eta_,
        Float_t phi_,
        Float_t dxy_,
        Float_t dz_,
        Int_t charge_
    )
        : px(px_),
          py(py_),
          pz(pz_),
          pt(pt_),
          eta(eta_),
          phi(phi_),
          dxy(dxy_),
          dz(dz_),
          charge(charge_)
    {}

    ClassDef(MyElectron, 1);
};

#endif
