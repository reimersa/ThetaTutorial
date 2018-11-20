{


  TFile* f_sig1 = new TFile("SIG500.root", "READ");
  TFile* f_sig2 = new TFile("SIG1100.root", "READ");
  TFile* f_bkg1 = new TFile("BKG1.root", "READ");
  TFile* f_bkg2 = new TFile("BKG2.root", "READ");
  TFile* f_data = new TFile("DATA.root", "READ");





  // h_bkg1->SetLineWidth(2);
  // h_bkg1->GetYaxis()->SetRangeUser(0., 50000);
  // h_bkg2->SetLineWidth(2);




  TCanvas* c = new TCanvas("c", "c", 600, 600);

  THStack* hs = new THStack("hs", "");

  TH1F* h_bkg1 = (TH1F*)f_bkg1->Get("M_ll");
  h_bkg1->SetFillColor(kAzure-1);
  h_bkg1->SetMarkerColor(kAzure-1);
  h_bkg1->SetLineColor(kAzure-1);
  h_bkg1->SetMarkerStyle(21);
  hs->Add(h_bkg1);
  TH1F* h_bkg2 = (TH1F*)f_bkg2->Get("M_ll");
  h_bkg2->SetFillColor(kRed-4);
  h_bkg2->SetMarkerColor(kRed-4);
  h_bkg2->SetLineColor(kRed-4);
  h_bkg2->SetMarkerStyle(21);
  hs->Add(h_bkg2);
  hs->Draw("hist");



  TH1F* h_sig1 = (TH1F*)f_sig1->Get("M_ll");
  h_sig1->SetLineColor(kBlack);
  h_sig1->SetMarkerColor(kBlack);
  h_sig1->SetLineWidth(2);
  h_sig1->SetLineStyle(1);
  h_sig1->Draw("hist SAME");

  TH1F* h_sig2 = (TH1F*)f_sig2->Get("M_ll");
  h_sig2->SetLineColor(kBlack);
  h_sig2->SetMarkerColor(kBlack);
  h_sig2->SetLineWidth(2);
  h_sig2->SetLineStyle(2);
  h_sig2->Draw("hist SAME");

  TH1F* h_data = (TH1F*)f_data->Get("M_ll");
  h_data->SetLineColor(kBlack);
  h_data->SetMarkerColor(kBlack);
  h_data->SetMarkerStyle(20);
  h_data->SetMarkerSize(0.7);
  h_data->Draw("E1 SAME");

  c->SaveAs("Distribution.eps");

}
