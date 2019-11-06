void minus_beackground_signal()
{
  TFile* f1= new TFile("/Users/grigorijtolkacev/Desktop/ATLAS/SW/nom_mu/signal/minus.2.SM_WLepton.root", "READ");
  TFile* f2= new TFile("/Users/grigorijtolkacev/Desktop/ATLAS/SW/nom_mu/background/minus.1.SM_WLepton.root", "READ");

  auto taunu = (TTree*)f1->Get("NOMINAL");
  auto munu = (TTree*)f2->Get("NOMINAL");

    //histo for comparing signal - beackground
  TH1F *h_tau_pt = new TH1F("tau_pt", "#tau^{#minus} ;P_{T} [GeV];Normalized Units", 150, 0, 120);
  TH1F *h_tau_phi_minus = new TH1F("tau_phi_minus", "#tau^{#minus};d#varphi (l-E^{miss}_{T}) ;Normalized Units", 150, -6, 6);
  TH1F *h_tau_phi = new TH1F("tau_phi", "#tau^{#minus};#varph ;Normalized Units", 150, -5, 5);
  TH1F *h_taumet_phi = new TH1F("taumet_phi", " #bar{#nu}_{#tau};#varphi ;Normalized Units", 150, -5, 5);
  TH1F *h_taumet_energy = new TH1F("taumet_energy", "#bar{#nu}_{#tau};E [GeV];Normalized Units", 150, 0, 100);
  TH1F *h_taunu_mt = new TH1F("tau_mt", "W^{#minus} #rightarrow #tau^{#minus} #plus #bar{#nu}_{#tau};m_{T} [GeV];Normalized Units", 150, 0, 140);
  TH1F *h_tau_eta = new TH1F("tau_eta", "#tau^{#minus};#eta ;Normalized Units", 150, -3,3);
  TH1F *h_mu_pt = new TH1F("mu_pt", "#mu^{#minus} ;P_{T} [GeV];Normalized Units", 150, 0, 120);
  TH1F *h_mu_phi_minus = new TH1F("mu_phi_minus", "#mu^{#minus};d#varphi (l-E^{miss}_{T});Normalized Units", 150, -6, 6);
  TH1F *h_mu_phi = new TH1F("mu_phi", "#mu^{#minus};#phi ;Normalized Units", 150, -5, 5);
  TH1F *h_mumet_phi = new TH1F("mu_metphi", "#bar{#nu}_{#mu};#phi ;Normalized Units", 150, -5, 5);
  TH1F *h_mumet_energy = new TH1F("met_energy", "#bar{#nu}_{#mu};E [GeV];Normalized Units", 150, 0, 120);
  TH1F *h_munu_mt = new TH1F("nu_mt", "W^{#minus} #rightarrow #mu^{#minus} #plus #bar{#nu}_{#mu};m_{T} [GeV];Normalized Units", 150, 0, 140);
  TH1F *h_mu_eta = new TH1F("mu_eta", "#mu^{#minus};#eta ;Normalized Units", 150, -3, 3);

    gStyle->SetOptTitle(kFALSE);
    gStyle->SetOptStat(0);
    
  TCanvas *c1 = new TCanvas("c1","",800,400);
  TCanvas *c2 = new TCanvas("c2","",800,400);
  TCanvas *c3 = new TCanvas("c3","",800,400);
  TCanvas *c4 = new TCanvas("c4","",800,400);
  TCanvas *c5 = new TCanvas("c5","",800,400);
  TCanvas *c6 = new TCanvas("c6","",800,400);
  TCanvas *c7 = new TCanvas("c7","",800,400);
    
    
  h_tau_pt->SetDirectory(gROOT);
  h_tau_eta->SetDirectory(gROOT);
  h_tau_phi_minus->SetDirectory(gROOT);
  h_tau_phi->SetDirectory(gROOT);
  h_taumet_phi->SetDirectory(gROOT);
  h_taumet_energy->SetDirectory(gROOT);
  h_taunu_mt->SetDirectory(gROOT);

  h_mu_pt->SetDirectory(gROOT);
  h_mu_eta->SetDirectory(gROOT);
  h_mu_phi->SetDirectory(gROOT);    
  h_mu_phi_minus->SetDirectory(gROOT);
  h_mumet_phi->SetDirectory(gROOT);
  h_mumet_energy->SetDirectory(gROOT);
  h_munu_mt->SetDirectory(gROOT);

  TLorentzVector* lep_tau = 0;
  TLorentzVector* met_tau = 0;
  TLorentzVector* lep_mu = 0;
  TLorentzVector* met_mu = 0;
    
  Int_t tau_medium = 0;
  UInt_t tau_isoTight = 0;
  Int_t mu_medium = 0;
  UInt_t mu_isoTight = 0;
  int mu_n_bjets = 0;
  int tau_n_bjets = 0;
  int n_tau_e;
  int n_tau_mu;
  int n_tau_t;
  int n_mu_e;
  int n_mu_mu;
  int n_mu_t;
    
  taunu->SetBranchAddress("lep_0_p4", &lep_tau);
  taunu->SetBranchAddress("met_reco_p4", &met_tau);
  taunu->SetBranchAddress("lep_0_id_medium", &tau_medium);
  taunu->SetBranchAddress("lep_0_iso_FCTight", &tau_isoTight);
  taunu->SetBranchAddress("n_bjets", &tau_n_bjets);
  taunu->SetBranchAddress("n_electrons", &n_tau_e);
  taunu->SetBranchAddress("n_muons", &n_tau_mu);
  taunu->SetBranchAddress("n_taus", &n_tau_t);
    
  munu->SetBranchAddress("lep_0_p4", &lep_mu);
  munu->SetBranchAddress("met_reco_p4", &met_mu);
  munu->SetBranchAddress("lep_0_id_medium", &mu_medium);
  munu->SetBranchAddress("lep_0_iso_FCTight", &mu_isoTight);
  munu->SetBranchAddress("n_bjets", &mu_n_bjets);
  munu->SetBranchAddress("n_electrons", &n_mu_e);
  munu->SetBranchAddress("n_muons", &n_mu_mu);
  munu->SetBranchAddress("n_taus", &n_mu_t);
    

  Long64_t N = taunu->GetEntries();
  std::cout<<"N events: "<< N << std::endl;
    
    for (Long64_t i = 0; i < N ; i++)
    {
        taunu->GetEntry(i);
        
        double_t tau_pt = lep_tau->Pt();
        double_t tau_eta = lep_tau->Eta();
        double_t tau_phi = lep_tau->Phi();
        double_t tau_energy = lep_tau->E();
        double_t taumet_pt = met_tau->Pt();
        double_t taumet_phi = met_tau->Phi();
        double_t taumet_energy = met_tau->E();
        double_t phi_tau = tau_phi-taumet_phi;
        double_t taunu_mt = sqrt(2*tau_pt*taumet_pt*(1-cos(phi_tau)));
        
        if ( !( (fabs(tau_eta) < 2.4)   )) continue;

        if(!((n_tau_e+n_tau_mu)==0 && n_tau_t == 1))
        // Cut for QCD
        
        if ( !(tau_pt > 25) ) continue;
        if ( !(taumet_energy > 25) ) continue;
        if ( !(taunu_mt > 40) ) continue;
        if ( !(tau_medium == 1))continue;
        if ( !(tau_isoTight == 1))continue;
        if ( !(tau_n_bjets==0))continue;
       
        h_tau_pt->Fill(tau_pt);
        h_tau_eta->Fill(tau_eta);
        h_tau_phi->Fill(tau_phi);
        h_tau_phi_minus->Fill(phi_tau);
        h_taumet_phi->Fill(taumet_phi);
        h_taumet_energy->Fill(taumet_energy);
        h_taunu_mt->Fill(taunu_mt);
    }
    
    Long64_t K = munu->GetEntries();
    std::cout<<"N events: "<< K << std::endl;
      
      for (Long64_t i = 0; i < K ; i++)
      {
             munu->GetEntry(i);
          
          double_t mu_pt = lep_mu->Pt();
          double_t mu_eta = lep_mu->Eta();
          double_t mu_phi = lep_mu->Phi();
          double_t mu_energy = lep_mu->E();
          double_t mumet_pt = met_mu->Pt();
          double_t mumet_phi = met_mu->Phi();
          double_t mumet_energy = met_mu->E();
          double_t phi_mu = mu_phi-mumet_phi;
          double_t munu_mt = sqrt(2*mu_pt*mumet_pt*(1-cos(phi_mu)));
          //mu eta gap
          if ( !( (fabs(mu_eta) < 2.4)   )) continue;
          
          if(!((n_mu_e+n_mu_mu)==1 && n_tau_t == 0))

          if ( !(mu_pt > 25) ) continue;
          if ( !(mumet_energy > 25) ) continue;
          if ( !(munu_mt > 40) ) continue;
          if( !(mu_medium == 1))continue;
          if( !(mu_isoTight == 1))continue;
          if( !(mu_n_bjets==0))continue;
          
          h_mu_pt->Fill(mu_pt);
          h_mu_eta->Fill(mu_eta);
          h_mu_phi_minus->Fill(phi_mu);
          h_mu_phi->Fill(mu_phi);
          h_mumet_phi->Fill(mumet_phi);
          h_mumet_energy->Fill(mumet_energy);
          h_munu_mt->Fill(munu_mt);
      }
      
    
  f1->Close();
  f2->Close();
    
    Double_t norm = 1;
    
    c1->cd();
    h_mu_pt->Scale(norm/h_mu_pt->Integral(), "width");
    h_tau_pt->Scale(norm/h_tau_pt->Integral(), "width");
    h_tau_pt->Draw("HIST ");
    h_mu_pt->SetLineColor(kRed);
    h_mu_pt->Draw("HIST same");
    gPad->BuildLegend(0.9,0.9,0.8,0.7);
      
    c2->cd();
    h_mu_phi_minus->Scale(norm/h_mu_phi_minus->Integral(), "width");
    h_tau_phi_minus->Scale(norm/h_tau_phi_minus->Integral(), "width");
    h_mu_phi_minus->SetLineColor(kRed);
    h_mu_phi_minus->Draw("HIST");
    h_tau_phi_minus->Draw("HIST same");
    gPad->BuildLegend(0.9,0.9,0.8,0.7);

    c3->cd();
    h_mumet_energy->Scale(norm/h_mumet_energy->Integral(), "width");
    h_taumet_energy->Scale(norm/h_taumet_energy->Integral(), "width");
    h_taumet_energy->Draw("HIST");
    h_mumet_energy->SetLineColor(kRed);
    h_mumet_energy->Draw("HIST same");
    gPad->BuildLegend(0.9,0.9,0.8,0.7);
    
    c4->cd();
    h_taunu_mt->Scale(norm/h_taunu_mt->Integral(), "width");
    h_munu_mt->Scale(norm/h_munu_mt->Integral(), "width");
    h_taunu_mt->Draw("HIST");
    h_munu_mt->SetLineColor(kRed);
    h_munu_mt->Draw("HIST same ");
    gPad->BuildLegend(0.9,0.9,0.6,0.50);
     
    c5->cd();
    h_tau_phi->Scale(norm/h_tau_phi->Integral(), "width");
    h_mu_phi->Scale(norm/h_mu_phi->Integral(), "width");
    h_mu_phi->SetLineColor(kRed);
    h_mu_phi->Draw("HIST ");
    h_tau_phi->Draw("HIST same");
    gPad->BuildLegend(0.9,0.9,0.8,0.7);
        
    c6->cd();
    h_taumet_phi->Scale(norm/h_taumet_phi->Integral(), "width");
    h_mumet_phi->Scale(norm/h_mumet_phi->Integral(), "width");
    h_mumet_phi->SetLineColor(kRed);
    h_mumet_phi->Draw("HIST ");
    h_taumet_phi->Draw("HIST same");
    gPad->BuildLegend(0.9,0.9,0.8,0.7);
    
    c7->cd();
    h_tau_eta->Scale(norm/h_tau_eta->Integral(), "width");
    h_mu_eta->Scale(norm/h_mu_eta->Integral(), "width");
    h_mu_eta->SetLineColor(kRed);
    h_mu_eta->Draw("HIST ");
    h_tau_eta->Draw("HIST same");
    gPad->BuildLegend(0.9,0.9,0.8,0.7);

    
    //c1->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/lep_muandtau_minus_pt.pdf");
    //c2->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/lep_muandtau_minus_l-Emiss.pdf");
    //c3->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/met_muandtau_minus.energy.pdf");
    //c4->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/muandtau_minus_mt.pdf");
    //c5->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/lep_muandtau_minus_phi.pdf");
    //c6->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/met_muandtau_minus_phi.pdf");
    //c7->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/lep__muandtau_minus_eta.pdf");
    
}
