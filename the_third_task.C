//Вашим следующим заданием будет реконструкция поперечной массы W бозона.
//Для этого вам понадобится 4импульс лидирующего лепота (lep_0) и вектор потерянной энергии: формула 6 вот тут [1].
//Покажите в сравнении для e и mu каналов.
void the_third_task()
{
  TFile* f1= new TFile("/Users/grigorijtolkacev/Desktop/ATLAS/21.root", "READ");
  TFile* f2= new TFile("/Users/grigorijtolkacev/Desktop/ATLAS/user.dponomar.17679514._000003.SM_WLepton.root", "READ");
  auto enu = (TTree*)f1->Get("NOMINAL");
  auto munu = (TTree*)f2->Get("NOMINAL");
  TH1F *tmenu = new TH1F("enu", "W #rightarrow e #nu_{e};m_{T} [GeV];Normalized Units", 150, 0, 200);
  TH1F *tmmunu = new TH1F("munu", "W #rightarrow #mu #nu_{#mu};m_{T} [GeV];Normalized Units", 150, 0, 200);
  TCanvas *c = new TCanvas("c","",1000,600);
  gStyle->SetOptTitle(kFALSE);
  gStyle->SetOptStat(0);
    
  tmenu->SetDirectory(gROOT);
  tmmunu->SetDirectory(gROOT);

  TLorentzVector* lep_e = 0;
  TLorentzVector* met_e = 0;
  TLorentzVector* lep_mu = 0;
  TLorentzVector* met_mu = 0;
  enu->SetBranchAddress("lep_0_p4", &lep_e);
  enu->SetBranchAddress("met_reco_p4", &met_e);
  munu->SetBranchAddress("lep_0_p4", &lep_mu);
  munu->SetBranchAddress("met_reco_p4", &met_mu);
    
  Long64_t N = enu->GetEntries();
    
  std::cout<<"N events: "<< N << std::endl;
    
    for (Long64_t i = 0; i < N ; i++) {
      enu->GetEntry(i);
      tmenu->Fill(sqrt(2*lep_e->Pt()*met_e->Pt()*(1-cos(lep_e->Phi()+met_e->Phi()))));
                    }
    Long64_t K = munu->GetEntries();
      std::cout<<"N events: "<< K << std::endl;
        
        for (Long64_t i = 0; i < K ; i++) {
          munu->GetEntry(i);
          tmmunu->Fill(sqrt(2*lep_mu->Pt()*met_mu->Pt()*(1-cos(lep_mu->Phi()+met_mu->Phi()))));
       
        }

         f1->Close();
         f2->Close();
         c->cd();
         Double_t norm = 1;
         tmenu->Scale(norm/tmenu->Integral(), "width");
         tmmunu->Scale(norm/tmmunu->Integral(), "width");
       
         tmmunu->SetLineColor(kRed);
         tmmunu->Draw("HIST");
         tmenu->Draw("HIST same");
         gPad->BuildLegend(1.0,0.8,0.8,0.5,"","");
    
}
