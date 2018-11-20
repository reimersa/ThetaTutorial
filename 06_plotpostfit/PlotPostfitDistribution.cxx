{

  // Get the postfit file for backgrounds, input file for data (data is not modified by MLE fit)
  TFile* f_pre = new TFile("../02_thetainput/theta_histograms.root", "READ");
  TFile* f_post = new TFile("../04_thetaoutput/postfit_histograms.root", "READ");

  // Get data and signals from f_pre, the two backgrounds from f_post
  TH1F* h_data = (TH1F*)f_pre->Get("M_ll__DATA");
  TH1F* h_bkg1 = (TH1F*)f_post->Get("M_ll__BKG1");
  TH1F* h_bkg2 = (TH1F*)f_post->Get("M_ll__BKG2");

  TCanvas* c = new TCanvas("c", "c", 600, 600);
  THStack* hs = new THStack("hs", "");
  h_bkg1->SetFillColor(kAzure-1);
  h_bkg1->SetMarkerColor(kAzure-1);
  h_bkg1->SetLineColor(kAzure-1);
  h_bkg1->SetMarkerStyle(21);
  hs->Add(h_bkg1);
  h_bkg2->SetFillColor(kRed-4);
  h_bkg2->SetMarkerColor(kRed-4);
  h_bkg2->SetLineColor(kRed-4);
  h_bkg2->SetMarkerStyle(21);
  hs->Add(h_bkg2);
  hs->Draw("hist");

  h_data->SetLineColor(kBlack);
  h_data->SetMarkerColor(kBlack);
  h_data->SetMarkerStyle(20);
  h_data->SetMarkerSize(0.85);
  h_data->Draw("E1 SAME");

  c->SaveAs("Distribution_postfit.eps");

}
