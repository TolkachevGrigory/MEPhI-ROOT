void the_fouth_task(){
  TFile* f1= new TFile("/Users/grigorijtolkacev/Desktop/ATLAS/21.root", "READ");
  TFile* f2= new TFile("/Users/grigorijtolkacev/Desktop/ATLAS/user.dponomar.17679514._000003.SM_WLepton.root", "READ");

  auto enu = (TTree*)f1->Get("NOMINAL");
  auto munu = (TTree*)f2->Get("NOMINAL");
    
    
   TH1F *h_e_pt = new TH1F("e_pt", "e ;P_{T} [GeV];Normalized Units", 150, -10, 100);
   TH1F *h_e_eta = new TH1F("e_eta", "e ;#eta ;Normalized Units", 150, -3, 3);
   TH1F *h_e_phi = new TH1F("e_phi", "e;#phi ;Normalized Units", 150, -4, 4);
   TH1F *h_e_energy = new TH1F("e_energy", "e;E [GeV];Normalized Units", 150, 0, 350);
   TH1F *h_emet_pt = new TH1F("emet_pt", "#nu_{e} ;P_{T} [GeV];Normalized Units", 150, -10, 100);
   TH1F *h_emet_phi = new TH1F("emet_pt", "#nu_{e};#phi ;Normalized Units", 150, -4, 4);
   TH1F *h_emet_energy = new TH1F("emet_energy", "#nu_{e};E [GeV];Normalized Units", 150, 0, 100);
   TH1F *h_enu_mt = new TH1F("enu_mt", "W #rightarrow e #nu_{e};m_{T} [GeV];Normalized Units", 150, 0, 140);
  
  TH1F *h_mu_pt = new TH1F("_pt", "#mu ;P_{T} [GeV];Normalized Units", 150, -10, 100);
  TH1F *h_mu_eta = new TH1F("_eta", "#mu ;#eta ;Normalized Units", 150, -3, 3);
  TH1F *h_mu_phi = new TH1F("_phi", "#mu;#phi ;Normalized Units", 150, -4, 4);
  TH1F *h_mu_energy = new TH1F("_energy", "#mu;E [GeV];Normalized Units", 150, 0, 350);
  TH1F *h_mumet_pt = new TH1F("met_pt", " #nu_{#mu} ;P_{T} [GeV];Normalized Units", 150, -10, 100);
  TH1F *h_mumet_phi = new TH1F("emet_pt", "#nu_{#mu};#phi ;Normalized Units", 150, -4, 4);
  TH1F *h_mumet_energy = new TH1F("met_energy", "#nu_{#mu};E [GeV];Normalized Units", 150, 0, 100);
  TH1F *h_munu_mt = new TH1F("nu_mt", "W #rightarrow #mu #nu_{#mu};m_{T} [GeV];Normalized Units", 150, 0, 140);

  
    //gStyle->SetOptTitle(kFALSE);
  //0gStyle->SetOptStat(0);
   TCanvas *c1 = new TCanvas("c1","",1400,800);
   TCanvas *c2 = new TCanvas("c2","",1400,800);
   gStyle->SetOptTitle(kFALSE);
   gStyle->SetOptStat(0);

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


    h_mu_pt->SetDirectory(gROOT);
    h_mu_eta->SetDirectory(gROOT);
    h_mu_phi->SetDirectory(gROOT);
    h_mu_energy->SetDirectory(gROOT);
    h_mumet_pt->SetDirectory(gROOT);
    h_mumet_phi->SetDirectory(gROOT);
    h_mumet_energy->SetDirectory(gROOT);
    h_munu_mt->SetDirectory(gROOT);


  TLorentzVector* lep_e = 0;
  TLorentzVector* met_e = 0;
  TLorentzVector* lep_mu = 0;
  TLorentzVector* met_mu = 0;
    
  int n_e_t = 0;
 // UInt_t lep = 0;
  int n_e_mu = 0;
  int n_e_e = 0;
  int n_mu_mu = 0;
  int n_mu_e = 0;
  int n_mu_t = 0;
  Int_t e_medium = 0;
  UInt_t e_Gradient = 0;
  Int_t mu_medium = 0;
  UInt_t mu_Gradient = 0;
    
  enu->SetBranchAddress("lep_0_p4", &lep_e);
  enu->SetBranchAddress("met_reco_p4", &met_e);
  enu->SetBranchAddress("n_electrons", &n_e_e);
  enu->SetBranchAddress("n_muons", &n_e_mu);
  enu->SetBranchAddress("n_taus", &n_e_t);
  enu->SetBranchAddress("lep_0_id_medium", &e_medium);
  enu->SetBranchAddress("lep_0_iso_Gradient", &e_Gradient);


  munu->SetBranchAddress("lep_0_p4", &lep_mu);
  munu->SetBranchAddress("met_reco_p4", &met_mu);
  munu->SetBranchAddress("n_electrons", &n_mu_e);
  munu->SetBranchAddress("n_muons", &n_mu_mu);
  munu->SetBranchAddress("n_taus", &n_mu_t);
  munu->SetBranchAddress("lep_0_id_medium", &mu_medium);
  munu->SetBranchAddress("lep_0_iso_Gradient", &mu_Gradient);
    

  Long64_t N = enu->GetEntries();
  std::cout<<"N events: "<< N << std::endl;
    
    for (Long64_t i = 0; i < N ; i++) {
      enu->GetEntry(i);
        
        double_t e_pt = lep_e->Pt();
        double_t e_eta = lep_e->Eta();
        double_t e_phi = lep_e->Phi();
        double_t e_energy = lep_e->E();
        double_t emet_pt = met_e->Pt();
        double_t emet_phi = met_e->Phi();
        double_t emet_energy = met_e->E();
        double_t enu_mt = sqrt(2*e_pt*emet_pt*(1-cos(e_phi-emet_phi)));
        if ( !( (fabs(e_eta) < 1.35 || fabs(e_eta) > 1.59) && (fabs(e_eta) < 2.47) ) ) continue;
        // Cut for QCD
        if ( !(e_pt > 25) ) continue;
        if ( !(emet_pt > 25) ) continue;
        if ( !(enu_mt > 40) ) continue;
        if(!(e_medium == 1)&& !(e_Gradient == 1))continue;
        if(n_e_e == 1 && n_e_mu == 0  && n_e_t == 0){
        h_e_pt->Fill(e_pt);
        h_e_eta->Fill(e_eta);
        h_e_phi->Fill(e_phi);
        h_e_energy->Fill(e_energy);
        h_emet_pt->Fill(emet_pt);
        h_emet_phi->Fill(emet_phi);
        h_emet_energy->Fill(emet_energy);
        h_enu_mt->Fill(enu_mt);
    }
    }
    
    Long64_t K = munu->GetEntries();
    std::cout<<"N events: "<< K << std::endl;
      
      for (Long64_t i = 0; i < K ; i++) {
             munu->GetEntry(i);
          
          double_t mu_pt = lep_mu->Pt();
          double_t mu_eta = lep_mu->Eta();
          double_t mu_phi = lep_mu->Phi();
          double_t mu_energy = lep_mu->E();
          double_t mumet_pt = met_mu->Pt();
          double_t mumet_phi = met_mu->Phi();
          double_t mumet_energy = met_mu->E();
          double_t munu_mt = sqrt(2*mu_pt*mumet_pt*(1-cos(mu_phi-mumet_phi)));
          
          if ( !(mu_pt > 25) ) continue;
          if ( !(mumet_pt > 25) ) continue;
          if ( !(munu_mt > 40) ) continue;
          if(!(mu_medium == 1)&& !(mu_Gradient == 1))continue;
         if(n_mu_e == 0 && n_mu_mu == 1 && n_mu_t == 0){
          h_mu_pt->Fill(mu_pt);
          h_mu_eta->Fill(mu_eta);
          h_mu_phi->Fill(mu_phi);
          h_mu_energy->Fill(mu_energy);
          h_mumet_pt->Fill(mumet_pt);
          h_mumet_phi->Fill(mumet_phi);
          h_mumet_energy->Fill(mumet_energy);
          h_munu_mt->Fill(munu_mt);
      }
      }
      
    
  f1->Close();
  f2->Close();
    
    Double_t norm = 1;
    h_mu_pt->Scale(norm/h_mu_pt->Integral(), "width");
    h_e_pt->Scale(norm/h_e_pt->Integral(), "width");
    c1->cd(1);
    h_mu_pt->SetLineColor(kRed);
    h_mu_pt->Draw("HIST");
    h_e_pt->Draw("HIST same");
    gPad->BuildLegend(0.9,0.1,0.8,0.3);
    
      
    c1->cd(2);
    h_mu_eta->Scale(norm/h_mu_eta->Integral(), "width");
    h_e_eta->Scale(norm/h_e_eta->Integral(), "width");
    h_e_eta->Draw("HIST");
    h_mu_eta->SetLineColor(kRed);
    h_mu_eta->Draw("HIST same");
    gPad->BuildLegend(0.9,0.1,0.8,0.3);
      
    c1->cd(3);
    h_mu_phi->Scale(norm/h_mu_phi->Integral(), "width");
    h_e_phi->Scale(norm/h_e_phi->Integral(), "width");
    h_e_phi->Draw("HIST");
    h_mu_phi->SetLineColor(kRed);
    h_mu_phi->Draw("HIST same");
    gPad->BuildLegend(0.9,0.1,0.8,0.3);

    c1->cd(4);
    h_mu_energy->Scale(norm/h_mu_energy->Integral(), "width");
    h_e_energy->Scale(norm/h_e_energy->Integral(), "width");
    h_e_energy->Draw("HIST");
    h_mu_energy->SetLineColor(kRed);
    h_mu_energy->Draw("HIST same");
    gPad->BuildLegend(0.9,0.1,0.8,0.3);
    
    c2->cd(1);
    h_mumet_pt->Scale(norm/h_mumet_pt->Integral(), "width");
    h_emet_pt->Scale(norm/h_emet_pt->Integral(), "width");
    h_mumet_pt->SetLineColor(kRed);
    h_mumet_pt->Draw("HIST");
    h_emet_pt->Draw("HIST same");
    gPad->BuildLegend(0.9,0.1,0.8,0.3);
   
    c2->cd(2);
    h_mumet_phi->Scale(norm/h_mumet_phi->Integral(), "width");
    h_emet_phi->Scale(norm/h_emet_phi->Integral(), "width");
    h_emet_phi->Draw("HIST");
    h_mumet_phi->SetLineColor(kRed);
    h_mumet_phi->Draw("HIST same");
    gPad->BuildLegend(0.9,0.1,0.8,0.3);
    
    c2->cd(3);
    h_mumet_energy->Scale(norm/h_mumet_energy->Integral(), "width");
    h_emet_energy->Scale(norm/h_emet_energy->Integral(), "width");
    h_mumet_energy->SetLineColor(kRed);
    h_mumet_energy->Draw("HIST");
    h_emet_energy->Draw("HIST same");
    gPad->BuildLegend(0.9,0.1,0.8,0.3);
    
    
    c2->cd(4);
    h_enu_mt->Scale(norm/h_enu_mt->Integral(), "width");
    h_munu_mt->Scale(norm/h_munu_mt->Integral(), "width");
    h_enu_mt->Draw("HIST");
    h_munu_mt->SetLineColor(kRed);
    h_munu_mt->Draw("HIST same");
    gPad->BuildLegend(0.9,0.1,0.8,0.3);
    
    c1->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/t4.1.pdf");
    c2->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/t4.2.pdf");
}
