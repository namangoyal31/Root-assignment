#define tree_example4Class_cxx
#include "tree_example4Class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void tree_example4Class::Loop()
{
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

      Float_t hPt = 0;
      Int_t h_index = -1;

      if (np > 0) {

         for (Int_t j = 0; j < np; j++) {

            if (pt[j] > hPt) {
               hPt = pt[j];
               h_index = j;
            }
         }

         h_pxpy->Fill(px[h_index], py[h_index]);
         h_pt->Fill(pt[h_index]);
      }
   }

   TCanvas *c1 = new TCanvas();
   h_pxpy->Draw("colz");
   c1->SaveAs("tree_example5_pxpy.png");
   c1->Update();
   h_pt->Draw();
   c1->SaveAs("tree_example5_pt.png");
}