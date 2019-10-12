//По ссылке [1] вы найдете сампл для распада W->mu+nu. Для начала нарисуйте его
//отдельно с помощью готового скрипта. Потом сравните распределения двух каналов
//: нарисуйте кинематические распределения двух каналов одновременно на каждом
//канвасе. Отсортируйте все распределения на единицу (делите на интеграл), что
//бы можно было сравнить их форму. Чтобы было удобно, поменяйте цвет линии одному из каналов. Добавьте на кана
//легенду, которая даст понять значение линий. Зная различия в методике регистрации мюонов и электронов в
//ATLAS, попробуйте объяснить разницу распределений.
void the_second_task()
{
  TFile* f1= new TFile("/Users/grigorijtolkacev/Desktop/ATLAS/21.root", "READ");
  TFile* f2= new TFile("/Users/grigorijtolkacev/Desktop/ATLAS/user.dponomar.17679514._000003.SM_WLepton.root", "READ");

  auto enu = (TTree*)f1->Get("NOMINAL");
  auto munu = (TTree*)f2->Get("NOMINAL");
    
    
  TH1F *enu11 = new TH1F("Pte", "e ;P_{T} [GeV];Entries", 150, -10, 100);
  TH1F *enu12 = new TH1F("Etae", "e ;#eta ;Entries", 150, -3, 3);
  TH1F *enu13 = new TH1F("Phie", "e;#phi ;Entries", 150, -4, 4);
  TH1F *enu14 = new TH1F("Ee", "e;E [GeV];Entries", 150, 0, 400);
  TH1F *enu21 = new TH1F("Ptnue", "#nu_{e};P_{T} [GeV];Entries", 150, -10, 120);
  TH1F *enu23 = new TH1F("Phinue", "#nu_{e};#phi ;Entries", 150, -4, 4);
  TH1F *enu24 = new TH1F("Enue", "#nu_{e};E [GeV];Entries", 150, -10, 300);
  
  TH1F *munu11 = new TH1F("Ptmu", "#mu;P_{T} [GeV];Entries", 150, -10, 100);
  TH1F *munu12 = new TH1F("Etamu", "#mu;#eta ;Entries", 150, -3, 3);
  TH1F *munu13 = new TH1F("Phimu", "#mu;#phi ;Entries", 150, -4, 4);
  TH1F *munu14 = new TH1F("Emu", "#mu;E [GeV];Entries", 150, 0, 400);
  TH1F *munu21 = new TH1F("Ptnumu", "#nu_{#mu};P_{T} [GeV];Entries", 150, -10, 120);
  TH1F *munu23 = new TH1F("Phinumu", "#nu_{#mu};#phi ;Entries", 150, -4, 4);
  TH1F *munu24 = new TH1F("Emunu", "#nu_{#mu};E [GeV];Entries", 150, -10, 300);

  
  TCanvas *c = new TCanvas("c","",1800,1800);
  //gStyle->SetOptTitle(kFALSE);
  //gStyle->SetOptStat(0);
  c->Divide(2,3);
 
  enu11->SetDirectory(gROOT);
  enu12->SetDirectory(gROOT);
  enu13->SetDirectory(gROOT);
  enu14->SetDirectory(gROOT);
  enu21->SetDirectory(gROOT);
  enu23->SetDirectory(gROOT);
  enu24->SetDirectory(gROOT);
  munu11->SetDirectory(gROOT);
  munu12->SetDirectory(gROOT);
  munu13->SetDirectory(gROOT);
  munu14->SetDirectory(gROOT);
  munu21->SetDirectory(gROOT);
  munu23->SetDirectory(gROOT);
  munu24->SetDirectory(gROOT);


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
      enu11->Fill(lep_e->Pt());
      enu12->Fill(lep_e->Eta());
      enu13->Fill(lep_e->Phi());
      enu14->Fill(lep_e->E());
      enu21->Fill(met_e->Pt());
      enu23->Fill(met_e->Phi());
      enu24->Fill(met_e->E());
    }
    
    Long64_t K = munu->GetEntries();
    std::cout<<"N events: "<< K << std::endl;
      
      for (Long64_t i = 0; i < K ; i++) {
        munu->GetEntry(i);
        munu11->Fill(lep_mu->Pt());
        munu12->Fill(lep_mu->Eta());
        munu13->Fill(lep_mu->Phi());
        munu14->Fill(lep_mu->E());
        munu21->Fill(met_mu->Pt());
        munu23->Fill(met_mu->Phi());
        munu24->Fill(met_mu->E());
      }
      
    
  f1->Close();
  f2->Close();
    
    c->cd(1);
    Double_t norm = 1;
    enu11->Scale(norm/enu11->Integral(), "width");
    munu11->Scale(norm/munu11->Integral(), "width");
    enu11->Draw("HIST");
     munu11->Draw("HIST");
    enu11->SetLineColor(kRed);
    enu11->Draw("HIST same");
   
     gPad->BuildLegend(1.0,0.7,0.6,0.9,"","");

    
    c->cd(2);
    enu12->Scale(norm/enu12->Integral(), "width");
    munu12->Scale(norm/munu12->Integral(), "width");
    enu12->Draw("HIST");
    enu12->SetLineColor(kRed);
    munu12->Draw("HIST same");
    gPad->BuildLegend(1.0,0.7,0.6,0.9,"","");

    c->cd(3);
    enu13->Scale(norm/enu13->Integral(), "width");
    munu13->Scale(norm/munu13->Integral(), "width");
    enu13->Draw("HIST");
    enu13->SetLineColor(kRed);
    munu13->Draw("HIST same");
    gPad->BuildLegend(1.0,0.7,0.6,0.9,"","");
    
    c->cd(4);
    enu21->Scale(norm/enu21->Integral(), "width");
    munu21->Scale(norm/munu21->Integral(), "width");
    munu21->Draw("HIST");
    enu21->SetLineColor(kRed);
    enu21->Draw("HIST same");
    
    gPad->BuildLegend(1.0,0.7,0.6,0.9,"","");
    
  

    c->cd(6);
    enu23->Scale(norm/enu23->Integral(), "width");
    munu23->Scale(norm/munu23->Integral(), "width");
    enu23->Draw("HIST");
    enu23->SetLineColor(kRed);
    munu23->Draw("HIST same");
    gPad->BuildLegend(1.0,0.7,0.6,0.9,"","");
    

}
