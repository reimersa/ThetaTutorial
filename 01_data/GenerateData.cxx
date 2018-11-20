{
  vector<float> xsecs = {10., 5., 3., 1., 0.5, 0.1, 1., 1.};
  vector<TString> processes = {"SIG200", "SIG500", "SIG800", "SIG1100", "SIG1400", "SIG1700", "BKG1", "BKG2", "DATA"};
  vector<int> nevt_to_generate = {3000, 20000, 50000, 90000, 115000, 130000, 200000, 1000000};
  vector<TF1*> funcs;
  float range_min = 0., range_max = 2000.;


  // Define functions for signal and background
  TF1* fsig1 = new TF1("fsig1", "gaus", range_min, range_max);
  fsig1->SetParameters(1, 200, 20);
  funcs.emplace_back(fsig1);

  TF1* fsig2 = new TF1("fsig2", "gaus", range_min, range_max);
  fsig2->SetParameters(1, 500, 50);
  funcs.emplace_back(fsig2);

  TF1* fsig3 = new TF1("fsig3", "gaus", range_min, range_max);
  fsig3->SetParameters(1, 800, 80);
  funcs.emplace_back(fsig3);

  TF1* fsig4 = new TF1("fsig4", "gaus", range_min, range_max);
  fsig4->SetParameters(1, 1100, 110);
  funcs.emplace_back(fsig4);

  TF1* fsig5 = new TF1("fsig5", "gaus", range_min, range_max);
  fsig5->SetParameters(1, 1400, 140);
  funcs.emplace_back(fsig5);

  TF1* fsig6 = new TF1("fsig6", "gaus", range_min, range_max);
  fsig6->SetParameters(1, 1700, 170);
  funcs.emplace_back(fsig6);

  TF1* fbkg1 = new TF1("fbkg1", "exp(-0.0002*x)", range_min, range_max);
  funcs.emplace_back(fbkg1);

  TF1* fbkg2 = new TF1("fbkg2", "exp(-0.0035*x)", range_min, range_max);
  funcs.emplace_back(fbkg2);


  // Generate histograms from functions
  for(unsigned int i=0; i<processes.size(); i++){

    TString proc = processes[i];

    if(i != processes.size() - 1){
      // Generate histogram for this process
      TH1F* h_tmp = new TH1F("M_ll", ";M_{ll}", 50, range_min, range_max);
      h_tmp->FillRandom(funcs[i]->GetName(), nevt_to_generate[i]);
      h_tmp->Scale(xsecs[i]);

      // Write to rootfile
      TString outname = proc + ".root";
      TFile* fout = new TFile(outname, "RECREATE");
      h_tmp->Write();
      fout->Close();

      delete fout;
      delete h_tmp;
    }
    else{
      // Generate histogram for data
      TH1F* h_tmp = new TH1F("M_ll", ";M_{ll}", 50, range_min, range_max);
      h_tmp->FillRandom(funcs[i-1]->GetName(), nevt_to_generate[i-1]/4.3);
      h_tmp->FillRandom(funcs[i-2]->GetName(), nevt_to_generate[i-2]/5.4);
      h_tmp->Scale((nevt_to_generate[i-1] + nevt_to_generate[i-2])/h_tmp->Integral());

      // Write to rootfile
      TString outname = proc + ".root";
      TFile* fout = new TFile(outname, "RECREATE");
      h_tmp->Write();
      fout->Close();

      delete fout;
      delete h_tmp;

    }

  }








}
