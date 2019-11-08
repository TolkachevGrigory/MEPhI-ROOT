//электронный кана сигнал/шум с татистическую ошибку
void minus_beackground_signal_nomel()
{
 TFile* f1= new TFile("/Users/grigorijtolkacev/Desktop/ATLAS/SW/mon_el/signal/minus.1.SM_WLepton.root", "READ");
  TFile* f2= new TFile("/Users/grigorijtolkacev/Desktop/ATLAS/SW/mon_el/background/minus.6.SM_WLepton.root", "READ");

  auto taunu = (TTree*)f1->Get("NOMINAL");
  auto munu = (TTree*)f2->Get("NOMINAL");

    //histo for comparing signal - beackground
  TH1F *h_tau_pt = new TH1F("tau_pt", "#tau^{#minus} ;P_{T} [GeV];Normalized Units", 150, 20, 90);
  TH1F *h_tau_phi_minus = new TH1F("tau_phi_minus", "#tau^{#minus};d#varphi (l-E^{miss}_{T}) ;Normalized Units", 150, -4, 4);
  TH1F *h_tau_phi = new TH1F("tau_phi", "#tau^{#minus};#varphi ;Normalized Units", 150, -5, 5);
  TH1F *h_taumet_phi = new TH1F("taumet_phi", " #bar{#nu}_{#tau};#varphi ;Normalized Units", 150, -5, 5);
  TH1F *h_taumet_energy = new TH1F("taumet_energy", "#bar{#nu}_{#tau};E [GeV];Normalized Units", 150, 20, 100);
  TH1F *h_taunu_mt = new TH1F("tau_mt", "W^{#minus} #rightarrow #tau^{#minus} #plus #bar{#nu}_{#tau};m_{T} [GeV];Normalized Units", 150, 35, 160);
  TH1F *h_tau_eta = new TH1F("tau_eta", "#tau^{#minus};#eta ;Normalized Units", 150, -3,3);
    
    
    
  TH1F *h_mu_pt = new TH1F("e_pt", "e^{#minus} ;P_{T} [GeV];Normalized Units", 150, 20, 90);
  TH1F *h_mu_phi_minus = new TH1F("e_phi", "e^{#minus};d#varphi (l-E^{miss}_{T}) ;Normalized Units", 150, -4, 4);
  TH1F *h_mu_phi = new TH1F("e_phi", "e^{#minus};#varphi ;Normalized Units", 150, -5, 5);
  TH1F *h_mumet_phi = new TH1F("emet_phi", " #bar{#nu}_{e};#varphi ;Normalized Units", 150, -4, 4);
  TH1F *h_mumet_energy = new TH1F("e_energy", "#bar{#nu}_{e};E [GeV];Normalized Units", 150, 20, 120);
  TH1F *h_munu_mt = new TH1F("e_mt", "W^{#minus} #rightarrow e^{#minus} #plus #bar{#nu}_{e};m_{T} [GeV];Normalized Units", 150, 35, 160);
  TH1F *h_mu_eta = new TH1F("e_eta", "e^{#minus};#eta ;Normalized Units", 150, -3,3);

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
  int n_tau_e = 0 ;
  int n_tau_mu = 0;
  int n_tau_t = 0;
  int n_mu_e = 0;
  int n_mu_mu =0 ;
  int n_mu_t = 0;
  UInt_t lep1 = 0;
  UInt_t lep2 = 0;

    
  taunu->SetBranchAddress("lep_0_p4", &lep_tau);
  taunu->SetBranchAddress("met_reco_p4", &met_tau);
  taunu->SetBranchAddress("lep_0_id_medium", &tau_medium);
  taunu->SetBranchAddress("lep_0_iso_FCTight", &tau_isoTight);
  taunu->SetBranchAddress("n_bjets", &tau_n_bjets);
  taunu->SetBranchAddress("n_electrons", &n_tau_e);
  taunu->SetBranchAddress("n_muons", &n_tau_mu);
  taunu->SetBranchAddress("n_taus", &n_tau_t);
  taunu->SetBranchAddress("lep_0", &lep1);
    
  munu->SetBranchAddress("lep_0_p4", &lep_mu);
  munu->SetBranchAddress("met_reco_p4", &met_mu);
  munu->SetBranchAddress("lep_0_id_medium", &mu_medium);
  munu->SetBranchAddress("lep_0_iso_FCTight", &mu_isoTight);
  munu->SetBranchAddress("n_bjets", &mu_n_bjets);
  munu->SetBranchAddress("n_electrons", &n_mu_e);
  munu->SetBranchAddress("n_muons", &n_mu_mu);
  munu->SetBranchAddress("n_taus", &n_mu_t);
  taunu->SetBranchAddress("lep_0", &lep2);
    

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
        
        if ( !(fabs(tau_eta)<1.37 || fabs(tau_eta)>1.52) && (fabs(tau_eta)<2.47) )continue;

       // if(!((n_tau_e+n_tau_mu)==0 && n_tau_t == 1))continue;
        // Cut for QCD
        
        if ( !(tau_pt > 25) ) continue;
        if ( !(taumet_energy > 25) ) continue;
        if ( !(taunu_mt > 40) ) continue;
        if ( !(tau_medium == 1))continue;
        if ( !(tau_isoTight == 1))continue;
        if ( !(tau_n_bjets==0))continue;
        
        h_tau_phi->Fill(tau_phi);
        h_taumet_phi->Fill(taumet_phi);
        
        if ( !(fabs(phi_tau)<3.14 && fabs(phi_tau)>0))continue;
        h_tau_pt->Fill(tau_pt);
        h_tau_eta->Fill(tau_eta);
        h_tau_phi_minus->Fill(phi_tau);
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
          if ( !(fabs(mu_eta)<1.37 || fabs(mu_eta)>1.52) && (fabs(mu_eta)<2.47) )continue;
          
          if(!((n_mu_e+n_mu_mu)==1 && n_mu_t == 0))continue;
         

          if ( !(mu_pt > 25) ) continue;
          if ( !(mumet_energy > 25) ) continue;
          if ( !(munu_mt > 40) ) continue;
          if( !(mu_medium == 1))continue;
          if( !(mu_isoTight == 1))continue;
          if( !(mu_n_bjets==0))continue;
          
          h_mu_phi->Fill(mu_phi);
          h_mumet_phi->Fill(mumet_phi);
          
        if ( !(fabs(phi_mu)<3.14 && fabs(phi_mu)>0))continue;
          
          
          h_mu_pt->Fill(mu_pt);
          h_mu_eta->Fill(mu_eta);
          h_mu_phi_minus->Fill(phi_mu);
          
          h_mumet_energy->Fill(mumet_energy);
          h_munu_mt->Fill(munu_mt);
      }
      
    
  f1->Close();
  f2->Close();
    
    Double_t norm = 1;
    
    c1->cd();
    h_mu_pt->Scale(norm/h_mu_pt->Integral(), "width");
    h_tau_pt->Scale(norm/h_tau_pt->Integral(), "width");
    
    h_tau_pt->SetLineColor(kBlue+3);
    //h_tau_pt->Sumw2();
    h_tau_pt-> SetMarkerStyle (21);
    h_tau_pt-> SetMarkerSize (0.2);
    h_tau_pt->SetFillStyle(4050);
    h_tau_pt->SetFillColor(kBlue-7);
    h_tau_pt->Draw("HIST");
    h_tau_pt->GetYaxis()->SetRangeUser(0., 0.12);
    h_tau_pt->Draw("E same");

    
    h_mu_pt->SetLineColor(kRed+2);
  //  h_mu_pt->Sumw2();
    h_mu_pt-> SetMarkerStyle (21);
    h_mu_pt-> SetMarkerSize (0.2);
    h_mu_pt->SetFillColor(kRed);
    h_mu_pt->SetFillStyle(3354);
    h_mu_pt->Draw("HIST  E same");
    
    auto legend1 = new TLegend(0.89,0.88,0.77,0.67);
 //   legend1->SetHeader("The Legend Title","C"); // option "C" allows to center the header
    legend1->AddEntry( h_tau_pt,"#tau^{#minus} ","f");
    legend1->AddEntry( h_mu_pt,"e^{#minus} ","f");
    legend1->Draw();

    
 
    
      
    c2->cd();
    h_mu_phi_minus->Scale(norm/h_mu_phi_minus->Integral(), "width");
    h_tau_phi_minus->Scale(norm/h_tau_phi_minus->Integral(), "width");
    
    h_mu_phi_minus->SetLineColor(kBlue+3);
   // h_mu_phi_minus->Sumw2();
    h_mu_phi_minus-> SetMarkerStyle (21);
    h_mu_phi_minus-> SetMarkerSize (0.2);
    h_mu_phi_minus->SetFillStyle(4050);
    h_mu_phi_minus->SetFillColor(kBlue-7);
    h_mu_phi_minus->Draw("HIST");
    h_mu_phi_minus->Draw("E same ");

       
    h_tau_phi_minus->SetLineColor(kRed+2);
   // h_tau_phi_minus->Sumw2();
    h_tau_phi_minus-> SetMarkerStyle (21);
    h_tau_phi_minus-> SetMarkerSize (0.2);
    h_tau_phi_minus->SetFillColor(kRed);
    h_tau_phi_minus->SetFillStyle(3354);
    h_tau_phi_minus->Draw("HIST E same ");
    
    
    auto legend2 = new TLegend(0.89,0.88,0.77,0.67);
    
       legend2->AddEntry( h_tau_pt,"#tau^{#minus} ","f");
       legend2->AddEntry( h_mu_pt,"e^{#minus} ","f");
       legend2->Draw();
    

    c3->cd();
    h_mumet_energy->Scale(norm/h_mumet_energy->Integral(), "width");
    h_taumet_energy->Scale(norm/h_taumet_energy->Integral(), "width");
    
    h_taumet_energy->SetLineColor(kBlue+3);
   // h_taumet_energy->Sumw2();
    h_taumet_energy-> SetMarkerStyle (21);
    h_taumet_energy-> SetMarkerSize (0.2);
    h_taumet_energy->SetFillStyle(4050);
    h_taumet_energy->SetFillColor(kBlue-7);
    h_taumet_energy->GetYaxis()->SetRangeUser(0., 0.070);
    h_taumet_energy->Draw("HIST");
    h_taumet_energy->Draw("E same");
    
    h_mumet_energy->SetLineColor(kRed+2);
   // h_mumet_energy->Sumw2();
    h_mumet_energy->SetMarkerStyle (21);
    h_mumet_energy-> SetMarkerSize (0.2);
    h_mumet_energy->SetFillColor(kRed);
    h_mumet_energy->SetFillStyle(3354);
    h_mumet_energy->Draw("HIST E same ");
    
    auto legend3 = new TLegend(0.89,0.88,0.77,0.67);
       legend3->AddEntry( h_taumet_energy," #bar{#nu}_{#tau}","f");
       legend3->AddEntry( h_mumet_energy," #bar{#nu}_{e}","f");
       legend3->Draw();
    
    c4->cd();
    h_taunu_mt->Scale(norm/h_taunu_mt->Integral(), "width");
    h_munu_mt->Scale(norm/h_munu_mt->Integral(), "width");
    
    
    
    
    h_taunu_mt->SetLineColor(kBlue+3);
   // h_taunu_mt->Sumw2();
    h_taunu_mt-> SetMarkerStyle (21);
    h_taunu_mt-> SetMarkerSize (0.2);
    h_taunu_mt->SetFillStyle(4050);
    h_taunu_mt->SetFillColor(kBlue-7);
    h_taunu_mt->GetYaxis()->SetRangeUser(0., 0.050);
    h_taunu_mt->Draw("HIST");
    h_taunu_mt->Draw("E same");

    
    h_munu_mt->SetLineColor(kRed+2);
   // h_munu_mt->Sumw2();
    h_munu_mt->SetMarkerStyle (21);
    h_munu_mt-> SetMarkerSize (0.2);
    h_munu_mt->SetFillColor(kRed);
    h_munu_mt->SetFillStyle(3354);
    h_munu_mt->Draw("HIST E same ");

   // gPad->BuildLegend(0.9,0.9,0.6,0.50);
    auto legend4 = new TLegend(0.9,0.9,0.6,0.50);
    legend4->AddEntry( h_taunu_mt,"W^{#minus} #rightarrow #tau^{#minus} #plus #bar{#nu}_{#tau} ","f");
    legend4->AddEntry( h_munu_mt,"W^{#minus} #rightarrow e^{#minus} #plus #bar{#nu}_{e} ","f");
    legend4->Draw();
        
     
    c5->cd();
    
    h_tau_phi->Scale(norm/h_tau_phi->Integral(), "width");
    h_mu_phi->Scale(norm/h_mu_phi->Integral(), "width");
    
    
    
    h_tau_phi->SetLineColor(kBlue+3);
   //  h_tau_phi->Sumw2();
     h_tau_phi-> SetMarkerStyle (21);
     h_tau_phi-> SetMarkerSize (0.2);
     h_tau_phi->SetFillStyle(4050);
     h_tau_phi->SetFillColor(kBlue-7);
     h_tau_phi->GetYaxis()->SetRangeUser(0., 0.25);
     h_tau_phi->Draw("HIST");
     h_tau_phi->Draw("E same");

    
    h_mu_phi->SetLineColor(kRed+2);
   // h_mu_phi->Sumw2();
    h_mu_phi->SetMarkerStyle (21);
    h_mu_phi-> SetMarkerSize (0.2);
    h_mu_phi->SetFillColor(kRed);
    h_mu_phi->SetFillStyle(3354);
    h_mu_phi->Draw("HIST E same ");
   
    
    auto legend5 = new TLegend(0.89,0.88,0.77,0.67);
    legend5->AddEntry( h_tau_phi,"#tau^{#minus} ","f");
    legend5->AddEntry( h_mu_phi,"e^{#minus} ","f");
    legend5->Draw();
        
    c6->cd();
    h_taumet_phi->Scale(norm/h_taumet_phi->Integral(), "width");
    h_mumet_phi->Scale(norm/h_mumet_phi->Integral(), "width");
    
    
    
    h_taumet_phi->SetLineColor(kBlue+3);
   //  h_taumet_phi->Sumw2();
     h_taumet_phi-> SetMarkerStyle (21);
     h_taumet_phi-> SetMarkerSize (0.2);
     h_taumet_phi->SetFillStyle(4050);
     h_taumet_phi->SetFillColor(kBlue-7);
     h_taumet_phi->GetYaxis()->SetRangeUser(0., 0.24);
     h_taumet_phi->Draw("HIST");
     h_taumet_phi->Draw("E same");


    
    h_mumet_phi->SetLineColor(kRed+2);
   // h_mumet_phi->Sumw2();
    h_mumet_phi->SetMarkerStyle (21);
    h_mumet_phi-> SetMarkerSize (0.2);
    h_mumet_phi->SetFillColor(kRed);
    h_mumet_phi->SetFillStyle(3354);
    h_mumet_phi->Draw("HIST E same ");
    
    auto legend6 = new TLegend(0.89,0.88,0.77,0.67);
    legend6->AddEntry( h_taumet_phi," #bar{#nu}_{#tau}","f");
    legend6->AddEntry( h_mumet_phi," #bar{#nu}_{e}","f");
    legend6->Draw();
    
    c7->cd();
    h_tau_eta->Scale(norm/h_tau_eta->Integral(), "width");
    h_mu_eta->Scale(norm/h_mu_eta->Integral(), "width");
    
     h_tau_eta->SetLineColor(kBlue+3);
   //  h_tau_eta->Sumw2();
     h_tau_eta-> SetMarkerStyle (21);
     h_tau_eta-> SetMarkerSize (0.2);
     h_tau_eta->SetFillStyle(4050);
     h_tau_eta->SetFillColor(kBlue-7);
     h_tau_eta->GetYaxis()->SetRangeUser(0., 0.43);
     h_tau_eta->Draw("HIST");
     h_tau_eta->Draw("E same");


    
     h_mu_eta->SetLineColor(kRed+2);
 //    h_mu_eta->Sumw2();
     h_mu_eta->SetMarkerStyle (21);
     h_mu_eta-> SetMarkerSize (0.2);
     h_mu_eta->SetFillColor(kRed);
     h_mu_eta->SetFillStyle(3354);
     h_mu_eta->Draw("HIST E same ");
    
    
    auto legend7 = new TLegend(0.89,0.88,0.77,0.67);
       legend7->AddEntry( h_tau_eta,"#tau^{#minus} ","f");
       legend7->AddEntry( h_mu_eta,"e^{#minus} ","f");
       legend7->Draw();


    
    c1->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/lep_eandtau_minus_pt.pdf");
    c2->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/lep_eandtau_minus_l-Emiss.pdf");
    c3->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/met_eandtau_minus.energy.pdf");
    c4->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/eandtau_minus_mt.pdf");
    c5->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/lep_eandtau_minus_phi.pdf");
    c6->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/met_eandtau_minus_phi.pdf");
    c7->SaveAs("/Users/grigorijtolkacev/Desktop/ATLAS/SW/lep_eandtau_minus_eta.pdf");
    
}
