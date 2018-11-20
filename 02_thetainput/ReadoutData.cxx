{

  // Define vector to hold all histograms we want to pass to theta in the end
  vector<TH1F*> hists;

  // Processes we want to pass to theta, ideally already part of the root-filename
  vector<TString> processes = {"SIG200", "SIG500", "SIG800", "SIG1100", "SIG1400", "SIG1700", "BKG1", "BKG2", "DATA"};

  // If not already done, the signal samples should be normalized to a production cross section of 1pb (in this example, we have to do this)
  // Cross sections are taken from "01_data/GenerateData.cxx"
  map<TString, float> xsecs;
  xsecs["SIG200"] = 10.;
  xsecs["SIG500"] = 5.;
  xsecs["SIG800"] = 3.;
  xsecs["SIG1100"] = 1.;
  xsecs["SIG1400"] = 0.5;
  xsecs["SIG1700"] = 0.1;

  // folder holding the rootfiles
  TString infilename_base = "../01_data/";

  // Loop over all processes for which we want to extract the histogram(s)
  for(unsigned int i=0; i<processes.size(); i++){
    TString proc = processes[i];
    TString infilename = infilename_base + proc + ".root";

    // Get file
    TFile* fin = new TFile(infilename, "READ");

    // Get histogram
    TH1F* h = (TH1F*)fin->Get("M_ll");

    // In case it is a signal histogram, normalize to 1pb
    if(proc.Contains("SIG")) h->Scale(1./xsecs[proc]);

    // Change name of histogram to follow theta's naming convention: Observable__Process(__SystematicName__SystematicDirection)
    // Note: Data always has to be named Observable__DATA(__SystematicName__SystematicDirection) [--> DATA all caps!]
    // At the moment, we don't consider systematics, lucky us!
    TString histname = "M_ll__" + proc;
    h->SetName(histname);

    // Append this hist to vector of hists
    hists.emplace_back(h);
  }

  // Loop over vector of hists, storing each of its elements to the file we'll feed to theta
  TFile* fout = new TFile("theta_histograms.root", "RECREATE");
  for(unsigned int i=0; i<hists.size(); i++) hists.at(i)->Write();
  fout->Close();
}
