void scan_momentum()
{
  app->InitMC("geometry/cubox");
  app->SetPrimaryPDG(-13);
  TGraph *gLoss = new TGraph();
  gLoss->SetTitle("Energy Loss vs Momentum;Momentum [GeV];Energy Deposited [GeV]");
  gLoss->SetMarkerStyle(20);
  gLoss->SetMarkerColor(kBlue);
  gLoss->SetLineWidth(2);
  gLoss->SetLineColor(kBlue);
  int n_steps = 20; 
  double p_min = 0.1;
  double p_max = 4.0;
  double step_size = (p_max - p_min) / (n_steps - 1);
  for (int i =0; i<n_steps; i++){
    double current_p = p_min + (i * step_size);
    app->SetPrimaryMomentum(current_p);
    if (gROOT->FindObject("hPrimaryEnergy")) 
      (TH1*)gROOT->FindObject("hPrimaryEnergy"))->Reset("");
    app->RunMC(1, 1);
    double loss = app->depEinNode("/EXPH_1/CALB_1");
    std::cout << "Momentum: " << current_p << " GeV -> Loss: " << loss << " GeV" << std::endl;
    gLoss->SetPoint(i, current_p, loss);
    }
  TCanvas *c1 = new TCanvas("c1", "Momentum Scan", 800, 600);
  c1->SetGrid(); 
  gLoss->Draw("ALP");
  c1->Update();

}


