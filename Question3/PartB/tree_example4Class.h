//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Sep 21 11:23:55 2026 by ROOT version 6.40.04
// from TTree T/tree with fixed array
// found on file: Tutorial/Outputs/Example04/myfile_example4.root
//////////////////////////////////////////////////////////

#ifndef tree_example4Class_h
#define tree_example4Class_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class tree_example4Class {
public :
   TTree          *fChain;   ///<!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; ///<!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           np;
   Float_t         px[9];   //[np]
   Float_t         py[9];   //[np]
   Float_t         pt[9];   //[np]

   // List of branches
   TBranch        *b_np;   ///<!
   TBranch        *b_px;   ///<!
   TBranch        *b_py;   ///<!
   TBranch        *b_pt;   ///<!

   tree_example4Class(TTree *tree=0);
   virtual ~tree_example4Class();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual bool     Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef tree_example4Class_cxx
tree_example4Class::tree_example4Class(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Tutorial/Outputs/Example04/myfile_example4.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Tutorial/Outputs/Example04/myfile_example4.root");
      }
      f->GetObject("T",tree);

   }
   Init(tree);
}

tree_example4Class::~tree_example4Class()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tree_example4Class::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tree_example4Class::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void tree_example4Class::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("np", &np, &b_np);
   fChain->SetBranchAddress("px", px, &b_px);
   fChain->SetBranchAddress("py", py, &b_py);
   fChain->SetBranchAddress("pt", pt, &b_pt);
   Notify();
}

bool tree_example4Class::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be for a new TTree in a TChain. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return true;
}

void tree_example4Class::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tree_example4Class::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef tree_example4Class_cxx
