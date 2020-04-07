void root_homework_TLV(){
TFile* f= new TFile("/Users/grigorijtolkacev/Downloads/MCData16a_345784_aMcAtNloPythia8_NNPDF30NLO_FxFx_nunugamma_pty_140_v5.root", "READ");
    
auto oldtree = (TTree*)f->Get("output_tree");

    
ULong64_t event;
//create TLorentzVector
TLorentzVector gamma;
TLorentzVector met;
TLorentzVector jet1;
TLorentzVector jet2;
    
//gamma
Double_t ph_pt = 0;
Double_t ph_eta = 0;
Double_t ph_phi = 0;

oldtree->SetBranchAddress ( "ph_pt" , &ph_pt);
oldtree->SetBranchAddress ( "ph_eta" , &ph_eta);
oldtree->SetBranchAddress ( "ph_phi" , &ph_phi);
//met
Double_t metTST_pt = 0;
Double_t metTST_phi = 0;
    
oldtree->SetBranchAddress ( "metTST_pt" , &metTST_pt);
oldtree->SetBranchAddress ( "metTST_phi" , &metTST_phi);

//jet1
Double_t jet_lead_pt = 0;
Double_t jet_lead_eta = 0;
Double_t jet_lead_phi = 0;
Double_t jet_lead_E = 0;

oldtree->SetBranchAddress ( "jet_lead_pt" , &jet_lead_pt);
oldtree->SetBranchAddress ( "jet_lead_eta" , &jet_lead_eta);
oldtree->SetBranchAddress ( "jet_lead_phi" , &jet_lead_phi);
oldtree->SetBranchAddress ( "jet_lead_E" , &jet_lead_E);

//jet2
Double_t jet_sublead_pt = 0;
Double_t jet_sublead_eta = 0;
Double_t jet_sublead_phi = 0;
Double_t jet_sublead_E = 0;

oldtree->SetBranchAddress ( "jet_sublead_pt" , &jet_sublead_pt);
oldtree->SetBranchAddress ( "jet_sublead_eta" , &jet_sublead_eta);
oldtree->SetBranchAddress ( "jet_sublead_phi" , &jet_sublead_phi);
oldtree->SetBranchAddress ( "jet_sublead_E" , &jet_sublead_E);
    
//for cuts
UInt_t n_mu = 0;
UInt_t n_e_looseBL = 0;
oldtree->SetBranchAddress ( "n_mu" , &n_mu);
oldtree->SetBranchAddress ( "n_e_looseBL" , &n_e_looseBL);
//create new file
    TFile *f1 = new TFile("/Users/grigorijtolkacev/Desktop/MCData16a_345784_aMcAtNloPythia8_NNPDF30NLO_FxFx_nunugamma_pty_140_v5_withCUTS.root","recreate");
    TTree *newtree = new TTree("tree","Simple Tree");
    newtree->Branch("EventBranch", &event, "EventBranch/I");
    newtree->Branch("met", "TLorentzVector", &met);
    newtree->Branch("jet1", "TLorentzVector", &jet1);
    newtree->Branch("jet2", "TLorentzVector", &jet1);
    
    
    Long64_t N = oldtree->GetEntries();
    std::cout<<"N events: "<< N << std::endl;
    int k=0;
    for (Long64_t i = 0; i < N; i++ ){
        oldtree->GetEntry(i);
        event = i;
        
        
    Double_t metTST_E = fabs(metTST_pt);
        
    gamma.SetPtEtaPhiE(ph_pt,ph_eta,ph_phi,0);
    met.SetPtEtaPhiE(metTST_pt,0,metTST_phi,metTST_E);
        
   // Double_t dPhi = fabs(gamma.Phi() - met.Phi());
   //     
   //     if(dPhi > 3.14159)
   //     {
   //         dPhi = 2*3.14159 - dPhi;
   //     }
        
    Double_t dPhi = fabs(gamma.DeltaPhi(met)); 
        
    if ( !(metTST_pt>150) ) continue;
    if ( !((n_mu+n_e_looseBL) == 0) ) continue;
    if ( !(dPhi>0.4) ) continue;
        
    jet1.SetPtEtaPhiE(jet_lead_pt,jet_lead_eta,jet_lead_phi ,jet_lead_E);
    jet2.SetPtEtaPhiE(jet_sublead_pt, jet_sublead_eta,jet_sublead_phi, jet_sublead_E);
        k+=1;
        newtree->Fill();
    }
     std::cout<<"K events: "<< k << std::endl;
    f->Close();
    newtree->Write();
    
    return 0;
}
