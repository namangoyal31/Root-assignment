#define tree_example1Class_cxx
#include "tree_example1Class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void tree_example1Class::Loop()
{
//   In a ROOT session, you can do:
//      root> .L tree_example1Class.C
//      root> tree_example1Class t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;   
   TH2F *h_pxpy = new TH2F(
      "h_pxpy",
      "py Vs px",
      100, -2.0, 2.0,
      100, -2.0, 2.0
   );

   TH1F *h_pt = new TH1F(
      "h_pt",
      "pt",
      100, 0., 5.0
   );

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      h_pxpy->Fill(px, py);
      h_pt->Fill(pt);
   }
   TCanvas *c1 = new TCanvas();
   h_pxpy->Draw("colz");
   c1->SaveAs("tree_example2_pxpy.png");
   c1->Update();
   h_pt->Draw();
   c1->SaveAs("tree_example2_pt.png");
}
