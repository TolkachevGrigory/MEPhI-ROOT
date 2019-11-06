//сравнение mu и e каналов 
void mu_e_minus()
{
  TFile* f1= new TFile("/Users/grigorijtolkacev/Desktop/ATLAS/SW/mon_el/background/minus.6.SM_WLepton.root", "READ");
  TFile* f2= new TFile("/Users/grigorijtolkacev/Desktop/ATLAS/SW/nom_mu/background/minus.1.SM_WLepton.root", "READ");

  auto enu = (TTree*)f1->Get("NOMINAL");
  auto munu = (TTree*)f2->Get("NOMINAL");
    
 // histo for comparing muon and electron
  TH1F *h_e_pt = new TH1F("e_pt", "e^{#minus} ;P_{T} [GeV];Normalized Units", 150, -10, 120);
  TH1F *h_e_phi_minus = new TH1F("e_phi", "e^{#minus};d#varphi (l-E^{miss}_{T}) ;Normalized Units", 150, -6, 6);
  TH1F *h_emet_energy = new TH1F("e_energy", "#bar{#nu}_{e};E [GeV];Normalized Units", 150, 0, 120);
  TH1F *h_enu_mt = new TH1F("e_mt", "W^{#minus} #rightarrow e^{#minus} #plus #bar{#nu}_{e};m_{T} [GeV];Normalized Units", 150, 0, 170);
  TH1F *h_e_eta = new TH1F("e_eta", "e^{#minus};#eta ;Normalized Units", 150, -3,3);
  TH1F *h_e_phi = new TH1F("e_phi", "e^{#minus};#varph ;Normalized Units", 150, -5, 5);
  TH1F *h_emet_phi = new TH1F("emet_phi", " #bar{#nu}_{e};#varphi ;Normalized Units", 150, -5, 5);
  
  TH1F *h_mu_pt = new TH1F("mu_pt", "#mu^{#minus} ;P_{T} [GeV];Normalized Units", 150, -10, 120);
  TH1F *h_mu_phi_minus = new TH1F("mu_phi", "#mu^{#minus};d#varphi (l-E^{miss}_{T}) ;Normalized Units", 150, -6, 6);
  TH1F *h_mumet_energy = new TH1F("met_energy", "#bar{#nu}_{#mu};E [GeV];Normalized Units", 150, 0, 120);
  TH1F *h_munu_mt = new TH1F("mu_mt", "W^{#minus} #rightarrow #mu^{#minus} #plus #bar{#nu}_{#mu};m_{T} [GeV];Normalized Units", 150, 0, 170);
  TH1F *h_mu_eta = new TH1F("mu_eta", "#mu^{#minus};#eta ;Normalized Units", 150, -3, 3);
  TH1F *h_mu_phi = new TH1F("mu_phi", "#mu^{#minus};#phi ;Normalized Units", 150, -5, 5);
  TH1F *h_mumet_phi = new TH1F("mu_metphi", "#bar{#nu}_{#mu};#phi ;Normalized Units", 150, -5, 5);

    gStyle->SetOptTitle(kFALSE);
    gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","",800,400);
  TCanvas *c2 = new TCanvas("c2","",800,400);
  TCanvas *c3 = new TCanvas("c3","",800,400);
  TCanvas *c4 = new TCanvas("c4","",800,400);
  TCanvas *c5 = new TCanvas("c5","",800,400);
  TCanvas *c6 = new TCanvas("c6","",800,400);
  TCanvas *c7 = new TCanvas("c7","",800,400);
    
    
 h_e_pt->SetDirectory(gROOT);
 h_e_eta->SetDirectory(gROOT);
 h_e_phi_minus->SetDirectory(gROOT);
 h_e_phi->SetDirectory(gROOT);
 h_emet_phi->SetDirectory(gROOT);
 h_emet_energy->SetDirectory(gROOT);
 h_enu_mt->SetDirectory(gROOT);


 h_mu_pt->SetDirectory(gROOT);
 h_mu_eta->SetDirectory(gROOT);
 h_mu_phi->SetDirectory(gROOT);
 h_mu_phi_minus->SetDirectory(gROOT);
 h_mumet_phi->SetDirectory(gROOT);
 h_mumet_energy->SetDirectory(gROOT);
 h_munu_mt->SetDirectory(gROOT);


  TLorentzVector* lep_e = 0;
  TLorentzVector* met_e = 0;
  TLorentzVector* lep_mu = 0;
  TLorentzVector* met_mu = 0;
    
  int n_e_t = 0;
  UInt_t lep1 = 0;
  UInt_t lep2 = 0;
  int n_e_mu = 0;
  int n_e_e = 0;
  int n_mu_mu = 0;
  int n_mu_e = 0;
  int n_mu_t = 0;
  Int_t e_medium = 0;
  UInt_t e_isoTight = 0;
  Int_t mu_medium = 0;
  UInt_t mu_isoTight = 0;
  int mu_n_bjets = 0;
  int e_n_bjets = 0;
    
  enu->SetBranchAddress("lep_0_p4", &lep_e);
  enu->SetBranchAddress("met_reco_p4", &met_e);
  enu->SetBranchAddress("n_electrons", &n_e_e);
  enu->SetBranchAddress("n_muons", &n_e_mu);
  enu->SetBranchAddress("n_taus", &n_e_t);
  enu->SetBranchAddress("lep_0_id_medium", &e_medium);
  enu->SetBranchAddress("lep_0_iso_FCTight", &e_isoTight);
  enu->SetBranchAddress("n_bjets", &e_n_bjets);
  enu->SetBranchAddress("lep_0", &lep1);
    
  munu->SetBranchAddress("lep_0_p4", &lep_mu);
  munu->SetBranchAddress("met_reco_p4", &met_mu);
  munu->SetBranchAddress("n_electrons", &n_mu_e);
  munu->SetBranchAddress("n_muons", &n_mu_mu);
  munu->SetBranchAddress("n_taus", &n_mu_t);
  munu->SetBranchAddress("lep_0_id_medium", &mu_medium);
  munu->SetBranchAddress("lep_0_iso_FCTight", &mu_isoTight);
  munu->SetBranchAddress("n_bjets", &mu_n_bjets);
  munu->SetBranchAddress("lep_0", &lep2);
    

  Long64_t N = enu->GetEntries();
  std::cout<<"N events: "<< N << std::endl;
    
    for (Long64_t i = 0; i < N ; i++)
    {
        enu->GetEntry(i);
        
        double_t e_pt = lep_e->Pt();
        double_t e_eta = lep_e->Eta();
        double_t e_phi = lep_e->Phi();
        double_t e_energy = lep_e->E();
        double_t emet_pt = met_e->Pt();
        double_t emet_phi = met_e->Phi();
        double_t emet_energy = met_e->E();
        double_t phi_e = e_phi-emet_phi;
        double_t enu_mt = sqrt(2*e_pt*emet_pt*(1-cos(phi_e)));
        
        //if( lep1==1 ) cout<<"This is Muon"<<endl;
        //if( lep1==2 ) cout<<"This is Electron"<<endl;
        
        if(!((n_e_e+n_e_mu) == 1 && n_e_t == 1))continue;
        if( !(fabs(e_eta)<1.37 || fabs(e_eta)>1.52) && (fabs(e_eta)<2.47) )continue;

        // Cut for QCD
        if ( !(e_pt > 25) ) continue;
        if ( !(emet_energy > 25) ) continue;
        if ( !(enu_mt > 40) ) continue;
        if ( !(e_medium == 1))continue;
        if ( !(e_isoTight == 1))continue;
        if ( !(e_n_bjets==0))continue;
        
        h_e_pt->Fill(e_pt);
        h_e_eta->Fill(e_eta);
        h_e_phi->Fill(e_phi);
        h_e_phi_minus->Fill(phi_e);
      
        h_emet_phi->Fill(emet_phi);
        h_emet_energy->Fill(emet_energy);
        h_enu_mt->Fill(enu_mt);

        
    }
    
    Long64_t K = munu->GetEntries();
    std::cout<<"N events: "<< K << std::endl;
      
      for (Long64_t i = 0; i < K ; i++)
      {
          munu->GetEntry(i);
          
        //  if( lep2==1 ) cout<<"This is Muon"<<endl;
       //   if( lep2==2 ) cout<<"This is Electron"<<endl;
          
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
          
          if(!((n_mu_mu+n_mu_e)==1 && n_mu_t==1)) continue;
          
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
    h_e_pt->Scale(norm/h_e_pt->Integral(), "width");
    h_e_pt->Draw("HIST ");
    h_mu_pt->SetLineColor(kRed);
    h_mu_pt->Draw("HIST same");
    gPad->BuildLegend(0.9,0.9,0.8,0.7);
      
    c2->cd();
    h_mu_phi_minus->Scale(norm/h_mu_phi_minus->Integral(), "width");
    h_e_phi_minus->Scale(norm/h_e_phi_minus->Integral(), "width");
    h_mu_phi_minus->SetLineColor(kRed);
    h_mu_phi_minus->Draw("HIST");
    h_e_phi_minus->Draw("HIST same");
    gPad->BuildLegend(0.9,0.9,0.8,0.7);

    c3->cd();
    h_mumet_energy->Scale(norm/h_mumet_energy->Integral(), "width");
    h_emet_energy->Scale(norm/h_emet_energy->Integral(), "width");
    h_emet_energy->Draw("HIST");
    h_mumet_energy->SetLineColor(kRed);
    h_mumet_energy->Draw("HIST same");
    gPad->BuildLegend(0.9,0.9,0.8,0.7);
    
    c4->cd();
    h_enu_mt->Scale(norm/h_enu_mt->Integral(), "width");
    h_munu_mt->Scale(norm/h_munu_mt->Integral(), "width");
    h_enu_mt->Draw("HIST");
    h_munu_mt->SetLineColor(kRed);
    h_munu_mt->Draw("HIST same ");
    gPad->BuildLegend(0.9,0.9,0.6,0.50);
     
    c5->cd();
    h_e_phi->Scale(norm/h_e_phi->Integral(), "width");
    h_mu_phi->Scale(norm/h_mu_phi->Integral(), "width");
    h_mu_phi->SetLineColor(kRed);
    h_mu_phi->Draw("HIST ");
    h_e_phi->Draw("HIST same");
    gPad->BuildLegend(0.9,0.9,0.8,0.7);
        
    c6->cd();
    h_emet_phi->Scale(norm/h_emet_phi->Integral(), "width");
    h_mumet_phi->Scale(norm/h_mumet_phi->Integral(), "width");
    h_mumet_phi->SetLineColor(kRed);
    h_mumet_phi->Draw("HIST ");
    h_emet_phi->Draw("HIST same");
    gPad->BuildLegend(0.9,0.9,0.8,0.7);
    
    c7->cd();
    h_e_eta->Scale(norm/h_e_eta->Integral(), "width");
    h_mu_eta->Scale(norm/h_mu_eta->Integral(), "width");
    h_e_eta->Draw("HIST ");
    h_mu_eta->SetLineColor(kRed);
    h_mu_eta->Draw("HIST same");
    gPad->BuildLegend(0.9,0.9,0.8,0.7);

    
    c1->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/lep_eandmu_minus_pt.pdf");
    c2->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/lep_eandmu_minus_l-Emiss.pdf");
    c3->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/met_eandmu_minus.energy.pdf");
    c4->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/munu_minus_mt.pdf");
    c5->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/lep_eandmu_minus_phi.pdf");
    c6->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/met_eandmu_minus_phi.pdf");
    c7->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/lep_eandmu_minus_eta.pdf");
    
}
