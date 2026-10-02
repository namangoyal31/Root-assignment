#define tree_example1Class_cxx

#include "tree_example1Class.h"

#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>

void tree_example1Class::Loop()
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

   TH1F *h_pt1 = new TH1F(
      "h_pt1",
      "pt > 1 GeV",
      100, 0., 5.0
   );

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   for (Long64_t jentry = 0; jentry < nentries; jentry++) {

      Long64_t ientry = LoadTree(jentry);

      if (ientry < 0) break;

      nb = fChain->GetEntry(jentry);
      nbytes += nb;

      h_pxpy->Fill(px, py);

      h_pt->Fill(pt);

      if (pt > 1.0)
         h_pt1->Fill(pt);
   }

   TCanvas *c1 = new TCanvas();

   h_pxpy->Draw("colz");

   c1->SaveAs("Question3/PartA/Outputs/tree_example2_pxpy.png");

   c1->Update();

   h_pt->SetLineColor(2);
   h_pt->SetLineWidth(2);

   h_pt1->SetLineColor(4);
   h_pt1->SetLineWidth(2);

   h_pt->Draw();

   h_pt1->Draw("sames");

   c1->SaveAs("Question3/PartA/Outputs/tree_example2_pt.png");
}