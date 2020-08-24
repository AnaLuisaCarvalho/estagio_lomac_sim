void NScint10() {
TFile *f = new TFile("outputNtupleTileFCC.root");
  TTree *myTree = (TTree *) f->Get("eventTree");

  TCanvas *c1 = new TCanvas();
  TH1I *NScintP = new TH1I ("NScintP", "", 100, 1350, 1100);
  NScintP->SetXTitle(" number of scintillation photons");
  NScintP->SetLineColor(kRed);
  NScintP->SetLineWidth(2);


  myTree->Draw("NScintPhotons>>NScintP");
  c1->SaveAs("NScint10.png");


  TH1F *TileHE = new TH1F ("TileHE", "", 20, 2.86, 3.48);
  TCanvas *c2 = new TCanvas();

  TileHE->SetXTitle("energy/scintillation photons (eV)");
  TileHE->SetLineColor(kBlue);
  TileHE->SetLineWidth(2);

  myTree->Draw("TileHitsEdep>>TileHE");
  c2->SaveAs("TileHE.png");


  TH1F *hPMTHE = new TH1F ("PMTHE", "", 15, 1.99, 2.95);
  TCanvas *c3 = new TCanvas();
  
	hPMTHE->SetXTitle("wave length shfiting photons/Energy ev");
 	hPMTHE->SetLineColor(kBlue);
        hPMTHE->SetLineWidth(3);
        myTree->Draw("PMTHitsEdep>>PMTHE");
	c3->SaveAs("FiberHitsEdep.png");

}

