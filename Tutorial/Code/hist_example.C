{
//gStyle->SetOptStat(11111);
gStyle->SetOptStat(0);
gStyle->SetOptFit(1);

TFile*myfile= new TFile("myhistos.root", "RECREATE");
myfile->cd();

TH1F *my_hist= new TH1F("my_hist", "My First Histogram", 100, 2, 200);
TCanvas *c2 = new TCanvas("c2","c2",600,600);
c2->cd();
my_hist->Fill(50);
my_hist->Fill(100,3);
my_hist->Fill(150);
my_hist->SetLineColor(kBlue);
my_hist->SetXTitle("numbers");
my_hist->SetYTitle("entries");
my_hist->Draw();


TH1F *my_hist2= new TH1F("my_hist2", "My Second Histogram", 100, 2, 200);
my_hist2->Fill(50,0.5);
my_hist2->Fill(100,1);
my_hist2->Fill(150,0.5);
my_hist2->SetLineColor(kRed);
my_hist2->Draw("esame");

c2->SaveAs("myhist.png");

my_hist->Write();
my_hist2->Write();
myfile->Close();

}
