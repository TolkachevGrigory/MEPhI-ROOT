void the_fouth_task(){
  TFile* f1 = new TFile("/Users/grigorijtolkacev/Desktop/ATLAS/21.root","READ");
  auto t_enu = (TTree*)f1->Get("NOMINAL");
  TH1F *h_e_pt = new TH1F("e_pt", "e ;P_{T} [GeV];Entries", 150, -10, 100);
  TH1F *h_e_eta = new TH1F("e_eta", "e ;#eta ;Entries", 150, -3, 3);
  TH1F *h_e_phi = new TH1F("e_phi", "e;#phi ;Entries", 150, -4, 4);
  TH1F *h_e_energy = new TH1F("e_energy", "e;E [GeV];Entries", 150, 0, 350);
  TH1F *h_emet_pt = new TH1F("emet_pt", "e ;P_{T} [GeV];Entries", 150, -10, 100);
  TH1F *h_emet_phi = new TH1F("emet_pt", "e;#phi ;Entries", 150, -4, 4);
  TH1F *h_emet_energy = new TH1F("emet_energy", "e;E [GeV];Entries", 150, 0, 100);
  TH1F *h_enu_mt = new TH1F("enu_mt", "e;E [GeV];Entries", 150, 0, 140);
 
    
  TH1F *h_e_pt_presel  = new TH1F("e_pt_presel ", "e ;P_{T} [GeV];Entries", 150, -10, 100);
  TH1F *h_e_eta_presel  = new TH1F("e_eta_presel ", "e ;#eta ;Entries", 150, -3, 3);
  TH1F *h_e_phi_presel  = new TH1F("e_phi_presel ", "e;#phi ;Entries", 150, -4, 4);
  TH1F *h_e_energy_presel  = new TH1F("e_energy_presel ", "e;E [GeV];Entries", 150, 0, 350);
  TH1F *h_emet_pt_presel  = new TH1F("emet_pt_presel ", "e ;P_{T} [GeV];Entries", 150, -10, 100);
  TH1F *h_emet_phi_presel  = new TH1F("emet_pt_presel ", "e;#phi ;Entries", 150, -4, 4);
  TH1F *h_emet_energy_presel  = new TH1F("emet_energy_presel ", "e;E [GeV];Entries", 150, 0, 100);
  TH1F *h_enu_mt_presel  = new TH1F("enu_mt_presel ", "e;E [GeV];Entries", 150, 0, 140);

  TCanvas *c1 = new TCanvas("c1","",1000,800);
  TCanvas *c2 = new TCanvas("c2","",1000,800);
  c1->Divide(2,2);
  c2->Divide(2,2);
  
  h_e_pt->SetDirectory(gROOT);
  h_e_eta->SetDirectory(gROOT);
  h_e_phi->SetDirectory(gROOT);
  h_e_energy->SetDirectory(gROOT);
  h_emet_pt->SetDirectory(gROOT);
  h_emet_phi->SetDirectory(gROOT);
  h_emet_energy->SetDirectory(gROOT);
  h_enu_mt->SetDirectory(gROOT);
    
  h_e_pt_presel->SetDirectory(gROOT);
  h_e_eta_presel->SetDirectory(gROOT);
  h_e_phi_presel->SetDirectory(gROOT);
  h_e_energy_presel->SetDirectory(gROOT);
  h_emet_pt_presel->SetDirectory(gROOT);
  h_emet_phi_presel->SetDirectory(gROOT);
  h_emet_energy_presel->SetDirectory(gROOT);
  h_enu_mt_presel->SetDirectory(gROOT);

  TLorentzVector* lep_0 = 0;
  TLorentzVector* met_e = 0;
  int n_e = 0;
  int n_mu = 0;
  int n_t = 0;
  t_enu->SetBranchAddress("lep_0_p4", &lep_0);
  t_enu->SetBranchAddress("met_reco_p4", &met_e);
  t_enu->SetBranchAddress("n_electrons", &n_e);
  t_enu->SetBranchAddress("n_muons", &n_mu);
  t_enu->SetBranchAddress("n_taus", &n_t);
  t_enu->SetBranchAddress("met_reco_p4", &met_e);

  Long64_t nEvents = t_enu->GetEntries();
  std::cout << "N events: " << nEvents << std::endl;
  for (Long64_t i = 0; i < nEvents; i++) {
    t_enu->GetEntry(i);

    double_t e_pt = lep_0->Pt();
    double_t e_eta = lep_0->Eta();
    double_t e_phi = lep_0->Phi();
    double_t e_energy = lep_0->E();
    double_t emet_pt = met_e->Pt();
    double_t emet_phi = met_e->Phi();
    double_t emet_energy = met_e->E();
    double_t enu_mt = sqrt(2*e_pt*emet_pt*(1-cos(e_phi-emet_phi)));
    
    h_e_pt_presel->Fill(e_pt);
    h_e_eta_presel->Fill(e_eta);
    h_e_phi_presel->Fill(e_phi);
    h_e_energy_presel->Fill(e_energy);
    h_emet_pt_presel->Fill(emet_pt);
    h_emet_phi_presel->Fill(emet_phi);
    h_emet_energy_presel->Fill(emet_energy);
    h_enu_mt_presel->Fill(enu_mt);
    
      

//if(n_e==0 && n_t == 0)continue;
      if ( !( (fabs(e_eta) < 1.32 || fabs(e_eta) > 1.52) && (fabs(e_eta ) < 2.47) ) ) continue;
      if((n_e+n_mu)==1 && n_t==0)continue;
      if(!(enu_mt > 40)) continue;
      if ( !(e_pt > 25) ) continue;
     if ( !(emet_pt > 25) ) continue;
      
      h_e_pt->Fill(e_pt);
      h_e_eta->Fill(e_eta);
      h_e_phi->Fill(e_phi);
      h_e_energy->Fill(e_energy);
      h_emet_pt->Fill(emet_pt);
      h_emet_phi->Fill(emet_phi);
      h_emet_energy->Fill(emet_energy);
      h_enu_mt->Fill(enu_mt);
  }
  f1->Close();
  c1->cd(1);
  h_e_pt_presel->Draw("HIST");
  h_e_pt->SetLineColor(kRed);
  h_e_pt->Draw("HIST same");
    
  c1->cd(2);
  h_e_eta_presel->Draw("HIST");
  h_e_eta->SetLineColor(kRed);
  h_e_eta->Draw("HIST same");
    
  c1->cd(3);
  h_e_phi_presel->Draw("HIST");
  h_e_phi->SetLineColor(kRed);
  h_e_phi->Draw("HIST same");

  c1->cd(4);
  h_e_energy_presel->Draw("HIST");
  h_e_energy->SetLineColor(kRed);
  h_e_energy->Draw("HIST same");
  
  c2->cd(1);
  h_emet_pt_presel->Draw("HIST");
  h_emet_pt->SetLineColor(kRed);
  h_emet_pt->Draw("HIST same");

  c2->cd(2);
  h_emet_phi_presel->Draw("HIST");
  h_emet_phi->SetLineColor(kRed);
  h_emet_phi->Draw("HIST same");
  
  c2->cd(3);
  h_emet_energy_presel->Draw("HIST");
  h_emet_energy->SetLineColor(kRed);
  h_emet_energy->Draw("HIST same");
  
  c2->cd(4);
  h_enu_mt_presel->Draw("HIST");
  h_enu_mt->SetLineColor(kRed);
  h_enu_mt->Draw("HIST same");

}
