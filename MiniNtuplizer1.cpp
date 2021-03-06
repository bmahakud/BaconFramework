#include "../include/GenLoader.hh"
#include "../include/MuonLoader.hh"
#include "../include/PFLoader.hh"
#include "fastjet/tools/Filter.hh"
#include "fastjet/tools/Pruner.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/JetCleanser.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/tools/GridMedianBackgroundEstimator.hh"
#include "fastjet/tools/JetMedianBackgroundEstimator.hh"
#include "fastjet/tools/Subtractor.hh"
#include "fastjet/contrib/SafeSubtractor.hh"
#include "fastjet/contrib/SoftKiller.hh"
#include "fastjet/contrib/SoftDrop.hh" 
#include "fastjet/contrib/ConstituentSubtractor.hh"
#include "fastjet/Selector.hh"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TMath.h"
#include "BaconAna/DataFormats/interface/TJet.hh"
#include "BaconAna/DataFormats/interface/TEventInfo.hh"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdlib>

using namespace std;
using namespace fastjet;
using namespace contrib;

//Object Processors
GenLoader       *fGen      = 0; 
MuonLoader      *fMuon     = 0; 
PFLoader        *fPFCand   = 0; 

TClonesArray *fJet;
TBranch      *fJetBr;

TTree* load(std::string iName) { 
  TFile *lFile = TFile::Open(iName.c_str());
  TTree *lTree = (TTree*) lFile->FindObjectAny("Events");
  return lTree;
}


struct JetInfo {
  int npu ;
/////////////////////////pt /////
  vector<float> pt;
  vector<float> ptcorr;
  vector<float> ptraw;
  vector<float> ptclean;
  vector<float> pttrim;
  vector<float> pttrimsafe;
  vector<float> ptconst;
  vector<float> ptunc;
  vector<float> pt_tr1;
  vector<float> pt_tr2;
  vector<float> pt_tr3;
  vector<float> pt_tr4;
  vector<float> pt_tr1_safe;
  vector<float> pt_tr2_safe;
  vector<float> pt_tr3_safe;
  vector<float> pt_tr4_safe;
  vector<float> pt_pr1;
  vector<float> pt_pr2;
  vector<float> pt_pr3;
  vector<float> pt_pr4;
  vector<float> pt_pr1_safe;
  vector<float> pt_pr2_safe;
  vector<float> pt_pr3_safe;
  vector<float> pt_pr4_safe;
  vector<float> pt_sd1;
  vector<float> pt_sd2;
  vector<float> pt_sd3;
  vector<float> pt_sd4;
  vector<float> pt_sd5;
  vector<float> pt_sd1_safe;
  vector<float> pt_sd2_safe;
  vector<float> pt_sd3_safe;
  vector<float> pt_sd4_safe;
  vector<float> pt_sd5_safe;
  

  



//////////////////////eta
  vector<float> eta;
  vector<float> eta_tr1;
  vector<float> eta_tr2;
  vector<float> eta_tr3;
  vector<float> eta_tr4;
  vector<float> eta_tr1_safe;
  vector<float> eta_tr2_safe;
  vector<float> eta_tr3_safe;
  vector<float> eta_tr4_safe;
  vector<float> eta_pr1;
  vector<float> eta_pr2;
  vector<float> eta_pr3;
  vector<float> eta_pr4;
  vector<float> eta_pr1_safe;
  vector<float> eta_pr2_safe;
  vector<float> eta_pr3_safe;
  vector<float> eta_pr4_safe;
  vector<float> eta_sd1;
  vector<float> eta_sd2;
  vector<float> eta_sd3;
  vector<float> eta_sd4;
  vector<float> eta_sd5;
  vector<float> eta_sd1_safe;
  vector<float> eta_sd2_safe;
  vector<float> eta_sd3_safe;
  vector<float> eta_sd4_safe;
  vector<float> eta_sd5_safe;


/////////////////////////////////////phi

  vector<float> phi;
  vector<float> phi_tr1;
  vector<float> phi_tr2;
  vector<float> phi_tr3;
  vector<float> phi_tr4;
  vector<float> phi_tr1_safe;
  vector<float> phi_tr2_safe;
  vector<float> phi_tr3_safe;
  vector<float> phi_tr4_safe;
  vector<float> phi_pr1;
  vector<float> phi_pr2;
  vector<float> phi_pr3;
  vector<float> phi_pr4;
  vector<float> phi_pr1_safe;
  vector<float> phi_pr2_safe;
  vector<float> phi_pr3_safe;
  vector<float> phi_pr4_safe;
  vector<float> phi_sd1;
  vector<float> phi_sd2;
  vector<float> phi_sd3;
  vector<float> phi_sd4;
  vector<float> phi_sd5;
  vector<float> phi_sd1_safe;
  vector<float> phi_sd2_safe;
  vector<float> phi_sd3_safe;
  vector<float> phi_sd4_safe;
  vector<float> phi_sd5_safe;
  


  
  vector<float> m;
  vector<float> mass_tr1;
  vector<float> mass_tr2;
  vector<float> mass_tr3;
  vector<float> mass_tr4;
  vector<float> mass_tr1_safe;
  vector<float> mass_tr2_safe;
  vector<float> mass_tr3_safe;
  vector<float> mass_tr4_safe;
  vector<float> mass_pr1;
  vector<float> mass_pr2;
  vector<float> mass_pr3;
  vector<float> mass_pr4;
  vector<float> mass_pr1_safe;
  vector<float> mass_pr2_safe;
  vector<float> mass_pr3_safe;
  vector<float> mass_pr4_safe;
  vector<float> mass_sd1;
  vector<float> mass_sd2;
  vector<float> mass_sd3;
  vector<float> mass_sd4;
  vector<float> mass_sd5;
  vector<float> mass_sd1_safe;
  vector<float> mass_sd2_safe;
  vector<float> mass_sd3_safe;
  vector<float> mass_sd4_safe;
  vector<float> mass_sd5_safe;





  vector<float> mraw;
  vector<float> mclean;
  vector<float> mpruned;
  vector<float> mprunedsafe;
  vector<float> mtrim;
  vector<float> mtrimsafe;
  vector<float> msoftdrop;
  vector<float> msoftdropsafe;
  vector<float> mconst;
  vector<int>   nparticles;
  vector<int>   nneutrals;
  vector<int>   ncharged;

  // gen level info
  vector<float> ptgen;
   vector<float> pt_tr1_gen;
  vector<float> pt_tr2_gen;
  vector<float> pt_tr3_gen;
  vector<float> pt_tr4_gen;
  vector<float> pt_tr1_safe_gen;
  vector<float> pt_tr2_safe_gen;
  vector<float> pt_tr3_safe_gen;
  vector<float> pt_tr4_safe_gen;
  vector<float> pt_pr1_gen;
  vector<float> pt_pr2_gen;
  vector<float> pt_pr3_gen;
  vector<float> pt_pr4_gen;
  vector<float> pt_pr1_safe_gen;
  vector<float> pt_pr2_safe_gen;
  vector<float> pt_pr3_safe_gen;
  vector<float> pt_pr4_safe_gen;
  vector<float> pt_sd1_gen;
  vector<float> pt_sd2_gen;
  vector<float> pt_sd3_gen;
  vector<float> pt_sd4_gen;
  vector<float> pt_sd5_gen;
  vector<float> pt_sd1_safe_gen;
  vector<float> pt_sd2_safe_gen;
  vector<float> pt_sd3_safe_gen; 
  vector<float> pt_sd4_safe_gen;
  vector<float> pt_sd5_safe_gen; 



  vector<float> etagen;
  vector<float> eta_tr1_gen;
  vector<float> eta_tr2_gen;
  vector<float> eta_tr3_gen;
  vector<float> eta_tr4_gen;
  vector<float> eta_tr1_safe_gen;
  vector<float> eta_tr2_safe_gen;
  vector<float> eta_tr3_safe_gen;
  vector<float> eta_tr4_safe_gen;
  vector<float> eta_pr1_gen;
  vector<float> eta_pr2_gen;
  vector<float> eta_pr3_gen;
  vector<float> eta_pr4_gen;
  vector<float> eta_pr1_safe_gen;
  vector<float> eta_pr2_safe_gen;
  vector<float> eta_pr3_safe_gen;
  vector<float> eta_pr4_safe_gen;
  vector<float> eta_sd1_gen;
  vector<float> eta_sd2_gen;
  vector<float> eta_sd3_gen;
  vector<float> eta_sd4_gen;
  vector<float> eta_sd5_gen;
  vector<float> eta_sd1_safe_gen;
  vector<float> eta_sd2_safe_gen;
  vector<float> eta_sd3_safe_gen;
  vector<float> eta_sd4_safe_gen;
   vector<float> eta_sd5_safe_gen;






  vector<float> phigen;
  vector<float> phi_tr1_gen;
  vector<float> phi_tr2_gen;
  vector<float> phi_tr3_gen;
  vector<float> phi_tr4_gen;
  vector<float> phi_tr1_safe_gen;
  vector<float> phi_tr2_safe_gen;
  vector<float> phi_tr3_safe_gen;
  vector<float> phi_tr4_safe_gen;
  vector<float> phi_pr1_gen;
  vector<float> phi_pr2_gen;
  vector<float> phi_pr3_gen;
  vector<float> phi_pr4_gen;
  vector<float> phi_pr1_safe_gen;
  vector<float> phi_pr2_safe_gen;
  vector<float> phi_pr3_safe_gen;
  vector<float> phi_pr4_safe_gen;
  vector<float> phi_sd1_gen;
  vector<float> phi_sd2_gen;
  vector<float> phi_sd3_gen;
  vector<float> phi_sd4_gen;
  vector<float> phi_sd5_gen;
  vector<float> phi_sd1_safe_gen;
  vector<float> phi_sd2_safe_gen;
  vector<float> phi_sd3_safe_gen;
  vector<float> phi_sd4_safe_gen;
  vector<float> phi_sd5_safe_gen;



  vector<float> mgen;
  vector<float> mass_tr1_gen;
  vector<float> mass_tr2_gen;
  vector<float> mass_tr3_gen;
  vector<float> mass_tr4_gen;
  vector<float> mass_tr1_safe_gen;
  vector<float> mass_tr2_safe_gen;
  vector<float> mass_tr3_safe_gen;
  vector<float> mass_tr4_safe_gen;
  vector<float> mass_pr1_gen;
  vector<float> mass_pr2_gen;
  vector<float> mass_pr3_gen;
  vector<float> mass_pr4_gen;
  vector<float> mass_pr1_safe_gen;
  vector<float> mass_pr2_safe_gen;
  vector<float> mass_pr3_safe_gen;
  vector<float> mass_pr4_safe_gen;
  vector<float> mass_sd1_gen;
  vector<float> mass_sd2_gen;
  vector<float> mass_sd3_gen;
  vector<float> mass_sd4_gen;
  vector<float> mass_sd5_gen;
  vector<float> mass_sd1_safe_gen;
  vector<float> mass_sd2_safe_gen;
  vector<float> mass_sd3_safe_gen;
  vector<float> mass_sd4_safe_gen;
  vector<float> mass_sd5_safe_gen;




  vector<float> mrawgen;
  vector<float> mtrimgen;
  vector<float> mtrimsafegen;
  vector<float> mcleangen; //needed?
  vector<float> mconstgen;//needed?
  vector<int>   imatch;
};


void getConstitsForCleansing(vector<PseudoJet> inputs, vector<PseudoJet> &oNeutrals, vector<PseudoJet> &oChargedLV, vector<PseudoJet> &oChargedPU){
  for (unsigned int i = 0; i < inputs.size(); i++){
    if (inputs[i].user_index() <= 1) oNeutrals.push_back(inputs[i]);
    if (inputs[i].user_index() == 2) oChargedLV.push_back(inputs[i]);
    if (inputs[i].user_index() == 3) oChargedPU.push_back(inputs[i]);
  }
}


class SW_IsPupCharged : public SelectorWorker {
public:
  SW_IsPupCharged(){}
  virtual bool pass(const PseudoJet & jet) const {
    return (jet.user_index() > 1);
  }
};

Selector SelectorIsPupCharged(){
  return Selector(new SW_IsPupCharged());
}


class SW_IsPupVertex : public SelectorWorker {
public:
  SW_IsPupVertex(){}
  virtual bool pass(const PseudoJet & jet) const {
    return (jet.user_index() == 2);
  }
};


Selector SelectorIsPupVertex(){
  return Selector(new SW_IsPupVertex());
}


double correction( PseudoJet &iJet,FactorizedJetCorrector *iJetCorr,double iRho) { 
  iJetCorr->setJetPt (iJet.pt());
  iJetCorr->setJetEta(iJet.eta());
  iJetCorr->setJetPhi(iJet.phi());
  iJetCorr->setJetE  (iJet.e());
  iJetCorr->setJetA  (iJet.area());
  iJetCorr->setRho(iRho);
  iJetCorr->setJetEMF(-99.0);
  double jetcorr= iJetCorr->getCorrection();
  return jetcorr;
}


double unc( PseudoJet &iJet,JetCorrectionUncertainty *iJetUnc) { 
  if(fabs(iJet.eta()) > 5. || fabs(iJet.pt()) < 10.) return 1.;
  iJetUnc->setJetPt ( iJet.pt()  );
  iJetUnc->setJetEta( iJet.eta() );
  double jetunc = iJetUnc->getUncertainty(true);
  return jetunc;
}


int matchingIndex(PseudoJet jet, vector<PseudoJet> genjets) {
  float rmin = 9999.;  
  int imatch = -1;
  for(unsigned int i = 0; i < genjets.size(); i++) {
    float rtemp = jet.delta_R(genjets[i]);
    if ( rtemp > 0.3 ) continue;
    if ( rtemp < rmin ){
      rmin =  rtemp;
      imatch = i;
    }
  }
  return (imatch);  
}



int matchingIndexFromJetInfo(PseudoJet jet, JetInfo jetInfo) {
  float rmin = 9999.;  
  int imatch = -1;
  for(unsigned int i = 0; i < (jetInfo.eta).size(); i++) {
    double dEta = fabs(jet.eta() - (jetInfo.eta)[i]);
    double dPhi = fabs(jet.phi() - (jetInfo.phi)[i]);
    if(dPhi > 2.*TMath::Pi()-dPhi) dPhi =  2.*TMath::Pi()-dPhi;
    float rtemp = sqrt(dEta*dEta+dPhi*dPhi);
    if ( rtemp > 0.3 ) continue;
    if ( rtemp < rmin ){
      rmin =  rtemp;
      imatch = i;
    }
  }
  return (imatch);  
}




void setupTree(TTree *iTree, JetInfo &iJet, std::string iName) {
  iTree->Branch((iName+"npu"       ).c_str(),&iJet.npu       );
  iTree->Branch((iName+"pt"        ).c_str(),&iJet.pt        );
  iTree->Branch((iName+"pt_tr1"        ).c_str(),&iJet.pt_tr1 );
  iTree->Branch((iName+"pt_tr2"        ).c_str(),&iJet.pt_tr2 );
  iTree->Branch((iName+"pt_tr3"        ).c_str(),&iJet.pt_tr3 );
  iTree->Branch((iName+"pt_tr4"        ).c_str(),&iJet.pt_tr4 );
  iTree->Branch((iName+"pt_tr1_safe"        ).c_str(),&iJet.pt_tr1_safe );
  iTree->Branch((iName+"pt_tr2_safe"        ).c_str(),&iJet.pt_tr2_safe );
  iTree->Branch((iName+"pt_tr3_safe"        ).c_str(),&iJet.pt_tr3_safe );
  iTree->Branch((iName+"pt_tr4_safe"        ).c_str(),&iJet.pt_tr4_safe );
  iTree->Branch((iName+"pt_pr1"        ).c_str(),&iJet.pt_pr1 );
  iTree->Branch((iName+"pt_pr2"        ).c_str(),&iJet.pt_pr2 );
  iTree->Branch((iName+"pt_pr3"        ).c_str(),&iJet.pt_pr3 );
  iTree->Branch((iName+"pt_pr4"        ).c_str(),&iJet.pt_pr4 );
  iTree->Branch((iName+"pt_pr1_safe"        ).c_str(),&iJet.pt_pr1_safe );
  iTree->Branch((iName+"pt_pr2_safe"        ).c_str(),&iJet.pt_pr2_safe );
  iTree->Branch((iName+"pt_pr3_safe"        ).c_str(),&iJet.pt_pr3_safe );
  iTree->Branch((iName+"pt_pr4_safe"        ).c_str(),&iJet.pt_pr4_safe );
  iTree->Branch((iName+"pt_sd1_safe"        ).c_str(),&iJet.pt_sd1_safe );
  iTree->Branch((iName+"pt_sd2_safe"        ).c_str(),&iJet.pt_sd2_safe );
  iTree->Branch((iName+"pt_sd3_safe"        ).c_str(),&iJet.pt_sd3_safe );
  iTree->Branch((iName+"pt_sd4_safe"        ).c_str(),&iJet.pt_sd4_safe );
  iTree->Branch((iName+"pt_sd5_safe"        ).c_str(),&iJet.pt_sd5_safe );
  iTree->Branch((iName+"pt_sd1"        ).c_str(),&iJet.pt_sd1 );
  iTree->Branch((iName+"pt_sd2"        ).c_str(),&iJet.pt_sd2 );
  iTree->Branch((iName+"pt_sd3"        ).c_str(),&iJet.pt_sd3 );
  iTree->Branch((iName+"pt_sd4"        ).c_str(),&iJet.pt_sd4 );
  iTree->Branch((iName+"pt_sd5"        ).c_str(),&iJet.pt_sd5 );

  
  iTree->Branch((iName+"ptcorr"    ).c_str(),&iJet.ptcorr    );
  iTree->Branch((iName+"ptraw"     ).c_str(),&iJet.ptraw     );
  iTree->Branch((iName+"ptclean"   ).c_str(),&iJet.ptclean   );
  iTree->Branch((iName+"pttrim"    ).c_str(),&iJet.pttrim    );
  iTree->Branch((iName+"pttrimsafe").c_str(),&iJet.pttrimsafe);
  iTree->Branch((iName+"ptconst"   ).c_str(),&iJet.ptconst   );
  iTree->Branch((iName+"ptunc"     ).c_str(),&iJet.ptunc     );
    

  iTree->Branch((iName+"eta"       ).c_str(),&iJet.eta       );



  iTree->Branch((iName+"eta_tr1"        ).c_str(),&iJet.eta_tr1 );
  iTree->Branch((iName+"eta_tr2"        ).c_str(),&iJet.eta_tr2 );
  iTree->Branch((iName+"eta_tr3"        ).c_str(),&iJet.eta_tr3 );
  iTree->Branch((iName+"eta_tr4"        ).c_str(),&iJet.eta_tr4 );
  iTree->Branch((iName+"eta_tr1_safe"        ).c_str(),&iJet.eta_tr1_safe );
  iTree->Branch((iName+"eta_tr2_safe"        ).c_str(),&iJet.eta_tr2_safe );
  iTree->Branch((iName+"eta_tr3_safe"        ).c_str(),&iJet.eta_tr3_safe );
  iTree->Branch((iName+"eta_tr4_safe"        ).c_str(),&iJet.eta_tr4_safe );
  iTree->Branch((iName+"eta_pr1"        ).c_str(),&iJet.eta_pr1 );
  iTree->Branch((iName+"eta_pr2"        ).c_str(),&iJet.eta_pr2 );
  iTree->Branch((iName+"eta_pr3"        ).c_str(),&iJet.eta_pr3 );
  iTree->Branch((iName+"eta_pr4"        ).c_str(),&iJet.eta_pr4 );
  iTree->Branch((iName+"eta_pr1_safe"        ).c_str(),&iJet.eta_pr1_safe );
  iTree->Branch((iName+"eta_pr2_safe"        ).c_str(),&iJet.eta_pr2_safe );
  iTree->Branch((iName+"eta_pr3_safe"        ).c_str(),&iJet.eta_pr3_safe );
  iTree->Branch((iName+"eta_pr4_safe"        ).c_str(),&iJet.eta_pr4_safe );
  iTree->Branch((iName+"eta_sd1_safe"        ).c_str(),&iJet.eta_sd1_safe );
  iTree->Branch((iName+"eta_sd2_safe"        ).c_str(),&iJet.eta_sd2_safe );
  iTree->Branch((iName+"eta_sd3_safe"        ).c_str(),&iJet.eta_sd3_safe );
  iTree->Branch((iName+"eta_sd4_safe"        ).c_str(),&iJet.eta_sd4_safe );
  iTree->Branch((iName+"eta_sd5_safe"        ).c_str(),&iJet.eta_sd5_safe );
  iTree->Branch((iName+"eta_sd1"        ).c_str(),&iJet.eta_sd1 );
  iTree->Branch((iName+"eta_sd2"        ).c_str(),&iJet.eta_sd2 );
  iTree->Branch((iName+"eta_sd3"        ).c_str(),&iJet.eta_sd3 );
  iTree->Branch((iName+"eta_sd4"        ).c_str(),&iJet.eta_sd4 );
  iTree->Branch((iName+"eta_sd5"        ).c_str(),&iJet.eta_sd5 );



  iTree->Branch((iName+"phi"       ).c_str(),&iJet.phi       );
 

 iTree->Branch((iName+"phi_tr1"        ).c_str(),&iJet.phi_tr1 );
  iTree->Branch((iName+"phi_tr2"        ).c_str(),&iJet.phi_tr2 );
  iTree->Branch((iName+"phi_tr3"        ).c_str(),&iJet.phi_tr3 );
  iTree->Branch((iName+"phi_tr4"        ).c_str(),&iJet.phi_tr4 );
  iTree->Branch((iName+"phi_tr1_safe"        ).c_str(),&iJet.phi_tr1_safe );
  iTree->Branch((iName+"phi_tr2_safe"        ).c_str(),&iJet.phi_tr2_safe );
  iTree->Branch((iName+"phi_tr3_safe"        ).c_str(),&iJet.phi_tr3_safe );
  iTree->Branch((iName+"phi_tr4_safe"        ).c_str(),&iJet.phi_tr4_safe );
  iTree->Branch((iName+"phi_pr1"        ).c_str(),&iJet.phi_pr1 );
  iTree->Branch((iName+"phi_pr2"        ).c_str(),&iJet.phi_pr2 );
  iTree->Branch((iName+"phi_pr3"        ).c_str(),&iJet.phi_pr3 );
  iTree->Branch((iName+"phi_pr4"        ).c_str(),&iJet.phi_pr4 );
  iTree->Branch((iName+"phi_pr1_safe"        ).c_str(),&iJet.phi_pr1_safe );
  iTree->Branch((iName+"phi_pr2_safe"        ).c_str(),&iJet.phi_pr2_safe );
  iTree->Branch((iName+"phi_pr3_safe"        ).c_str(),&iJet.phi_pr3_safe );
  iTree->Branch((iName+"phi_pr4_safe"        ).c_str(),&iJet.phi_pr4_safe );
  iTree->Branch((iName+"phi_sd1_safe"        ).c_str(),&iJet.phi_sd1_safe );
  iTree->Branch((iName+"phi_sd2_safe"        ).c_str(),&iJet.phi_sd2_safe );
  iTree->Branch((iName+"phi_sd3_safe"        ).c_str(),&iJet.phi_sd3_safe );
  iTree->Branch((iName+"phi_sd4_safe"        ).c_str(),&iJet.phi_sd4_safe );
  iTree->Branch((iName+"phi_sd5_safe"        ).c_str(),&iJet.phi_sd5_safe );
  iTree->Branch((iName+"phi_sd1"        ).c_str(),&iJet.phi_sd1 );
  iTree->Branch((iName+"phi_sd2"        ).c_str(),&iJet.phi_sd2 );
  iTree->Branch((iName+"phi_sd3"        ).c_str(),&iJet.phi_sd3 );
  iTree->Branch((iName+"phi_sd4"        ).c_str(),&iJet.phi_sd4 );
  iTree->Branch((iName+"phi_sd5"        ).c_str(),&iJet.phi_sd5 );

  iTree->Branch((iName+"m"         ).c_str(),&iJet.m         );
  iTree->Branch((iName+"mass_tr1"        ).c_str(),&iJet.mass_tr1 );
  iTree->Branch((iName+"mass_tr2"        ).c_str(),&iJet.mass_tr2 );
  iTree->Branch((iName+"mass_tr3"        ).c_str(),&iJet.mass_tr3 );
  iTree->Branch((iName+"mass_tr4"        ).c_str(),&iJet.mass_tr4 );
  iTree->Branch((iName+"mass_tr1_safe"        ).c_str(),&iJet.mass_tr1_safe );
  iTree->Branch((iName+"mass_tr2_safe"        ).c_str(),&iJet.mass_tr2_safe );
  iTree->Branch((iName+"mass_tr3_safe"        ).c_str(),&iJet.mass_tr3_safe );
  iTree->Branch((iName+"mass_tr4_safe"        ).c_str(),&iJet.mass_tr4_safe );
  iTree->Branch((iName+"mass_pr1"        ).c_str(),&iJet.mass_pr1 );
  iTree->Branch((iName+"mass_pr2"        ).c_str(),&iJet.mass_pr2 );
  iTree->Branch((iName+"mass_pr3"        ).c_str(),&iJet.mass_pr3 );
  iTree->Branch((iName+"mass_pr4"        ).c_str(),&iJet.mass_pr4 );
  iTree->Branch((iName+"mass_pr1_safe"        ).c_str(),&iJet.mass_pr1_safe );
  iTree->Branch((iName+"mass_pr2_safe"        ).c_str(),&iJet.mass_pr2_safe );
  iTree->Branch((iName+"mass_pr3_safe"        ).c_str(),&iJet.mass_pr3_safe );
  iTree->Branch((iName+"mass_pr4_safe"        ).c_str(),&iJet.mass_pr4_safe );
  iTree->Branch((iName+"mass_sd1_safe"        ).c_str(),&iJet.mass_sd1_safe );
  iTree->Branch((iName+"mass_sd2_safe"        ).c_str(),&iJet.mass_sd2_safe );
  iTree->Branch((iName+"mass_sd3_safe"        ).c_str(),&iJet.mass_sd3_safe );
  iTree->Branch((iName+"mass_sd4_safe"        ).c_str(),&iJet.mass_sd4_safe );
  iTree->Branch((iName+"mass_sd5_safe"        ).c_str(),&iJet.mass_sd5_safe );
  iTree->Branch((iName+"mass_sd1"        ).c_str(),&iJet.mass_sd1 );
  iTree->Branch((iName+"mass_sd2"        ).c_str(),&iJet.mass_sd2 );
  iTree->Branch((iName+"mass_sd3"        ).c_str(),&iJet.mass_sd3 );
  iTree->Branch((iName+"mass_sd4"        ).c_str(),&iJet.mass_sd4 );
  iTree->Branch((iName+"mass_sd5"        ).c_str(),&iJet.mass_sd5 );



  iTree->Branch((iName+"mraw"      ).c_str(),&iJet.mraw      );
  iTree->Branch((iName+"mtrim"     ).c_str(),&iJet.mtrim     );
  iTree->Branch((iName+"mtrimsafe" ).c_str(),&iJet.mtrimsafe );
  iTree->Branch((iName+"mpruned" ).c_str(),&iJet.mpruned );
  iTree->Branch((iName+"mprunedsafe" ).c_str(),&iJet.mprunedsafe );
  iTree->Branch((iName+"msoftdrop" ).c_str(),&iJet.msoftdrop);
  iTree->Branch((iName+"msoftdropsafe" ).c_str(),&iJet.msoftdropsafe);
  iTree->Branch((iName+"mclean"    ).c_str(),&iJet.mclean    );
  iTree->Branch((iName+"mconst"    ).c_str(),&iJet.mconst    );
  iTree->Branch((iName+"nparticles").c_str(),&iJet.nparticles);
  iTree->Branch((iName+"nneutrals" ).c_str(),&iJet.nneutrals);
  iTree->Branch((iName+"ncharged"  ).c_str(),&iJet.ncharged);
  // gen info
  iTree->Branch((iName+"ptgen"       ).c_str(),&iJet.ptgen       );
  iTree->Branch((iName+"pt_tr1_gen"        ).c_str(),&iJet.pt_tr1_gen );
  iTree->Branch((iName+"pt_tr2_gen"        ).c_str(),&iJet.pt_tr2_gen );
  iTree->Branch((iName+"pt_tr3_gen"        ).c_str(),&iJet.pt_tr3_gen );
  iTree->Branch((iName+"pt_tr4_gen"        ).c_str(),&iJet.pt_tr4_gen );
  iTree->Branch((iName+"pt_tr1_safe_gen"        ).c_str(),&iJet.pt_tr1_safe_gen );
  iTree->Branch((iName+"pt_tr2_safe_gen"        ).c_str(),&iJet.pt_tr2_safe_gen );
  iTree->Branch((iName+"pt_tr3_safe_gen"        ).c_str(),&iJet.pt_tr3_safe_gen );
  iTree->Branch((iName+"pt_tr4_safe_gen"        ).c_str(),&iJet.pt_tr4_safe_gen );
  iTree->Branch((iName+"pt_pr1_gen"        ).c_str(),&iJet.pt_pr1_gen );
  iTree->Branch((iName+"pt_pr2_gen"        ).c_str(),&iJet.pt_pr2_gen );
  iTree->Branch((iName+"pt_pr3_gen"        ).c_str(),&iJet.pt_pr3_gen );
  iTree->Branch((iName+"pt_pr4_gen"        ).c_str(),&iJet.pt_pr4_gen );
  iTree->Branch((iName+"pt_pr1_safe_gen"        ).c_str(),&iJet.pt_pr1_safe_gen );
  iTree->Branch((iName+"pt_pr2_safe_gen"        ).c_str(),&iJet.pt_pr2_safe_gen );
  iTree->Branch((iName+"pt_pr3_safe_gen"        ).c_str(),&iJet.pt_pr3_safe_gen );
  iTree->Branch((iName+"pt_pr4_safe_gen"        ).c_str(),&iJet.pt_pr4_safe_gen );
  iTree->Branch((iName+"pt_sd1_safe_gen"        ).c_str(),&iJet.pt_sd1_safe_gen );
  iTree->Branch((iName+"pt_sd2_safe_gen"        ).c_str(),&iJet.pt_sd2_safe_gen );
  iTree->Branch((iName+"pt_sd3_safe_gen"        ).c_str(),&iJet.pt_sd3_safe_gen );
  iTree->Branch((iName+"pt_sd4_safe_gen"        ).c_str(),&iJet.pt_sd4_safe_gen );
  iTree->Branch((iName+"pt_sd5_safe_gen"        ).c_str(),&iJet.pt_sd5_safe_gen );
  iTree->Branch((iName+"pt_sd1_gen"        ).c_str(),&iJet.pt_sd1_gen );
  iTree->Branch((iName+"pt_sd2_gen"        ).c_str(),&iJet.pt_sd2_gen );
  iTree->Branch((iName+"pt_sd3_gen"        ).c_str(),&iJet.pt_sd3_gen );
  iTree->Branch((iName+"pt_sd4_gen"        ).c_str(),&iJet.pt_sd4_gen );
  iTree->Branch((iName+"pt_sd5_gen"        ).c_str(),&iJet.pt_sd5_gen );



  iTree->Branch((iName+"etagen"      ).c_str(),&iJet.etagen      );


  iTree->Branch((iName+"eta_tr1_gen"        ).c_str(),&iJet.eta_tr1_gen );
  iTree->Branch((iName+"eta_tr2_gen"        ).c_str(),&iJet.eta_tr2_gen );
  iTree->Branch((iName+"eta_tr3_gen"        ).c_str(),&iJet.eta_tr3_gen );
  iTree->Branch((iName+"eta_tr4_gen"        ).c_str(),&iJet.eta_tr4_gen );
  iTree->Branch((iName+"eta_tr1_safe_gen"        ).c_str(),&iJet.eta_tr1_safe_gen );
  iTree->Branch((iName+"eta_tr2_safe_gen"        ).c_str(),&iJet.eta_tr2_safe_gen );
  iTree->Branch((iName+"eta_tr3_safe_gen"        ).c_str(),&iJet.eta_tr3_safe_gen );
  iTree->Branch((iName+"eta_tr4_safe_gen"        ).c_str(),&iJet.eta_tr4_safe_gen );
  iTree->Branch((iName+"eta_pr1_gen"        ).c_str(),&iJet.eta_pr1_gen );
  iTree->Branch((iName+"eta_pr2_gen"        ).c_str(),&iJet.eta_pr2_gen );
  iTree->Branch((iName+"eta_pr3_gen"        ).c_str(),&iJet.eta_pr3_gen );
  iTree->Branch((iName+"eta_pr4_gen"        ).c_str(),&iJet.eta_pr4_gen );
  iTree->Branch((iName+"eta_pr1_safe_gen"        ).c_str(),&iJet.eta_pr1_safe_gen );
  iTree->Branch((iName+"eta_pr2_safe_gen"        ).c_str(),&iJet.eta_pr2_safe_gen );
  iTree->Branch((iName+"eta_pr3_safe_gen"        ).c_str(),&iJet.eta_pr3_safe_gen );
  iTree->Branch((iName+"eta_pr4_safe_gen"        ).c_str(),&iJet.eta_pr4_safe_gen );
  iTree->Branch((iName+"eta_sd1_safe_gen"        ).c_str(),&iJet.eta_sd1_safe_gen );
  iTree->Branch((iName+"eta_sd2_safe_gen"        ).c_str(),&iJet.eta_sd2_safe_gen );
  iTree->Branch((iName+"eta_sd3_safe_gen"        ).c_str(),&iJet.eta_sd3_safe_gen );
  iTree->Branch((iName+"eta_sd4_safe_gen"        ).c_str(),&iJet.eta_sd4_safe_gen );
  iTree->Branch((iName+"eta_sd5_safe_gen"        ).c_str(),&iJet.eta_sd5_safe_gen );
  iTree->Branch((iName+"eta_sd1_gen"        ).c_str(),&iJet.eta_sd1_gen );
  iTree->Branch((iName+"eta_sd2_gen"        ).c_str(),&iJet.eta_sd2_gen );
  iTree->Branch((iName+"eta_sd3_gen"        ).c_str(),&iJet.eta_sd3_gen );
  iTree->Branch((iName+"eta_sd4_gen"        ).c_str(),&iJet.eta_sd4_gen );
  iTree->Branch((iName+"eta_sd5_gen"        ).c_str(),&iJet.eta_sd5_gen );

  iTree->Branch((iName+"phigen"      ).c_str(),&iJet.phigen      );


  iTree->Branch((iName+"phi_tr1_gen"        ).c_str(),&iJet.phi_tr1_gen );
  iTree->Branch((iName+"phi_tr2_gen"        ).c_str(),&iJet.phi_tr2_gen );
  iTree->Branch((iName+"phi_tr3_gen"        ).c_str(),&iJet.phi_tr3_gen );
  iTree->Branch((iName+"phi_tr4_gen"        ).c_str(),&iJet.phi_tr4_gen );
  iTree->Branch((iName+"phi_tr1_safe_gen"        ).c_str(),&iJet.phi_tr1_safe_gen );
  iTree->Branch((iName+"phi_tr2_safe_gen"        ).c_str(),&iJet.phi_tr2_safe_gen );
  iTree->Branch((iName+"phi_tr3_safe_gen"        ).c_str(),&iJet.phi_tr3_safe_gen );
  iTree->Branch((iName+"phi_tr4_safe_gen"        ).c_str(),&iJet.phi_tr4_safe_gen );
  iTree->Branch((iName+"phi_pr1_gen"        ).c_str(),&iJet.phi_pr1_gen );
  iTree->Branch((iName+"phi_pr2_gen"        ).c_str(),&iJet.phi_pr2_gen );
  iTree->Branch((iName+"phi_pr3_gen"        ).c_str(),&iJet.phi_pr3_gen );
  iTree->Branch((iName+"phi_pr4_gen"        ).c_str(),&iJet.phi_pr4_gen );
  iTree->Branch((iName+"phi_pr1_safe_gen"        ).c_str(),&iJet.phi_pr1_safe_gen );
  iTree->Branch((iName+"phi_pr2_safe_gen"        ).c_str(),&iJet.phi_pr2_safe_gen );
  iTree->Branch((iName+"phi_pr3_safe_gen"        ).c_str(),&iJet.phi_pr3_safe_gen );
  iTree->Branch((iName+"phi_pr4_safe_gen"        ).c_str(),&iJet.phi_pr4_safe_gen );
  iTree->Branch((iName+"phi_sd1_safe_gen"        ).c_str(),&iJet.phi_sd1_safe_gen );
  iTree->Branch((iName+"phi_sd2_safe_gen"        ).c_str(),&iJet.phi_sd2_safe_gen );
  iTree->Branch((iName+"phi_sd3_safe_gen"        ).c_str(),&iJet.phi_sd3_safe_gen );
  iTree->Branch((iName+"phi_sd4_safe_gen"        ).c_str(),&iJet.phi_sd4_safe_gen );
  iTree->Branch((iName+"phi_sd5_safe_gen"        ).c_str(),&iJet.phi_sd5_safe_gen );
  iTree->Branch((iName+"phi_sd1_gen"        ).c_str(),&iJet.phi_sd1_gen );
  iTree->Branch((iName+"phi_sd2_gen"        ).c_str(),&iJet.phi_sd2_gen );
  iTree->Branch((iName+"phi_sd3_gen"        ).c_str(),&iJet.phi_sd3_gen );
  iTree->Branch((iName+"phi_sd4_gen"        ).c_str(),&iJet.phi_sd4_gen );
  iTree->Branch((iName+"phi_sd5_gen"        ).c_str(),&iJet.phi_sd5_gen );


  iTree->Branch((iName+"mgen"        ).c_str(),&iJet.mgen        );
  iTree->Branch((iName+"mass_tr1_gen"        ).c_str(),&iJet.mass_tr1_gen );
  iTree->Branch((iName+"mass_tr2_gen"        ).c_str(),&iJet.mass_tr2_gen );
  iTree->Branch((iName+"mass_tr3_gen"        ).c_str(),&iJet.mass_tr3_gen );
  iTree->Branch((iName+"mass_tr4_gen"        ).c_str(),&iJet.mass_tr4_gen );
  iTree->Branch((iName+"mass_tr1_safe_gen"        ).c_str(),&iJet.mass_tr1_safe_gen );
  iTree->Branch((iName+"mass_tr2_safe_gen"        ).c_str(),&iJet.mass_tr2_safe_gen );
  iTree->Branch((iName+"mass_tr3_safe_gen"        ).c_str(),&iJet.mass_tr3_safe_gen );
  iTree->Branch((iName+"mass_tr4_safe_gen"        ).c_str(),&iJet.mass_tr4_safe_gen );
  iTree->Branch((iName+"mass_pr1_gen"        ).c_str(),&iJet.mass_pr1_gen );
  iTree->Branch((iName+"mass_pr2_gen"        ).c_str(),&iJet.mass_pr2_gen );
  iTree->Branch((iName+"mass_pr3_gen"        ).c_str(),&iJet.mass_pr3_gen );
  iTree->Branch((iName+"mass_pr4_gen"        ).c_str(),&iJet.mass_pr4_gen );
  iTree->Branch((iName+"mass_pr1_safe_gen"        ).c_str(),&iJet.mass_pr1_safe_gen );
  iTree->Branch((iName+"mass_pr2_safe_gen"        ).c_str(),&iJet.mass_pr2_safe_gen );
  iTree->Branch((iName+"mass_pr3_safe_gen"        ).c_str(),&iJet.mass_pr3_safe_gen );
  iTree->Branch((iName+"mass_pr4_safe_gen"        ).c_str(),&iJet.mass_pr4_safe_gen );
  iTree->Branch((iName+"mass_sd1_safe_gen"        ).c_str(),&iJet.mass_sd1_safe_gen );
  iTree->Branch((iName+"mass_sd2_safe_gen"        ).c_str(),&iJet.mass_sd2_safe_gen );
  iTree->Branch((iName+"mass_sd3_safe_gen"        ).c_str(),&iJet.mass_sd3_safe_gen );
  iTree->Branch((iName+"mass_sd4_safe_gen"        ).c_str(),&iJet.mass_sd4_safe_gen );
  iTree->Branch((iName+"mass_sd5_safe_gen"        ).c_str(),&iJet.mass_sd5_safe_gen );
  iTree->Branch((iName+"mass_sd1_gen"        ).c_str(),&iJet.mass_sd1_gen );
  iTree->Branch((iName+"mass_sd2_gen"        ).c_str(),&iJet.mass_sd2_gen );
  iTree->Branch((iName+"mass_sd3_gen"        ).c_str(),&iJet.mass_sd3_gen );
  iTree->Branch((iName+"mass_sd4_gen"        ).c_str(),&iJet.mass_sd4_gen );
  iTree->Branch((iName+"mass_sd5_gen"        ).c_str(),&iJet.mass_sd5_gen );



  iTree->Branch((iName+"mrawgen"     ).c_str(),&iJet.mrawgen     );//needed?
  iTree->Branch((iName+"mtrimgen"    ).c_str(),&iJet.mtrimgen    );//needed?
  iTree->Branch((iName+"mtrimsafegen").c_str(),&iJet.mtrimsafegen);//needed?
  iTree->Branch((iName+"mcleangen"   ).c_str(),&iJet.mcleangen   );//needed?
  iTree->Branch((iName+"mconstgen"   ).c_str(),&iJet.mconstgen   );//needed?

  iTree->Branch((iName+"imatch"      ).c_str(),&iJet.imatch      );
}


void clear(JetInfo &iJet) {
  iJet.npu  = -1;

  iJet.pt         .clear();
  iJet.pt_tr1 .clear();
  iJet.pt_tr2 .clear();
  iJet.pt_tr3 .clear();
  iJet.pt_tr4 .clear();
  iJet.pt_tr1_safe .clear();
  iJet.pt_tr2_safe .clear();
  iJet.pt_tr3_safe .clear();
  iJet.pt_tr4_safe .clear();
  iJet.pt_pr1 .clear();
  iJet.pt_pr2 .clear();
  iJet.pt_pr3 .clear();
  iJet.pt_pr4 .clear();
  iJet.pt_pr1_safe .clear();
  iJet.pt_pr2_safe .clear();
  iJet.pt_pr3_safe .clear();
  iJet.pt_pr4_safe .clear();
  iJet.pt_sd1 .clear();
  iJet.pt_sd2 .clear();
  iJet.pt_sd3 .clear();
  iJet.pt_sd4 .clear();
  iJet.pt_sd5 .clear();
  iJet.pt_sd1_safe .clear();
  iJet.pt_sd2_safe .clear();
  iJet.pt_sd3_safe .clear();
  iJet.pt_sd4_safe .clear();
  iJet.pt_sd5_safe .clear();  






  iJet.ptcorr     .clear();
  iJet.ptraw      .clear();
  iJet.ptclean    .clear();
  iJet.pttrim     .clear();
  iJet.pttrimsafe .clear();
  iJet.eta        .clear();

 iJet.eta_tr1 .clear();
  iJet.eta_tr2 .clear();
  iJet.eta_tr3 .clear();
  iJet.eta_tr4 .clear();
  iJet.eta_tr1_safe .clear();
  iJet.eta_tr2_safe .clear();
  iJet.eta_tr3_safe .clear();
  iJet.eta_tr4_safe .clear();
  iJet.eta_pr1 .clear();
  iJet.eta_pr2 .clear();
  iJet.eta_pr3 .clear();
  iJet.eta_pr4 .clear();
  iJet.eta_pr1_safe .clear();
  iJet.eta_pr2_safe .clear();
  iJet.eta_pr3_safe .clear();
  iJet.eta_pr4_safe .clear();
  iJet.eta_sd1 .clear();
  iJet.eta_sd2 .clear();
  iJet.eta_sd3 .clear();
  iJet.eta_sd4 .clear();
  iJet.eta_sd5 .clear();
  iJet.eta_sd1_safe .clear();
  iJet.eta_sd2_safe .clear();
  iJet.eta_sd3_safe .clear();
  iJet.eta_sd4_safe .clear();
  iJet.eta_sd5_safe .clear();

  iJet.phi        .clear();

  iJet.phi_tr1 .clear();
  iJet.phi_tr2 .clear();
  iJet.phi_tr3 .clear();
  iJet.phi_tr4 .clear();
  iJet.phi_tr1_safe .clear();
  iJet.phi_tr2_safe .clear();
  iJet.phi_tr3_safe .clear();
  iJet.phi_tr4_safe .clear();
  iJet.phi_pr1 .clear();
  iJet.phi_pr2 .clear();
  iJet.phi_pr3 .clear();
  iJet.phi_pr4 .clear();
  iJet.phi_pr1_safe .clear();
  iJet.phi_pr2_safe .clear();
  iJet.phi_pr3_safe .clear();
  iJet.phi_pr4_safe .clear();
  iJet.phi_sd1 .clear();
  iJet.phi_sd2 .clear();
  iJet.phi_sd3 .clear();
  iJet.phi_sd4 .clear();
  iJet.phi_sd5 .clear();
  iJet.phi_sd1_safe .clear();
  iJet.phi_sd2_safe .clear();
  iJet.phi_sd3_safe .clear();
  iJet.phi_sd4_safe .clear();
  iJet.phi_sd5_safe .clear();


  iJet.m          .clear();
  iJet.mass_tr1 .clear();
  iJet.mass_tr2 .clear();
  iJet.mass_tr3 .clear();
  iJet.mass_tr4 .clear();
  iJet.mass_tr1_safe .clear();
  iJet.mass_tr2_safe .clear();
  iJet.mass_tr3_safe .clear();
  iJet.mass_tr4_safe .clear();
  iJet.mass_pr1 .clear();
  iJet.mass_pr2 .clear();
  iJet.mass_pr3 .clear();
  iJet.mass_pr4 .clear();
  iJet.mass_pr1_safe .clear();
  iJet.mass_pr2_safe .clear();
  iJet.mass_pr3_safe .clear();
  iJet.mass_pr4_safe .clear();
  iJet.mass_sd1 .clear();
  iJet.mass_sd2 .clear();
  iJet.mass_sd3 .clear();
  iJet.mass_sd4 .clear();
  iJet.mass_sd5 .clear();
  iJet.mass_sd1_safe .clear();
  iJet.mass_sd2_safe .clear();
  iJet.mass_sd3_safe .clear();
  iJet.mass_sd4_safe .clear();
  iJet.mass_sd5_safe .clear();



  iJet.mraw       .clear();
  iJet.mtrim      .clear();
  iJet.mtrimsafe  .clear();
  iJet.mpruned    .clear();
  iJet.mprunedsafe.clear();
  iJet.msoftdrop  .clear();
  iJet.msoftdropsafe.clear();
  iJet.mclean     .clear();
  iJet.mconst     .clear();
  iJet.nparticles .clear();
  iJet.nneutrals  .clear();
  iJet.ncharged   .clear();

  iJet.ptgen       .clear();
  iJet.pt_tr1_gen .clear();
  iJet.pt_tr2_gen .clear();
  iJet.pt_tr3_gen .clear();
  iJet.pt_tr4_gen .clear();
  iJet.pt_tr1_safe_gen .clear();
  iJet.pt_tr2_safe_gen .clear();
  iJet.pt_tr3_safe_gen .clear();
  iJet.pt_tr4_safe_gen .clear();
  iJet.pt_pr1_gen .clear();
  iJet.pt_pr2_gen .clear();
  iJet.pt_pr3_gen .clear();
  iJet.pt_pr4_gen .clear();
  iJet.pt_pr1_safe_gen .clear();
  iJet.pt_pr2_safe_gen .clear();
  iJet.pt_pr3_safe_gen .clear();
  iJet.pt_pr4_safe_gen .clear();
  iJet.pt_sd1_gen .clear();
  iJet.pt_sd2_gen .clear();
  iJet.pt_sd3_gen .clear();
  iJet.pt_sd4_gen .clear();
  iJet.pt_sd5_gen .clear();
  iJet.pt_sd1_safe_gen .clear();
  iJet.pt_sd2_safe_gen .clear();
  iJet.pt_sd3_safe_gen .clear();
  iJet.pt_sd4_safe_gen .clear();
  iJet.pt_sd5_safe_gen .clear();



  iJet.etagen      .clear();
  iJet.eta_tr1_gen .clear();
  iJet.eta_tr2_gen .clear();
  iJet.eta_tr3_gen .clear();
  iJet.eta_tr4_gen .clear();
  iJet.eta_tr1_safe_gen .clear();
  iJet.eta_tr2_safe_gen .clear();
  iJet.eta_tr3_safe_gen .clear();
  iJet.eta_tr4_safe_gen .clear();
  iJet.eta_pr1_gen .clear();
  iJet.eta_pr2_gen .clear();
  iJet.eta_pr3_gen .clear();
  iJet.eta_pr4_gen .clear();
  iJet.eta_pr1_safe_gen .clear();
  iJet.eta_pr2_safe_gen .clear();
  iJet.eta_pr3_safe_gen .clear();
  iJet.eta_pr4_safe_gen .clear();
  iJet.eta_sd1_gen .clear();
  iJet.eta_sd2_gen .clear();
  iJet.eta_sd3_gen .clear();
  iJet.eta_sd4_gen .clear();
  iJet.eta_sd5_gen .clear();
  iJet.eta_sd1_safe_gen .clear();
  iJet.eta_sd2_safe_gen .clear();
  iJet.eta_sd3_safe_gen .clear();
  iJet.eta_sd4_safe_gen .clear();
  iJet.eta_sd5_safe_gen .clear();

  iJet.phigen      .clear();
  iJet.phi_tr1_gen .clear();
  iJet.phi_tr2_gen .clear();
  iJet.phi_tr3_gen .clear();
  iJet.phi_tr4_gen .clear();
  iJet.phi_tr1_safe_gen .clear();
  iJet.phi_tr2_safe_gen .clear();
  iJet.phi_tr3_safe_gen .clear();
  iJet.phi_tr4_safe_gen .clear();
  iJet.phi_pr1_gen .clear();
  iJet.phi_pr2_gen .clear();
  iJet.phi_pr3_gen .clear();
  iJet.phi_pr4_gen .clear();
  iJet.phi_pr1_safe_gen .clear();
  iJet.phi_pr2_safe_gen .clear();
  iJet.phi_pr3_safe_gen .clear();
  iJet.phi_pr4_safe_gen .clear();
  iJet.phi_sd1_gen .clear();
  iJet.phi_sd2_gen .clear();
  iJet.phi_sd3_gen .clear();
  iJet.phi_sd4_gen .clear();
  iJet.phi_sd5_gen .clear();
  iJet.phi_sd1_safe_gen .clear();
  iJet.phi_sd2_safe_gen .clear();
  iJet.phi_sd3_safe_gen .clear();
  iJet.phi_sd4_safe_gen .clear();
  iJet.phi_sd5_safe_gen .clear();


  iJet.mgen        .clear();
  iJet.mass_tr1_gen .clear();
  iJet.mass_tr2_gen .clear();
  iJet.mass_tr3_gen .clear();
  iJet.mass_tr4_gen .clear();
  iJet.mass_tr1_safe_gen .clear();
  iJet.mass_tr2_safe_gen .clear();
  iJet.mass_tr3_safe_gen .clear();
  iJet.mass_tr4_safe_gen .clear();
  iJet.mass_pr1_gen .clear();
  iJet.mass_pr2_gen .clear();
  iJet.mass_pr3_gen .clear();
  iJet.mass_pr4_gen .clear();
  iJet.mass_pr1_safe_gen .clear();
  iJet.mass_pr2_safe_gen .clear();
  iJet.mass_pr3_safe_gen .clear();
  iJet.mass_pr4_safe_gen .clear();
  iJet.mass_sd1_gen .clear();
  iJet.mass_sd2_gen .clear();
  iJet.mass_sd3_gen .clear();
  iJet.mass_sd4_gen .clear();
  iJet.mass_sd5_gen .clear();
  iJet.mass_sd1_safe_gen .clear();
  iJet.mass_sd2_safe_gen .clear();
  iJet.mass_sd3_safe_gen .clear();
  iJet.mass_sd4_safe_gen .clear();
  iJet.mass_sd5_safe_gen .clear();


  iJet.mrawgen     .clear();
  iJet.mtrimgen    .clear();
  iJet.mtrimsafegen.clear();
  iJet.mcleangen   .clear();
  iJet.mconstgen   .clear();
  iJet.imatch      .clear();
}



void setJet(PseudoJet &iJet, JetInfo &iJetI, JetDefinition jet_def_, JetMedianBackgroundEstimator bge_rho, JetMedianBackgroundEstimator bge_rhom, JetMedianBackgroundEstimator bge_rhoC, 
	    bool isGEN, bool isCHS, FactorizedJetCorrector *iJetCorr, JetCorrectionUncertainty *iJetUnc, JetCleanser &gsn_cleanser, 
	    bool doGenMatching, vector<PseudoJet> genJets) {

  // -- area-median subtractor  ( safe area subtractor )
  contrib::SafeAreaSubtractor *area_subtractor = 0;
  if(!isCHS) area_subtractor = new contrib::SafeAreaSubtractor(&bge_rho, &bge_rhom);
  if( isCHS) area_subtractor = new contrib::SafeAreaSubtractor(&bge_rho, &bge_rhom,SelectorIsPupCharged(),SelectorIsPupVertex());
  PseudoJet lCorr =  (*area_subtractor)(iJet);
  
  // -- constituent subtractor
  contrib::ConstituentSubtractor *const_subtractor = 0;
  const_subtractor = new contrib::ConstituentSubtractor(&bge_rhoC);
  (*const_subtractor).use_common_bge_for_rho_and_rhom(true);
  PseudoJet lConstit = (*const_subtractor)(iJet);

  // -- cleansing 
  vector<PseudoJet> neutrals,chargedLV,chargedPU;
  getConstitsForCleansing(iJet.constituents(),neutrals,chargedLV,chargedPU);
  PseudoJet     lClean = gsn_cleanser(neutrals,chargedLV,chargedPU);
  
  // -- trimming
  fastjet::Filter trimmer( fastjet::Filter(fastjet::JetDefinition(fastjet::kt_algorithm, 0.2), fastjet::SelectorPtFractionMin(0.05)));
  fastjet::Filter trimmer1( fastjet::Filter(fastjet::JetDefinition(fastjet::kt_algorithm, 0.2), fastjet::SelectorPtFractionMin(0.03)));
  fastjet::Filter trimmer2( fastjet::Filter(fastjet::JetDefinition(fastjet::kt_algorithm, 0.2), fastjet::SelectorPtFractionMin(0.05)));
  fastjet::Filter trimmer3( fastjet::Filter(fastjet::JetDefinition(fastjet::kt_algorithm, 0.3), fastjet::SelectorPtFractionMin(0.03)));
  fastjet::Filter trimmer4( fastjet::Filter(fastjet::JetDefinition(fastjet::kt_algorithm, 0.1), fastjet::SelectorPtFractionMin(0.03)));

  PseudoJet lTrim     = (trimmer)(iJet);
  PseudoJet lTrim1     = (trimmer1)(iJet);
  PseudoJet lTrim2     = (trimmer2)(iJet);
  PseudoJet lTrim3     = (trimmer3)(iJet);
  PseudoJet lTrim4     = (trimmer4)(iJet);




  trimmer.set_subtractor(area_subtractor);
  trimmer1.set_subtractor(area_subtractor);
  trimmer2.set_subtractor(area_subtractor);
  trimmer3.set_subtractor(area_subtractor);
  trimmer4.set_subtractor(area_subtractor);





  PseudoJet lTrimSafe = (trimmer)(iJet);
  PseudoJet lTrimSafe1 = (trimmer1)(iJet);
  PseudoJet lTrimSafe2 = (trimmer2)(iJet);
  PseudoJet lTrimSafe3 = (trimmer3)(iJet);
  PseudoJet lTrimSafe4 = (trimmer4)(iJet);




  


 
    //pruning
  double RCut= 0.5;
  Pruner pruner(jet_def_, 0.1,RCut);
  Pruner pruner1(jet_def_, 0.1,0.5);
  Pruner pruner2(jet_def_, 0.05,0.5);
  Pruner pruner3(jet_def_, 0.1,0.75);
  Pruner pruner4(jet_def_, 0.05,0.75);
  




  PseudoJet lPruned = pruner(iJet);
  PseudoJet lPruned1 = pruner1(iJet);
  PseudoJet lPruned2 = pruner2(iJet);
  PseudoJet lPruned3 = pruner3(iJet);
  PseudoJet lPruned4 = pruner4(iJet);




  PseudoJet lPrunedSafe = pruner(lCorr);
  PseudoJet lPrunedSafe1 = pruner1(lCorr);
  PseudoJet lPrunedSafe2 = pruner2(lCorr);
  PseudoJet lPrunedSafe3 = pruner3(lCorr);
  PseudoJet lPrunedSafe4 = pruner4(lCorr); 






  //softdrop
  contrib::SoftDrop softdrop(2., 0.1, 1.0);
  contrib::SoftDrop softdrop1(-1.0, 0.1, 1.0);
  contrib::SoftDrop softdrop2(0.0, 0.1, 1.0);
  contrib::SoftDrop softdrop3(0.66, 0.1, 1.0);
  contrib::SoftDrop softdrop4(1.0, 0.1, 1.0);
  contrib::SoftDrop softdrop5(2.0, 0.1, 1.0);




  PseudoJet lSoftDropped = softdrop(iJet);
  PseudoJet lSoftDropped1 = softdrop1(iJet);
  PseudoJet lSoftDropped2 = softdrop2(iJet);
  PseudoJet lSoftDropped3 = softdrop3(iJet);
  PseudoJet lSoftDropped4 = softdrop4(iJet);
  PseudoJet lSoftDropped5 = softdrop5(iJet);  




  softdrop.set_subtractor(area_subtractor);
  softdrop1.set_subtractor(area_subtractor);
  softdrop2.set_subtractor(area_subtractor);
  softdrop3.set_subtractor(area_subtractor);
  softdrop4.set_subtractor(area_subtractor);
  softdrop5.set_subtractor(area_subtractor);





  PseudoJet lSoftDroppedSafe = softdrop(iJet);
  PseudoJet lSoftDroppedSafe1 = softdrop1(iJet);
  PseudoJet lSoftDroppedSafe2 = softdrop2(iJet);
  PseudoJet lSoftDroppedSafe3 = softdrop3(iJet);
  PseudoJet lSoftDroppedSafe4 = softdrop4(iJet);
  PseudoJet lSoftDroppedSafe5 = softdrop5(iJet);  




  
  // -- apply the JEC
  double lJEC = 1.;
  double lUnc = 0 ;
  if (!isGEN){
    lJEC = correction(iJet,iJetCorr,bge_rho.rho());  
    lUnc = unc       (iJet,iJetUnc);
  }

  // -- find the gen jet matched to this reco jet
  int imatch = -1;
  if (doGenMatching) imatch = matchingIndex(iJet,genJets);
  
  // -- fill jet info
  (iJetI.pt        ).push_back(lCorr     .pt());
  



  (iJetI.ptcorr    ).push_back(iJet      .pt()*lJEC);
  (iJetI.pt_tr1  ).push_back(lTrim1      .pt());
  (iJetI.pt_tr2    ).push_back(lTrim2      .pt());
  (iJetI.pt_tr3    ).push_back(lTrim3      .pt());
  (iJetI.pt_tr4    ).push_back(lTrim4      .pt());
  (iJetI.pt_tr1_safe  ).push_back(lTrimSafe1      .pt());
  (iJetI.pt_tr2_safe    ).push_back(lTrimSafe2      .pt());
  (iJetI.pt_tr3_safe    ).push_back(lTrimSafe3      .pt());
  (iJetI.pt_tr4_safe    ).push_back(lTrimSafe4      .pt());
  (iJetI.pt_pr1  ).push_back(lPruned1      .pt());
  (iJetI.pt_pr2    ).push_back(lPruned2      .pt());
  (iJetI.pt_pr3    ).push_back(lPruned3      .pt());
  (iJetI.pt_pr4    ).push_back(lPruned4      .pt());
  (iJetI.pt_pr1_safe  ).push_back(lPrunedSafe1      .pt());
  (iJetI.pt_pr2_safe    ).push_back(lPrunedSafe2      .pt());
  (iJetI.pt_pr3_safe    ).push_back(lPrunedSafe3      .pt());
  (iJetI.pt_pr4_safe    ).push_back(lPrunedSafe4      .pt());
  (iJetI.pt_sd1  ).push_back(lSoftDropped1      .pt());
  (iJetI.pt_sd2    ).push_back(lSoftDropped2      .pt());
  (iJetI.pt_sd3    ).push_back(lSoftDropped3      .pt());
  (iJetI.pt_sd4    ).push_back(lSoftDropped4      .pt());
  (iJetI.pt_sd5    ).push_back(lSoftDropped5      .pt());
  (iJetI.pt_sd1_safe  ).push_back(lSoftDroppedSafe1      .pt());
  (iJetI.pt_sd2_safe    ).push_back(lSoftDroppedSafe2      .pt());
  (iJetI.pt_sd3_safe    ).push_back(lSoftDroppedSafe3      .pt());
  (iJetI.pt_sd4_safe    ).push_back(lSoftDroppedSafe4      .pt());
  (iJetI.pt_sd5_safe    ).push_back(lSoftDroppedSafe5      .pt());







  (iJetI.ptraw     ).push_back(iJet      .pt());
  (iJetI.ptclean   ).push_back(lClean    .pt());
  (iJetI.pttrim    ).push_back(lTrim     .pt());
  (iJetI.pttrimsafe).push_back(lTrimSafe .pt());
  (iJetI.ptconst   ).push_back(lConstit  .pt());
  (iJetI.ptunc     ).push_back(lUnc);
  (iJetI.eta       ).push_back(iJet      .eta());

  (iJetI.eta_tr1  ).push_back(lTrim1      .eta());
  (iJetI.eta_tr2    ).push_back(lTrim2      .eta());
  (iJetI.eta_tr3    ).push_back(lTrim3      .eta());
  (iJetI.eta_tr4    ).push_back(lTrim4      .eta());
  (iJetI.eta_tr1_safe  ).push_back(lTrimSafe1      .eta());
  (iJetI.eta_tr2_safe    ).push_back(lTrimSafe2      .eta());
  (iJetI.eta_tr3_safe    ).push_back(lTrimSafe3      .eta());
  (iJetI.eta_tr4_safe    ).push_back(lTrimSafe4      .eta());
  (iJetI.eta_pr1  ).push_back(lPruned1      .eta());
  (iJetI.eta_pr2    ).push_back(lPruned2      .eta());
  (iJetI.eta_pr3    ).push_back(lPruned3      .eta());
  (iJetI.eta_pr4    ).push_back(lPruned4      .eta());
  (iJetI.eta_pr1_safe  ).push_back(lPrunedSafe1      .eta());
  (iJetI.eta_pr2_safe    ).push_back(lPrunedSafe2      .eta());
  (iJetI.eta_pr3_safe    ).push_back(lPrunedSafe3      .eta());
  (iJetI.eta_pr4_safe    ).push_back(lPrunedSafe4      .eta());
  (iJetI.eta_sd1  ).push_back(lSoftDropped1      .eta());
  (iJetI.eta_sd2    ).push_back(lSoftDropped2      .eta());
  (iJetI.eta_sd3    ).push_back(lSoftDropped3      .eta());
  (iJetI.eta_sd4    ).push_back(lSoftDropped4      .eta());
  (iJetI.eta_sd5    ).push_back(lSoftDropped5      .eta());
  (iJetI.eta_sd1_safe  ).push_back(lSoftDroppedSafe1      .eta());
  (iJetI.eta_sd2_safe    ).push_back(lSoftDroppedSafe2      .eta());
  (iJetI.eta_sd3_safe    ).push_back(lSoftDroppedSafe3      .eta());
  (iJetI.eta_sd4_safe    ).push_back(lSoftDroppedSafe4      .eta());
  (iJetI.eta_sd5_safe    ).push_back(lSoftDroppedSafe5      .eta());

  (iJetI.phi       ).push_back(iJet      .phi());
  (iJetI.phi_tr1  ).push_back(lTrim1      .phi());
  (iJetI.phi_tr2    ).push_back(lTrim2      .phi());
  (iJetI.phi_tr3    ).push_back(lTrim3      .phi());
  (iJetI.phi_tr4    ).push_back(lTrim4      .phi());
  (iJetI.phi_tr1_safe  ).push_back(lTrimSafe1      .phi());
  (iJetI.phi_tr2_safe    ).push_back(lTrimSafe2      .phi());
  (iJetI.phi_tr3_safe    ).push_back(lTrimSafe3      .phi());
  (iJetI.phi_tr4_safe    ).push_back(lTrimSafe4      .phi());
  (iJetI.phi_pr1  ).push_back(lPruned1      .phi());
  (iJetI.phi_pr2    ).push_back(lPruned2      .phi());
  (iJetI.phi_pr3    ).push_back(lPruned3      .phi());
  (iJetI.phi_pr4    ).push_back(lPruned4      .phi());
  (iJetI.phi_pr1_safe  ).push_back(lPrunedSafe1      .phi());
  (iJetI.phi_pr2_safe    ).push_back(lPrunedSafe2      .phi());
  (iJetI.phi_pr3_safe    ).push_back(lPrunedSafe3      .phi());
  (iJetI.phi_pr4_safe    ).push_back(lPrunedSafe4      .phi());
  (iJetI.phi_sd1  ).push_back(lSoftDropped1      .phi());
  (iJetI.phi_sd2    ).push_back(lSoftDropped2      .phi());
  (iJetI.phi_sd3    ).push_back(lSoftDropped3      .phi());
  (iJetI.phi_sd4    ).push_back(lSoftDropped4      .phi());
  (iJetI.phi_sd5    ).push_back(lSoftDropped5      .phi());
  (iJetI.phi_sd1_safe  ).push_back(lSoftDroppedSafe1      .phi());
  (iJetI.phi_sd2_safe    ).push_back(lSoftDroppedSafe2      .phi());
  (iJetI.phi_sd3_safe    ).push_back(lSoftDroppedSafe3      .phi());
  (iJetI.phi_sd4_safe    ).push_back(lSoftDroppedSafe4      .phi());
  (iJetI.phi_sd5_safe    ).push_back(lSoftDroppedSafe5      .phi()); 


 (iJetI.mraw      ).push_back(iJet      .m());
  (iJetI.m         ).push_back(lCorr     .m());
  (iJetI.mass_tr1  ).push_back(lTrim1      .m());
  (iJetI.mass_tr2    ).push_back(lTrim2      .m());
  (iJetI.mass_tr3    ).push_back(lTrim3      .m());
  (iJetI.mass_tr4    ).push_back(lTrim4      .m());
  (iJetI.mass_tr1_safe  ).push_back(lTrimSafe1      .m());
  (iJetI.mass_tr2_safe    ).push_back(lTrimSafe2      .m());
  (iJetI.mass_tr3_safe    ).push_back(lTrimSafe3      .m());
  (iJetI.mass_tr4_safe    ).push_back(lTrimSafe4      .m());
  (iJetI.mass_pr1  ).push_back(lPruned1      .m());
  (iJetI.mass_pr2    ).push_back(lPruned2      .m());
  (iJetI.mass_pr3    ).push_back(lPruned3      .m());
  (iJetI.mass_pr4    ).push_back(lPruned4      .m());
  (iJetI.mass_pr1_safe  ).push_back(lPrunedSafe1      .m());
  (iJetI.mass_pr2_safe    ).push_back(lPrunedSafe2      .m());
  (iJetI.mass_pr3_safe    ).push_back(lPrunedSafe3      .m());
  (iJetI.mass_pr4_safe    ).push_back(lPrunedSafe4      .m());
  (iJetI.mass_sd1  ).push_back(lSoftDropped1      .m());
  (iJetI.mass_sd2    ).push_back(lSoftDropped2      .m());
  (iJetI.mass_sd3    ).push_back(lSoftDropped3      .m());
  (iJetI.mass_sd4    ).push_back(lSoftDropped4      .m());
  (iJetI.mass_sd5    ).push_back(lSoftDropped5      .m());
  (iJetI.mass_sd1_safe  ).push_back(lSoftDroppedSafe1      .m());
  (iJetI.mass_sd2_safe    ).push_back(lSoftDroppedSafe2      .m());
  (iJetI.mass_sd3_safe    ).push_back(lSoftDroppedSafe3      .m());
  (iJetI.mass_sd4_safe    ).push_back(lSoftDroppedSafe4      .m());
  (iJetI.mass_sd5_safe    ).push_back(lSoftDroppedSafe5      .m());


  (iJetI.mclean    ).push_back(lClean    .m());
  (iJetI.mtrim     ).push_back(lTrim     .m());
  (iJetI.mtrimsafe ).push_back(lTrimSafe .m());
  (iJetI.mpruned   ).push_back(lPruned   .m());
  (iJetI.mprunedsafe).push_back(lPrunedSafe.m());
  (iJetI.msoftdrop).push_back(lSoftDropped.m());
  (iJetI.msoftdropsafe).push_back(lSoftDroppedSafe.m());
  (iJetI.mconst    ).push_back(lConstit  .m());
  (iJetI.nparticles).push_back((iJet.constituents()).size());
  (iJetI.nneutrals ).push_back(neutrals.size());
  (iJetI.ncharged  ).push_back(chargedLV.size()+chargedPU.size());
  
  if (imatch > -1){
    (iJetI.imatch  ).push_back(imatch);
    (iJetI.ptgen    ).push_back(genJets[imatch].pt());
 

  (iJetI.etagen   ).push_back(genJets[imatch].eta());
  (iJetI.phigen   ).push_back(genJets[imatch].phi());
  (iJetI.mgen     ).push_back(genJets[imatch].m());





  }
  else {
    (iJetI.imatch   ).push_back(imatch);
    (iJetI.ptgen    ).push_back(-999.);
    (iJetI.etagen   ).push_back(-999.);
    (iJetI.phigen   ).push_back(-999.);
    (iJetI.mgen     ).push_back(-999.);

  }
  
}


void setRecoJet(PseudoJet &iJet, JetInfo &iJetI, JetInfo iGenJetI,JetDefinition jet_def_, JetMedianBackgroundEstimator bge_rho, JetMedianBackgroundEstimator bge_rhom, JetMedianBackgroundEstimator bge_rhoC, 
		bool isCHS, FactorizedJetCorrector *iJetCorr, JetCorrectionUncertainty *iJetUnc, JetCleanser &gsn_cleanser) {

  // -- area-median subtractor  ( safe area subtractor )
  contrib::SafeAreaSubtractor *area_subtractor = 0;
  if(!isCHS) area_subtractor = new contrib::SafeAreaSubtractor(&bge_rho, &bge_rhom);
  if( isCHS) area_subtractor = new contrib::SafeAreaSubtractor(&bge_rho, &bge_rhom,SelectorIsPupCharged(),SelectorIsPupVertex());
  PseudoJet lCorr =  (*area_subtractor)(iJet);
  
  // -- constituent subtractor
  contrib::ConstituentSubtractor *const_subtractor = 0;
  const_subtractor = new contrib::ConstituentSubtractor(&bge_rhoC);
  (*const_subtractor).use_common_bge_for_rho_and_rhom(true);
  PseudoJet lConstit = (*const_subtractor)(iJet);

  // -- cleansing 
  vector<PseudoJet> neutrals,chargedLV,chargedPU;
  getConstitsForCleansing(iJet.constituents(),neutrals,chargedLV,chargedPU);
  PseudoJet     lClean = gsn_cleanser(neutrals,chargedLV,chargedPU);
  
   
// -- trimming
  fastjet::Filter trimmer( fastjet::Filter(fastjet::JetDefinition(fastjet::kt_algorithm, 0.2), fastjet::SelectorPtFractionMin(0.05)));
  fastjet::Filter trimmer1( fastjet::Filter(fastjet::JetDefinition(fastjet::kt_algorithm, 0.2), fastjet::SelectorPtFractionMin(0.03)));
  fastjet::Filter trimmer2( fastjet::Filter(fastjet::JetDefinition(fastjet::kt_algorithm, 0.2), fastjet::SelectorPtFractionMin(0.05)));
  fastjet::Filter trimmer3( fastjet::Filter(fastjet::JetDefinition(fastjet::kt_algorithm, 0.3), fastjet::SelectorPtFractionMin(0.03)));
  fastjet::Filter trimmer4( fastjet::Filter(fastjet::JetDefinition(fastjet::kt_algorithm, 0.1), fastjet::SelectorPtFractionMin(0.03)));

  PseudoJet lTrim     = (trimmer)(iJet);
  PseudoJet lTrim1     = (trimmer1)(iJet);
  PseudoJet lTrim2     = (trimmer2)(iJet);
  PseudoJet lTrim3     = (trimmer3)(iJet);
  PseudoJet lTrim4     = (trimmer4)(iJet);




  trimmer.set_subtractor(area_subtractor);
  trimmer1.set_subtractor(area_subtractor);
  trimmer2.set_subtractor(area_subtractor);
  trimmer3.set_subtractor(area_subtractor);
  trimmer4.set_subtractor(area_subtractor);





  PseudoJet lTrimSafe = (trimmer)(iJet);
  PseudoJet lTrimSafe1 = (trimmer1)(iJet);
  PseudoJet lTrimSafe2 = (trimmer2)(iJet);
  PseudoJet lTrimSafe3 = (trimmer3)(iJet);
  PseudoJet lTrimSafe4 = (trimmer4)(iJet);








    //pruning
  double RCut= 0.5;
  Pruner pruner(jet_def_, 0.1,RCut);
  Pruner pruner1(jet_def_, 0.1,0.5);
  Pruner pruner2(jet_def_, 0.05,0.5);
  Pruner pruner3(jet_def_, 0.1,0.75);
  Pruner pruner4(jet_def_, 0.05,0.75);



PseudoJet lPruned = pruner(iJet);
  PseudoJet lPruned1 = pruner1(iJet);
  PseudoJet lPruned2 = pruner2(iJet);
  PseudoJet lPruned3 = pruner3(iJet);
  PseudoJet lPruned4 = pruner4(iJet);




  PseudoJet lPrunedSafe = pruner(lCorr);
  PseudoJet lPrunedSafe1 = pruner1(lCorr);
  PseudoJet lPrunedSafe2 = pruner2(lCorr);
  PseudoJet lPrunedSafe3 = pruner3(lCorr);
  PseudoJet lPrunedSafe4 = pruner4(lCorr);






  //softdrop
  contrib::SoftDrop softdrop(2., 0.1, 1.0);
  contrib::SoftDrop softdrop1(-1.0, 0.1, 1.0);
  contrib::SoftDrop softdrop2(0.0, 0.1, 1.0);
  contrib::SoftDrop softdrop3(0.66, 0.1, 1.0);
  contrib::SoftDrop softdrop4(1.0, 0.1, 1.0);
  contrib::SoftDrop softdrop5(2.0, 0.1, 1.0);




  PseudoJet lSoftDropped = softdrop(iJet);
  PseudoJet lSoftDropped1 = softdrop1(iJet);
  PseudoJet lSoftDropped2 = softdrop2(iJet);
  PseudoJet lSoftDropped3 = softdrop3(iJet);
  PseudoJet lSoftDropped4 = softdrop4(iJet);
  PseudoJet lSoftDropped5 = softdrop5(iJet);




  softdrop.set_subtractor(area_subtractor);
  softdrop1.set_subtractor(area_subtractor);
  softdrop2.set_subtractor(area_subtractor);
  softdrop3.set_subtractor(area_subtractor);
  softdrop4.set_subtractor(area_subtractor);
  softdrop5.set_subtractor(area_subtractor);

   PseudoJet lSoftDroppedSafe = softdrop(iJet);
  PseudoJet lSoftDroppedSafe1 = softdrop1(iJet);
  PseudoJet lSoftDroppedSafe2 = softdrop2(iJet);
  PseudoJet lSoftDroppedSafe3 = softdrop3(iJet);
  PseudoJet lSoftDroppedSafe4 = softdrop4(iJet);
  PseudoJet lSoftDroppedSafe5 = softdrop5(iJet);


 
  // -- apply the JEC
  double lJEC = correction(iJet,iJetCorr,bge_rho.rho());  
  double lUnc = unc       (iJet,iJetUnc);
  

  // -- find the gen jet matched to this reco jet
  //int imatch = matchingIndex(iJet,genJets);
  int imatch = matchingIndexFromJetInfo(iJet, iGenJetI);
  
  // -- fill jet info
  (iJetI.pt        ).push_back(lCorr     .pt());
  (iJetI.ptcorr    ).push_back(iJet      .pt()*lJEC);
  (iJetI.pt_tr1  ).push_back(lTrim1      .pt());
  (iJetI.pt_tr2    ).push_back(lTrim2      .pt());
  (iJetI.pt_tr3    ).push_back(lTrim3      .pt());
  (iJetI.pt_tr4    ).push_back(lTrim4      .pt());
  (iJetI.pt_tr1_safe  ).push_back(lTrimSafe1      .pt());
  (iJetI.pt_tr2_safe    ).push_back(lTrimSafe2      .pt());
  (iJetI.pt_tr3_safe    ).push_back(lTrimSafe3      .pt());
  (iJetI.pt_tr4_safe    ).push_back(lTrimSafe4      .pt());
  (iJetI.pt_pr1  ).push_back(lPruned1      .pt());
  (iJetI.pt_pr2    ).push_back(lPruned2      .pt());
  (iJetI.pt_pr3    ).push_back(lPruned3      .pt());
  (iJetI.pt_pr4    ).push_back(lPruned4      .pt());
  (iJetI.pt_pr1_safe  ).push_back(lPrunedSafe1      .pt());
  (iJetI.pt_pr2_safe    ).push_back(lPrunedSafe2      .pt());
  (iJetI.pt_pr3_safe    ).push_back(lPrunedSafe3      .pt());
  (iJetI.pt_pr4_safe    ).push_back(lPrunedSafe4      .pt());
  (iJetI.pt_sd1  ).push_back(lSoftDropped1      .pt());
  (iJetI.pt_sd2    ).push_back(lSoftDropped2      .pt());
  (iJetI.pt_sd3    ).push_back(lSoftDropped3      .pt());
  (iJetI.pt_sd4    ).push_back(lSoftDropped4      .pt());
  (iJetI.pt_sd5    ).push_back(lSoftDropped5      .pt());
  (iJetI.pt_sd1_safe  ).push_back(lSoftDroppedSafe1      .pt());
  (iJetI.pt_sd2_safe    ).push_back(lSoftDroppedSafe2      .pt());
  (iJetI.pt_sd3_safe    ).push_back(lSoftDroppedSafe3      .pt());
  (iJetI.pt_sd4_safe    ).push_back(lSoftDroppedSafe4      .pt());
  (iJetI.pt_sd5_safe    ).push_back(lSoftDroppedSafe5      .pt());

  (iJetI.ptraw     ).push_back(iJet      .pt());
  (iJetI.ptclean   ).push_back(lClean    .pt());
  (iJetI.pttrim    ).push_back(lTrim     .pt());
  (iJetI.pttrimsafe).push_back(lTrimSafe .pt());
  (iJetI.ptconst   ).push_back(lConstit  .pt());
  (iJetI.ptunc     ).push_back(lUnc);
  (iJetI.eta       ).push_back(iJet      .eta());
   (iJetI.eta_tr1  ).push_back(lTrim1      .eta());
  (iJetI.eta_tr2    ).push_back(lTrim2      .eta());
  (iJetI.eta_tr3    ).push_back(lTrim3      .eta());
  (iJetI.eta_tr4    ).push_back(lTrim4      .eta());
  (iJetI.eta_tr1_safe  ).push_back(lTrimSafe1      .eta());
  (iJetI.eta_tr2_safe    ).push_back(lTrimSafe2      .eta());
  (iJetI.eta_tr3_safe    ).push_back(lTrimSafe3      .eta());
  (iJetI.eta_tr4_safe    ).push_back(lTrimSafe4      .eta());
  (iJetI.eta_pr1  ).push_back(lPruned1      .eta());
  (iJetI.eta_pr2    ).push_back(lPruned2      .eta());
  (iJetI.eta_pr3    ).push_back(lPruned3      .eta());
  (iJetI.eta_pr4    ).push_back(lPruned4      .eta());
  (iJetI.eta_pr1_safe  ).push_back(lPrunedSafe1      .eta());
  (iJetI.eta_pr2_safe    ).push_back(lPrunedSafe2      .eta());
  (iJetI.eta_pr3_safe    ).push_back(lPrunedSafe3      .eta());
  (iJetI.eta_pr4_safe    ).push_back(lPrunedSafe4      .eta());
  (iJetI.eta_sd1  ).push_back(lSoftDropped1      .eta());
  (iJetI.eta_sd2    ).push_back(lSoftDropped2      .eta());
  (iJetI.eta_sd3    ).push_back(lSoftDropped3      .eta());
  (iJetI.eta_sd4    ).push_back(lSoftDropped4      .eta());
  (iJetI.eta_sd5    ).push_back(lSoftDropped5      .eta());
  (iJetI.eta_sd1_safe  ).push_back(lSoftDroppedSafe1      .eta());
  (iJetI.eta_sd2_safe    ).push_back(lSoftDroppedSafe2      .eta());
  (iJetI.eta_sd3_safe    ).push_back(lSoftDroppedSafe3      .eta());
  (iJetI.eta_sd4_safe    ).push_back(lSoftDroppedSafe4      .eta());
  (iJetI.eta_sd5_safe    ).push_back(lSoftDroppedSafe5      .eta());



  (iJetI.phi       ).push_back(iJet      .phi());

  (iJetI.phi_tr1  ).push_back(lTrim1      .phi());
  (iJetI.phi_tr2    ).push_back(lTrim2      .phi());
  (iJetI.phi_tr3    ).push_back(lTrim3      .phi());
  (iJetI.phi_tr4    ).push_back(lTrim4      .phi());
  (iJetI.phi_tr1_safe  ).push_back(lTrimSafe1      .phi());
  (iJetI.phi_tr2_safe    ).push_back(lTrimSafe2      .phi());
  (iJetI.phi_tr3_safe    ).push_back(lTrimSafe3      .phi());
  (iJetI.phi_tr4_safe    ).push_back(lTrimSafe4      .phi());
  (iJetI.phi_pr1  ).push_back(lPruned1      .phi());
  (iJetI.phi_pr2    ).push_back(lPruned2      .phi());
  (iJetI.phi_pr3    ).push_back(lPruned3      .phi());
  (iJetI.phi_pr4    ).push_back(lPruned4      .phi());
  (iJetI.phi_pr1_safe  ).push_back(lPrunedSafe1      .phi());
  (iJetI.phi_pr2_safe    ).push_back(lPrunedSafe2      .phi());
  (iJetI.phi_pr3_safe    ).push_back(lPrunedSafe3      .phi());
  (iJetI.phi_pr4_safe    ).push_back(lPrunedSafe4      .phi());
  (iJetI.phi_sd1  ).push_back(lSoftDropped1      .phi());
  (iJetI.phi_sd2    ).push_back(lSoftDropped2      .phi());
  (iJetI.phi_sd3    ).push_back(lSoftDropped3      .phi());
  (iJetI.phi_sd4    ).push_back(lSoftDropped4      .phi());
  (iJetI.phi_sd5    ).push_back(lSoftDropped5      .phi());
  (iJetI.phi_sd1_safe  ).push_back(lSoftDroppedSafe1      .phi());
  (iJetI.phi_sd2_safe    ).push_back(lSoftDroppedSafe2      .phi());
  (iJetI.phi_sd3_safe    ).push_back(lSoftDroppedSafe3      .phi());
  (iJetI.phi_sd4_safe    ).push_back(lSoftDroppedSafe4      .phi());
  (iJetI.phi_sd5_safe    ).push_back(lSoftDroppedSafe5      .phi());


  (iJetI.mraw      ).push_back(iJet      .m());
  (iJetI.m         ).push_back(lCorr     .m());
  (iJetI.mass_tr1  ).push_back(lTrim1      .m());
  (iJetI.mass_tr2    ).push_back(lTrim2      .m());
  (iJetI.mass_tr3    ).push_back(lTrim3      .m());
  (iJetI.mass_tr4    ).push_back(lTrim4      .m());
  (iJetI.mass_tr1_safe  ).push_back(lTrimSafe1      .m());
  (iJetI.mass_tr2_safe    ).push_back(lTrimSafe2      .m());
  (iJetI.mass_tr3_safe    ).push_back(lTrimSafe3      .m());
  (iJetI.mass_tr4_safe    ).push_back(lTrimSafe4      .m());
  (iJetI.mass_pr1  ).push_back(lPruned1      .m());
  (iJetI.mass_pr2    ).push_back(lPruned2      .m());
  (iJetI.mass_pr3    ).push_back(lPruned3      .m());
  (iJetI.mass_pr4    ).push_back(lPruned4      .m());
  (iJetI.mass_pr1_safe  ).push_back(lPrunedSafe1      .m());
  (iJetI.mass_pr2_safe    ).push_back(lPrunedSafe2      .m());
  (iJetI.mass_pr3_safe    ).push_back(lPrunedSafe3      .m());
  (iJetI.mass_pr4_safe    ).push_back(lPrunedSafe4      .m());
  (iJetI.mass_sd1  ).push_back(lSoftDropped1      .m());
  (iJetI.mass_sd2    ).push_back(lSoftDropped2      .m());
  (iJetI.mass_sd3    ).push_back(lSoftDropped3      .m());
  (iJetI.mass_sd4    ).push_back(lSoftDropped4      .m());
  (iJetI.mass_sd5    ).push_back(lSoftDropped5      .m());
  (iJetI.mass_sd1_safe  ).push_back(lSoftDroppedSafe1      .m());
  (iJetI.mass_sd2_safe    ).push_back(lSoftDroppedSafe2      .m());
  (iJetI.mass_sd3_safe    ).push_back(lSoftDroppedSafe3      .m());
  (iJetI.mass_sd4_safe    ).push_back(lSoftDroppedSafe4      .m());
  (iJetI.mass_sd5_safe    ).push_back(lSoftDroppedSafe5      .m());



  (iJetI.mclean    ).push_back(lClean    .m());
  (iJetI.mtrim     ).push_back(lTrim     .m());
  (iJetI.mtrimsafe ).push_back(lTrimSafe .m());
  (iJetI.mpruned   ).push_back(lPruned   .m());
  (iJetI.mprunedsafe).push_back(lPrunedSafe.m());
  (iJetI.msoftdrop).push_back(lSoftDropped.m());
  (iJetI.msoftdropsafe).push_back(lSoftDroppedSafe.m());
  (iJetI.mconst    ).push_back(lConstit  .m());
  (iJetI.nparticles).push_back((iJet.constituents()).size());
  (iJetI.nneutrals ).push_back(neutrals.size());
  (iJetI.ncharged  ).push_back(chargedLV.size()+chargedPU.size());
  
  if (imatch > -1){
    (iJetI.imatch).push_back(imatch);
    (iJetI.ptgen    ).push_back((iGenJetI.pt)[imatch]);
    (iJetI.pt_tr1_gen     ).push_back((iGenJetI.pt_tr1)[imatch]);
    (iJetI.pt_tr2_gen     ).push_back((iGenJetI.pt_tr2)[imatch]);
    (iJetI.pt_tr3_gen     ).push_back((iGenJetI.pt_tr3)[imatch]);
    (iJetI.pt_tr4_gen     ).push_back((iGenJetI.pt_tr4)[imatch]);
    (iJetI.pt_tr1_safe_gen     ).push_back((iGenJetI.pt_tr1_safe)[imatch]);
    (iJetI.pt_tr2_safe_gen     ).push_back((iGenJetI.pt_tr2_safe)[imatch]);
    (iJetI.pt_tr3_safe_gen     ).push_back((iGenJetI.pt_tr3_safe)[imatch]);
    (iJetI.pt_tr4_safe_gen     ).push_back((iGenJetI.pt_tr4_safe)[imatch]);
    (iJetI.pt_pr1_gen     ).push_back((iGenJetI.pt_pr1)[imatch]);
    (iJetI.pt_pr2_gen     ).push_back((iGenJetI.pt_pr2)[imatch]);
    (iJetI.pt_pr3_gen     ).push_back((iGenJetI.pt_pr3)[imatch]);
    (iJetI.pt_pr4_gen     ).push_back((iGenJetI.pt_pr4)[imatch]);
    (iJetI.pt_pr1_safe_gen     ).push_back((iGenJetI.pt_pr1_safe)[imatch]);
    (iJetI.pt_pr2_safe_gen     ).push_back((iGenJetI.pt_pr2_safe)[imatch]);
    (iJetI.pt_pr3_safe_gen     ).push_back((iGenJetI.pt_pr3_safe)[imatch]);
    (iJetI.pt_pr4_safe_gen     ).push_back((iGenJetI.pt_pr4_safe)[imatch]);
    (iJetI.pt_sd1_gen     ).push_back((iGenJetI.pt_sd1)[imatch]);
    (iJetI.pt_sd2_gen     ).push_back((iGenJetI.pt_sd2)[imatch]);
    (iJetI.pt_sd3_gen     ).push_back((iGenJetI.pt_sd3)[imatch]);
    (iJetI.pt_sd4_gen     ).push_back((iGenJetI.pt_sd4)[imatch]);
    (iJetI.pt_sd5_gen     ).push_back((iGenJetI.pt_sd5)[imatch]);
    (iJetI.pt_sd1_safe_gen     ).push_back((iGenJetI.pt_sd1_safe)[imatch]);
    (iJetI.pt_sd2_safe_gen     ).push_back((iGenJetI.pt_sd2_safe)[imatch]);
    (iJetI.pt_sd3_safe_gen     ).push_back((iGenJetI.pt_sd3_safe)[imatch]);
    (iJetI.pt_sd4_safe_gen     ).push_back((iGenJetI.pt_sd4_safe)[imatch]);
    (iJetI.pt_sd5_safe_gen     ).push_back((iGenJetI.pt_sd5_safe)[imatch]);



    (iJetI.etagen   ).push_back((iGenJetI.eta)[imatch]);
    (iJetI.eta_tr1_gen     ).push_back((iGenJetI.eta_tr1)[imatch]);
    (iJetI.eta_tr2_gen     ).push_back((iGenJetI.eta_tr2)[imatch]);
    (iJetI.eta_tr3_gen     ).push_back((iGenJetI.eta_tr3)[imatch]);
    (iJetI.eta_tr4_gen     ).push_back((iGenJetI.eta_tr4)[imatch]);
    (iJetI.eta_tr1_safe_gen     ).push_back((iGenJetI.eta_tr1_safe)[imatch]);
    (iJetI.eta_tr2_safe_gen     ).push_back((iGenJetI.eta_tr2_safe)[imatch]);
    (iJetI.eta_tr3_safe_gen     ).push_back((iGenJetI.eta_tr3_safe)[imatch]);
    (iJetI.eta_tr4_safe_gen     ).push_back((iGenJetI.eta_tr4_safe)[imatch]);
    (iJetI.eta_pr1_gen     ).push_back((iGenJetI.eta_pr1)[imatch]);
    (iJetI.eta_pr2_gen     ).push_back((iGenJetI.eta_pr2)[imatch]);
    (iJetI.eta_pr3_gen     ).push_back((iGenJetI.eta_pr3)[imatch]);
    (iJetI.eta_pr4_gen     ).push_back((iGenJetI.eta_pr4)[imatch]);
    (iJetI.eta_pr1_safe_gen     ).push_back((iGenJetI.eta_pr1_safe)[imatch]);
    (iJetI.eta_pr2_safe_gen     ).push_back((iGenJetI.eta_pr2_safe)[imatch]);
    (iJetI.eta_pr3_safe_gen     ).push_back((iGenJetI.eta_pr3_safe)[imatch]);
    (iJetI.eta_pr4_safe_gen     ).push_back((iGenJetI.eta_pr4_safe)[imatch]);
    (iJetI.eta_sd1_gen     ).push_back((iGenJetI.eta_sd1)[imatch]);
    (iJetI.eta_sd2_gen     ).push_back((iGenJetI.eta_sd2)[imatch]);
    (iJetI.eta_sd3_gen     ).push_back((iGenJetI.eta_sd3)[imatch]);
    (iJetI.eta_sd4_gen     ).push_back((iGenJetI.eta_sd4)[imatch]);
    (iJetI.eta_sd5_gen     ).push_back((iGenJetI.eta_sd5)[imatch]);
    (iJetI.eta_sd1_safe_gen     ).push_back((iGenJetI.eta_sd1_safe)[imatch]);
    (iJetI.eta_sd2_safe_gen     ).push_back((iGenJetI.eta_sd2_safe)[imatch]);
    (iJetI.eta_sd3_safe_gen     ).push_back((iGenJetI.eta_sd3_safe)[imatch]);
    (iJetI.eta_sd4_safe_gen     ).push_back((iGenJetI.eta_sd4_safe)[imatch]);
    (iJetI.eta_sd5_safe_gen     ).push_back((iGenJetI.eta_sd5_safe)[imatch]);





    (iJetI.phigen   ).push_back((iGenJetI.phi)[imatch]);
    (iJetI.phi_tr1_gen     ).push_back((iGenJetI.phi_tr1)[imatch]);
    (iJetI.phi_tr2_gen     ).push_back((iGenJetI.phi_tr2)[imatch]);
    (iJetI.phi_tr3_gen     ).push_back((iGenJetI.phi_tr3)[imatch]);
    (iJetI.phi_tr4_gen     ).push_back((iGenJetI.phi_tr4)[imatch]);
    (iJetI.phi_tr1_safe_gen     ).push_back((iGenJetI.phi_tr1_safe)[imatch]);
    (iJetI.phi_tr2_safe_gen     ).push_back((iGenJetI.phi_tr2_safe)[imatch]);
    (iJetI.phi_tr3_safe_gen     ).push_back((iGenJetI.phi_tr3_safe)[imatch]);
    (iJetI.phi_tr4_safe_gen     ).push_back((iGenJetI.phi_tr4_safe)[imatch]);
    (iJetI.phi_pr1_gen     ).push_back((iGenJetI.phi_pr1)[imatch]);
    (iJetI.phi_pr2_gen     ).push_back((iGenJetI.phi_pr2)[imatch]);
    (iJetI.phi_pr3_gen     ).push_back((iGenJetI.phi_pr3)[imatch]);
    (iJetI.phi_pr4_gen     ).push_back((iGenJetI.phi_pr4)[imatch]);
    (iJetI.phi_pr1_safe_gen     ).push_back((iGenJetI.phi_pr1_safe)[imatch]);
    (iJetI.phi_pr2_safe_gen     ).push_back((iGenJetI.phi_pr2_safe)[imatch]);
    (iJetI.phi_pr3_safe_gen     ).push_back((iGenJetI.phi_pr3_safe)[imatch]);
    (iJetI.phi_pr4_safe_gen     ).push_back((iGenJetI.phi_pr4_safe)[imatch]);
    (iJetI.phi_sd1_gen     ).push_back((iGenJetI.phi_sd1)[imatch]);
    (iJetI.phi_sd2_gen     ).push_back((iGenJetI.phi_sd2)[imatch]);
    (iJetI.phi_sd3_gen     ).push_back((iGenJetI.phi_sd3)[imatch]);
    (iJetI.phi_sd4_gen     ).push_back((iGenJetI.phi_sd4)[imatch]);
    (iJetI.phi_sd5_gen     ).push_back((iGenJetI.phi_sd5)[imatch]);
    (iJetI.phi_sd1_safe_gen     ).push_back((iGenJetI.phi_sd1_safe)[imatch]);
    (iJetI.phi_sd2_safe_gen     ).push_back((iGenJetI.phi_sd2_safe)[imatch]);
    (iJetI.phi_sd3_safe_gen     ).push_back((iGenJetI.phi_sd3_safe)[imatch]);
    (iJetI.phi_sd4_safe_gen     ).push_back((iGenJetI.phi_sd4_safe)[imatch]);
    (iJetI.phi_sd5_safe_gen     ).push_back((iGenJetI.phi_sd5_safe)[imatch]);


    
    (iJetI.mgen     ).push_back((iGenJetI.m)[imatch]);
    (iJetI.mass_tr1_gen     ).push_back((iGenJetI.mass_tr1)[imatch]);
    (iJetI.mass_tr2_gen     ).push_back((iGenJetI.mass_tr2)[imatch]);
    (iJetI.mass_tr3_gen     ).push_back((iGenJetI.mass_tr3)[imatch]);
    (iJetI.mass_tr4_gen     ).push_back((iGenJetI.mass_tr4)[imatch]);
    (iJetI.mass_tr1_safe_gen     ).push_back((iGenJetI.mass_tr1_safe)[imatch]);
    (iJetI.mass_tr2_safe_gen     ).push_back((iGenJetI.mass_tr2_safe)[imatch]);
    (iJetI.mass_tr3_safe_gen     ).push_back((iGenJetI.mass_tr3_safe)[imatch]);
    (iJetI.mass_tr4_safe_gen     ).push_back((iGenJetI.mass_tr4_safe)[imatch]);
    (iJetI.mass_pr1_gen     ).push_back((iGenJetI.mass_pr1)[imatch]);
    (iJetI.mass_pr2_gen     ).push_back((iGenJetI.mass_pr2)[imatch]);
    (iJetI.mass_pr3_gen     ).push_back((iGenJetI.mass_pr3)[imatch]);
    (iJetI.mass_pr4_gen     ).push_back((iGenJetI.mass_pr4)[imatch]);
    (iJetI.mass_pr1_safe_gen     ).push_back((iGenJetI.mass_pr1_safe)[imatch]);
    (iJetI.mass_pr2_safe_gen     ).push_back((iGenJetI.mass_pr2_safe)[imatch]);
    (iJetI.mass_pr3_safe_gen     ).push_back((iGenJetI.mass_pr3_safe)[imatch]);
    (iJetI.mass_pr4_safe_gen     ).push_back((iGenJetI.mass_pr4_safe)[imatch]);
    (iJetI.mass_sd1_gen     ).push_back((iGenJetI.mass_sd1)[imatch]);
    (iJetI.mass_sd2_gen     ).push_back((iGenJetI.mass_sd2)[imatch]);
    (iJetI.mass_sd3_gen     ).push_back((iGenJetI.mass_sd3)[imatch]);
    (iJetI.mass_sd4_gen     ).push_back((iGenJetI.mass_sd4)[imatch]);
    (iJetI.mass_sd5_gen     ).push_back((iGenJetI.mass_sd5)[imatch]);
    (iJetI.mass_sd1_safe_gen     ).push_back((iGenJetI.mass_sd1_safe)[imatch]);
    (iJetI.mass_sd2_safe_gen     ).push_back((iGenJetI.mass_sd2_safe)[imatch]);
    (iJetI.mass_sd3_safe_gen     ).push_back((iGenJetI.mass_sd3_safe)[imatch]);
    (iJetI.mass_sd4_safe_gen     ).push_back((iGenJetI.mass_sd4_safe)[imatch]);
    (iJetI.mass_sd5_safe_gen     ).push_back((iGenJetI.mass_sd5_safe)[imatch]);   
    (iJetI.mrawgen     ).push_back((iGenJetI.mraw)[imatch]);
    (iJetI.mtrimgen    ).push_back((iGenJetI.mtrim)[imatch]);
    (iJetI.mtrimsafegen).push_back((iGenJetI.mtrimsafe)[imatch]);
    (iJetI.mcleangen   ).push_back((iGenJetI.mclean)[imatch]);
    (iJetI.mconstgen   ).push_back((iGenJetI.mconst)[imatch]);
  }
  else { //dummy values ?
    (iJetI.imatch).push_back(imatch);
    (iJetI.ptgen    ).push_back(-999.);
    (iJetI.pt_tr1_gen     ).push_back(-999.);
(iJetI.pt_tr2_gen     ).push_back(-999.);
(iJetI.pt_tr3_gen     ).push_back(-999.);
(iJetI.pt_tr4_gen     ).push_back(-999.);
(iJetI.pt_tr1_safe_gen     ).push_back(-999.);
(iJetI.pt_tr2_safe_gen     ).push_back(-999.);
(iJetI.pt_tr3_safe_gen     ).push_back(-999.);
(iJetI.pt_tr4_safe_gen     ).push_back(-999.);
(iJetI.pt_pr1_gen     ).push_back(-999.);
(iJetI.pt_pr2_gen     ).push_back(-999.);
(iJetI.pt_pr3_gen     ).push_back(-999.);
(iJetI.pt_pr4_gen     ).push_back(-999.);
(iJetI.pt_pr1_safe_gen     ).push_back(-999.);
(iJetI.pt_pr2_safe_gen     ).push_back(-999.);
(iJetI.pt_pr3_safe_gen     ).push_back(-999.);
(iJetI.pt_pr4_safe_gen     ).push_back(-999.);
(iJetI.pt_sd1_gen     ).push_back(-999.);
(iJetI.pt_sd2_gen     ).push_back(-999.);
(iJetI.pt_sd3_gen     ).push_back(-999.);
(iJetI.pt_sd4_gen     ).push_back(-999.);
(iJetI.pt_sd5_gen     ).push_back(-999.);
(iJetI.pt_sd1_safe_gen     ).push_back(-999.);
(iJetI.pt_sd2_safe_gen     ).push_back(-999.);
(iJetI.pt_sd3_safe_gen     ).push_back(-999.);
(iJetI.pt_sd4_safe_gen     ).push_back(-999.);
(iJetI.pt_sd5_safe_gen     ).push_back(-999.);



    (iJetI.etagen   ).push_back(-999.);
    (iJetI.eta_tr1_gen     ).push_back(-999.);
(iJetI.eta_tr2_gen     ).push_back(-999.);
(iJetI.eta_tr3_gen     ).push_back(-999.);
(iJetI.eta_tr4_gen     ).push_back(-999.);
(iJetI.eta_tr1_safe_gen     ).push_back(-999.);
(iJetI.eta_tr2_safe_gen     ).push_back(-999.);
(iJetI.eta_tr3_safe_gen     ).push_back(-999.);
(iJetI.eta_tr4_safe_gen     ).push_back(-999.);
(iJetI.eta_pr1_gen     ).push_back(-999.);
(iJetI.eta_pr2_gen     ).push_back(-999.);
(iJetI.eta_pr3_gen     ).push_back(-999.);
(iJetI.eta_pr4_gen     ).push_back(-999.);
(iJetI.eta_pr1_safe_gen     ).push_back(-999.);
(iJetI.eta_pr2_safe_gen     ).push_back(-999.);
(iJetI.eta_pr3_safe_gen     ).push_back(-999.);
(iJetI.eta_pr4_safe_gen     ).push_back(-999.);
(iJetI.eta_sd1_gen     ).push_back(-999.);
(iJetI.eta_sd2_gen     ).push_back(-999.);
(iJetI.eta_sd3_gen     ).push_back(-999.);
(iJetI.eta_sd4_gen     ).push_back(-999.);
(iJetI.eta_sd5_gen     ).push_back(-999.);
(iJetI.eta_sd1_safe_gen     ).push_back(-999.);
(iJetI.eta_sd2_safe_gen     ).push_back(-999.);
(iJetI.eta_sd3_safe_gen     ).push_back(-999.);
(iJetI.eta_sd4_safe_gen     ).push_back(-999.);
(iJetI.eta_sd5_safe_gen     ).push_back(-999.);



    (iJetI.phigen   ).push_back(-999.);
    (iJetI.phi_tr1_gen     ).push_back(-999.);
(iJetI.phi_tr2_gen     ).push_back(-999.);
(iJetI.phi_tr3_gen     ).push_back(-999.);
(iJetI.phi_tr4_gen     ).push_back(-999.);
(iJetI.phi_tr1_safe_gen     ).push_back(-999.);
(iJetI.phi_tr2_safe_gen     ).push_back(-999.);
(iJetI.phi_tr3_safe_gen     ).push_back(-999.);
(iJetI.phi_tr4_safe_gen     ).push_back(-999.);
(iJetI.phi_pr1_gen     ).push_back(-999.);
(iJetI.phi_pr2_gen     ).push_back(-999.);
(iJetI.phi_pr3_gen     ).push_back(-999.);
(iJetI.phi_pr4_gen     ).push_back(-999.);
(iJetI.phi_pr1_safe_gen     ).push_back(-999.);
(iJetI.phi_pr2_safe_gen     ).push_back(-999.);
(iJetI.phi_pr3_safe_gen     ).push_back(-999.);
(iJetI.phi_pr4_safe_gen     ).push_back(-999.);
(iJetI.phi_sd1_gen     ).push_back(-999.);
(iJetI.phi_sd2_gen     ).push_back(-999.);
(iJetI.phi_sd3_gen     ).push_back(-999.);
(iJetI.phi_sd4_gen     ).push_back(-999.);
(iJetI.phi_sd5_gen     ).push_back(-999.);
(iJetI.phi_sd1_safe_gen     ).push_back(-999.);
(iJetI.phi_sd2_safe_gen     ).push_back(-999.);
(iJetI.phi_sd3_safe_gen     ).push_back(-999.);
(iJetI.phi_sd4_safe_gen     ).push_back(-999.);
(iJetI.phi_sd5_safe_gen     ).push_back(-999.);




    (iJetI.mgen     ).push_back(-999.);
    (iJetI.mass_tr1_gen     ).push_back(-999.);
(iJetI.mass_tr2_gen     ).push_back(-999.);
(iJetI.mass_tr3_gen     ).push_back(-999.);
(iJetI.mass_tr4_gen     ).push_back(-999.);
(iJetI.mass_tr1_safe_gen     ).push_back(-999.);
(iJetI.mass_tr2_safe_gen     ).push_back(-999.);
(iJetI.mass_tr3_safe_gen     ).push_back(-999.);
(iJetI.mass_tr4_safe_gen     ).push_back(-999.);
(iJetI.mass_pr1_gen     ).push_back(-999.);
(iJetI.mass_pr2_gen     ).push_back(-999.);
(iJetI.mass_pr3_gen     ).push_back(-999.);
(iJetI.mass_pr4_gen     ).push_back(-999.);
(iJetI.mass_pr1_safe_gen     ).push_back(-999.);
(iJetI.mass_pr2_safe_gen     ).push_back(-999.);
(iJetI.mass_pr3_safe_gen     ).push_back(-999.);
(iJetI.mass_pr4_safe_gen     ).push_back(-999.);
(iJetI.mass_sd1_gen     ).push_back(-999.);
(iJetI.mass_sd2_gen     ).push_back(-999.);
(iJetI.mass_sd3_gen     ).push_back(-999.);
(iJetI.mass_sd4_gen     ).push_back(-999.);
(iJetI.mass_sd5_gen     ).push_back(-999.);
(iJetI.mass_sd1_safe_gen     ).push_back(-999.);
(iJetI.mass_sd2_safe_gen     ).push_back(-999.);
(iJetI.mass_sd3_safe_gen     ).push_back(-999.);
(iJetI.mass_sd4_safe_gen     ).push_back(-999.);
(iJetI.mass_sd5_safe_gen     ).push_back(-999.);


    (iJetI.mrawgen     ).push_back(-999.);
    (iJetI.mtrimgen    ).push_back(-999.);
    (iJetI.mtrimsafegen).push_back(-999.);
    (iJetI.mcleangen   ).push_back(-999.);
    (iJetI.mconstgen   ).push_back(-999.);
  }
  
}


void setGenJet(PseudoJet &iJet, JetInfo &iJetI, JetDefinition jet_def_, JetMedianBackgroundEstimator bge_rho, JetMedianBackgroundEstimator bge_rhom, JetMedianBackgroundEstimator bge_rhoC, JetCleanser &gsn_cleanser) {

  // -- area-median subtractor  ( safe area subtractor )
  contrib::SafeAreaSubtractor *area_subtractor = 0;
  area_subtractor = new contrib::SafeAreaSubtractor(&bge_rho, &bge_rhom);
  PseudoJet lCorr =  (*area_subtractor)(iJet);
  
  // -- constituent subtractor
  contrib::ConstituentSubtractor *const_subtractor = 0;
  const_subtractor = new contrib::ConstituentSubtractor(&bge_rhoC);
  (*const_subtractor).use_common_bge_for_rho_and_rhom(true);
  PseudoJet lConstit = (*const_subtractor)(iJet);

  // -- cleansing 
  vector<PseudoJet> neutrals,chargedLV,chargedPU;
  getConstitsForCleansing(iJet.constituents(),neutrals,chargedLV,chargedPU);
  PseudoJet     lClean = gsn_cleanser(neutrals,chargedLV,chargedPU);
  
  // -- trimming
  fastjet::Filter trimmer( fastjet::Filter(fastjet::JetDefinition(fastjet::kt_algorithm, 0.2), fastjet::SelectorPtFractionMin(0.05)));
  fastjet::Filter trimmer1( fastjet::Filter(fastjet::JetDefinition(fastjet::kt_algorithm, 0.2), fastjet::SelectorPtFractionMin(0.03)));
  fastjet::Filter trimmer2( fastjet::Filter(fastjet::JetDefinition(fastjet::kt_algorithm, 0.2), fastjet::SelectorPtFractionMin(0.05)));
  fastjet::Filter trimmer3( fastjet::Filter(fastjet::JetDefinition(fastjet::kt_algorithm, 0.3), fastjet::SelectorPtFractionMin(0.03)));
  fastjet::Filter trimmer4( fastjet::Filter(fastjet::JetDefinition(fastjet::kt_algorithm, 0.1), fastjet::SelectorPtFractionMin(0.03)));


  PseudoJet lTrim     = (trimmer)(iJet);
  PseudoJet lTrim1     = (trimmer1)(iJet);
  PseudoJet lTrim2     = (trimmer2)(iJet);
  PseudoJet lTrim3     = (trimmer3)(iJet);
  PseudoJet lTrim4     = (trimmer4)(iJet);

  trimmer.set_subtractor(area_subtractor);
  trimmer1.set_subtractor(area_subtractor);
  trimmer2.set_subtractor(area_subtractor);
  trimmer3.set_subtractor(area_subtractor);
  trimmer4.set_subtractor(area_subtractor);


  PseudoJet lTrimSafe = (trimmer)(iJet);
  PseudoJet lTrimSafe1 = (trimmer1)(iJet);
  PseudoJet lTrimSafe2 = (trimmer2)(iJet);
  PseudoJet lTrimSafe3 = (trimmer3)(iJet);
  PseudoJet lTrimSafe4 = (trimmer4)(iJet);


  
   double RCut= 0.5;
  Pruner pruner(jet_def_, 0.1,RCut);
   Pruner pruner1(jet_def_, 0.1,0.5);
  Pruner pruner2(jet_def_, 0.05,0.5);
  Pruner pruner3(jet_def_, 0.1,0.75);
  Pruner pruner4(jet_def_, 0.05,0.75);



  PseudoJet lPruned = pruner(iJet);
  PseudoJet lPruned1 = pruner1(iJet);
  PseudoJet lPruned2 = pruner2(iJet);
  PseudoJet lPruned3 = pruner3(iJet);
  PseudoJet lPruned4 = pruner4(iJet);

  PseudoJet lPrunedSafe = pruner(lCorr);
  PseudoJet lPrunedSafe1 = pruner1(lCorr);
  PseudoJet lPrunedSafe2 = pruner2(lCorr);
  PseudoJet lPrunedSafe3 = pruner3(lCorr);
  PseudoJet lPrunedSafe4 = pruner4(lCorr);


  
  //softdrop
 contrib::SoftDrop softdrop(2., 0.1, 1.0);
 contrib::SoftDrop softdrop1(-1.0, 0.1, 1.0);
  contrib::SoftDrop softdrop2(0.0, 0.1, 1.0);
  contrib::SoftDrop softdrop3(0.66, 0.1, 1.0);
  contrib::SoftDrop softdrop4(1.0, 0.1, 1.0);
  contrib::SoftDrop softdrop5(2.0, 0.1, 1.0);



  PseudoJet lSoftDropped = softdrop(iJet);
  PseudoJet lSoftDropped1 = softdrop1(iJet);
  PseudoJet lSoftDropped2 = softdrop2(iJet);
  PseudoJet lSoftDropped3 = softdrop3(iJet);
  PseudoJet lSoftDropped4 = softdrop4(iJet);
  PseudoJet lSoftDropped5 = softdrop5(iJet);


  softdrop.set_subtractor(area_subtractor);
  softdrop1.set_subtractor(area_subtractor);
  softdrop2.set_subtractor(area_subtractor);
  softdrop3.set_subtractor(area_subtractor);
  softdrop4.set_subtractor(area_subtractor);
  softdrop5.set_subtractor(area_subtractor);



  PseudoJet lSoftDroppedSafe = softdrop(iJet);
  PseudoJet lSoftDroppedSafe1 = softdrop1(iJet);
  PseudoJet lSoftDroppedSafe2 = softdrop2(iJet);
  PseudoJet lSoftDroppedSafe3 = softdrop3(iJet);
  PseudoJet lSoftDroppedSafe4 = softdrop4(iJet);
  PseudoJet lSoftDroppedSafe5 = softdrop5(iJet);




    
  // -- fill jet info
  (iJetI.pt        ).push_back(lCorr     .pt());
  (iJetI.pt_tr1  ).push_back(lTrim1      .pt());
  (iJetI.pt_tr2    ).push_back(lTrim2      .pt());
  (iJetI.pt_tr3    ).push_back(lTrim3      .pt());
  (iJetI.pt_tr4    ).push_back(lTrim4      .pt());
  (iJetI.pt_tr1_safe  ).push_back(lTrimSafe1      .pt());
  (iJetI.pt_tr2_safe    ).push_back(lTrimSafe2      .pt());
  (iJetI.pt_tr3_safe    ).push_back(lTrimSafe3      .pt());
  (iJetI.pt_tr4_safe    ).push_back(lTrimSafe4      .pt());
  (iJetI.pt_pr1  ).push_back(lPruned1      .pt());
  (iJetI.pt_pr2    ).push_back(lPruned2      .pt());
  (iJetI.pt_pr3    ).push_back(lPruned3      .pt());
  (iJetI.pt_pr4    ).push_back(lPruned4      .pt());
  (iJetI.pt_pr1_safe  ).push_back(lPrunedSafe1      .pt());
  (iJetI.pt_pr2_safe    ).push_back(lPrunedSafe2      .pt());
  (iJetI.pt_pr3_safe    ).push_back(lPrunedSafe3      .pt());
  (iJetI.pt_pr4_safe    ).push_back(lPrunedSafe4      .pt());
  (iJetI.pt_sd1  ).push_back(lSoftDropped1      .pt());
  (iJetI.pt_sd2    ).push_back(lSoftDropped2      .pt());
  (iJetI.pt_sd3    ).push_back(lSoftDropped3      .pt());
  (iJetI.pt_sd4    ).push_back(lSoftDropped4      .pt());
  (iJetI.pt_sd5    ).push_back(lSoftDropped5      .pt());
  (iJetI.pt_sd1_safe  ).push_back(lSoftDroppedSafe1      .pt());
  (iJetI.pt_sd2_safe    ).push_back(lSoftDroppedSafe2      .pt());
  (iJetI.pt_sd3_safe    ).push_back(lSoftDroppedSafe3      .pt());
  (iJetI.pt_sd4_safe    ).push_back(lSoftDroppedSafe4      .pt());
  (iJetI.pt_sd5_safe    ).push_back(lSoftDroppedSafe5      .pt()); 


  (iJetI.ptcorr    ).push_back(iJet      .pt());
  (iJetI.ptraw     ).push_back(iJet      .pt());
  (iJetI.ptclean   ).push_back(lClean    .pt());
  (iJetI.pttrim    ).push_back(lTrim     .pt());
  (iJetI.pttrimsafe).push_back(lTrimSafe .pt());
  (iJetI.ptconst   ).push_back(lConstit  .pt());
  (iJetI.ptunc     ).push_back(0.);
  (iJetI.eta       ).push_back(iJet      .eta());
  (iJetI.eta_tr1  ).push_back(lTrim1      .eta());
  (iJetI.eta_tr2    ).push_back(lTrim2      .eta());
  (iJetI.eta_tr3    ).push_back(lTrim3      .eta());
  (iJetI.eta_tr4    ).push_back(lTrim4      .eta());
  (iJetI.eta_tr1_safe  ).push_back(lTrimSafe1      .eta());
  (iJetI.eta_tr2_safe    ).push_back(lTrimSafe2      .eta());
  (iJetI.eta_tr3_safe    ).push_back(lTrimSafe3      .eta());
  (iJetI.eta_tr4_safe    ).push_back(lTrimSafe4      .eta());
  (iJetI.eta_pr1  ).push_back(lPruned1      .eta());
  (iJetI.eta_pr2    ).push_back(lPruned2      .eta());
  (iJetI.eta_pr3    ).push_back(lPruned3      .eta());
  (iJetI.eta_pr4    ).push_back(lPruned4      .eta());
  (iJetI.eta_pr1_safe  ).push_back(lPrunedSafe1      .eta());
  (iJetI.eta_pr2_safe    ).push_back(lPrunedSafe2      .eta());
  (iJetI.eta_pr3_safe    ).push_back(lPrunedSafe3      .eta());
  (iJetI.eta_pr4_safe    ).push_back(lPrunedSafe4      .eta());
  (iJetI.eta_sd1  ).push_back(lSoftDropped1      .eta());
  (iJetI.eta_sd2    ).push_back(lSoftDropped2      .eta());
  (iJetI.eta_sd3    ).push_back(lSoftDropped3      .eta());
  (iJetI.eta_sd4    ).push_back(lSoftDropped4      .eta());
  (iJetI.eta_sd5    ).push_back(lSoftDropped5      .eta());
  (iJetI.eta_sd1_safe  ).push_back(lSoftDroppedSafe1      .eta());
  (iJetI.eta_sd2_safe    ).push_back(lSoftDroppedSafe2      .eta());
  (iJetI.eta_sd3_safe    ).push_back(lSoftDroppedSafe3      .eta());
  (iJetI.eta_sd4_safe    ).push_back(lSoftDroppedSafe4      .eta());
  (iJetI.eta_sd5_safe    ).push_back(lSoftDroppedSafe5      .eta());





  (iJetI.phi       ).push_back(iJet      .phi());
  (iJetI.phi_tr1  ).push_back(lTrim1      .phi());
  (iJetI.phi_tr2    ).push_back(lTrim2      .phi());
  (iJetI.phi_tr3    ).push_back(lTrim3      .phi());
  (iJetI.phi_tr4    ).push_back(lTrim4      .phi());
  (iJetI.phi_tr1_safe  ).push_back(lTrimSafe1      .phi());
  (iJetI.phi_tr2_safe    ).push_back(lTrimSafe2      .phi());
  (iJetI.phi_tr3_safe    ).push_back(lTrimSafe3      .phi());
  (iJetI.phi_tr4_safe    ).push_back(lTrimSafe4      .phi());
  (iJetI.phi_pr1  ).push_back(lPruned1      .phi());
  (iJetI.phi_pr2    ).push_back(lPruned2      .phi());
  (iJetI.phi_pr3    ).push_back(lPruned3      .phi());
  (iJetI.phi_pr4    ).push_back(lPruned4      .phi());
  (iJetI.phi_pr1_safe  ).push_back(lPrunedSafe1      .phi());
  (iJetI.phi_pr2_safe    ).push_back(lPrunedSafe2      .phi());
  (iJetI.phi_pr3_safe    ).push_back(lPrunedSafe3      .phi());
  (iJetI.phi_pr4_safe    ).push_back(lPrunedSafe4      .phi());
  (iJetI.phi_sd1  ).push_back(lSoftDropped1      .phi());
  (iJetI.phi_sd2    ).push_back(lSoftDropped2      .phi());
  (iJetI.phi_sd3    ).push_back(lSoftDropped3      .phi());
  (iJetI.phi_sd4    ).push_back(lSoftDropped4      .phi());
  (iJetI.phi_sd5    ).push_back(lSoftDropped5      .phi());
  (iJetI.phi_sd1_safe  ).push_back(lSoftDroppedSafe1      .phi());
  (iJetI.phi_sd2_safe    ).push_back(lSoftDroppedSafe2      .phi());
  (iJetI.phi_sd3_safe    ).push_back(lSoftDroppedSafe3      .phi());
  (iJetI.phi_sd4_safe    ).push_back(lSoftDroppedSafe4      .phi());
  (iJetI.phi_sd5_safe    ).push_back(lSoftDroppedSafe5      .phi());



  (iJetI.mraw      ).push_back(iJet      .m());
  (iJetI.m         ).push_back(lCorr     .m());
  (iJetI.mass_tr1  ).push_back(lTrim1      .m());
  (iJetI.mass_tr2    ).push_back(lTrim2      .m());
  (iJetI.mass_tr3    ).push_back(lTrim3      .m());
  (iJetI.mass_tr4    ).push_back(lTrim4      .m());
  (iJetI.mass_tr1_safe  ).push_back(lTrimSafe1      .m());
  (iJetI.mass_tr2_safe    ).push_back(lTrimSafe2      .m());
  (iJetI.mass_tr3_safe    ).push_back(lTrimSafe3      .m());
  (iJetI.mass_tr4_safe    ).push_back(lTrimSafe4      .m());
  (iJetI.mass_pr1  ).push_back(lPruned1      .m());
  (iJetI.mass_pr2    ).push_back(lPruned2      .m());
  (iJetI.mass_pr3    ).push_back(lPruned3      .m());
  (iJetI.mass_pr4    ).push_back(lPruned4      .m());
  (iJetI.mass_pr1_safe  ).push_back(lPrunedSafe1      .m());
  (iJetI.mass_pr2_safe    ).push_back(lPrunedSafe2      .m());
  (iJetI.mass_pr3_safe    ).push_back(lPrunedSafe3      .m());
  (iJetI.mass_pr4_safe    ).push_back(lPrunedSafe4      .m());
  (iJetI.mass_sd1  ).push_back(lSoftDropped1      .m());
  (iJetI.mass_sd2    ).push_back(lSoftDropped2      .m());
  (iJetI.mass_sd3    ).push_back(lSoftDropped3      .m());
  (iJetI.mass_sd4    ).push_back(lSoftDropped4      .m());
  (iJetI.mass_sd5    ).push_back(lSoftDropped5      .m());
  (iJetI.mass_sd1_safe  ).push_back(lSoftDroppedSafe1      .m());
  (iJetI.mass_sd2_safe    ).push_back(lSoftDroppedSafe2      .m());
  (iJetI.mass_sd3_safe    ).push_back(lSoftDroppedSafe3      .m());
  (iJetI.mass_sd4_safe    ).push_back(lSoftDroppedSafe4      .m());
  (iJetI.mass_sd5_safe    ).push_back(lSoftDroppedSafe5      .m());


  (iJetI.mclean    ).push_back(lClean    .m());
  (iJetI.mtrim     ).push_back(lTrim     .m());
  (iJetI.mtrimsafe ).push_back(lTrimSafe .m());
  (iJetI.mpruned   ).push_back(lPruned   .m());
  (iJetI.mprunedsafe).push_back(lPrunedSafe.m());
  (iJetI.msoftdrop).push_back(lSoftDropped.m());
  (iJetI.msoftdropsafe).push_back(lSoftDroppedSafe.m());
  (iJetI.mconst    ).push_back(lConstit  .m());
  (iJetI.nparticles).push_back((iJet.constituents()).size());
  (iJetI.nneutrals ).push_back(neutrals.size());
  (iJetI.ncharged  ).push_back(chargedLV.size()+chargedPU.size());
    
  // some duplicate infos.... should be fixed.
  (iJetI.imatch      ).push_back((iJetI.pt).size()-1);
  (iJetI.ptgen       ).push_back(lCorr     .pt());
  (iJetI.pt_tr1_gen  ).push_back(lTrim1      .pt());
  (iJetI.pt_tr2_gen    ).push_back(lTrim2      .pt());
  (iJetI.pt_tr3_gen    ).push_back(lTrim3      .pt());
  (iJetI.pt_tr4_gen    ).push_back(lTrim4      .pt());
  (iJetI.pt_tr1_safe_gen  ).push_back(lTrimSafe1      .pt());
  (iJetI.pt_tr2_safe_gen    ).push_back(lTrimSafe2      .pt());
  (iJetI.pt_tr3_safe_gen    ).push_back(lTrimSafe3      .pt());
  (iJetI.pt_tr4_safe_gen    ).push_back(lTrimSafe4      .pt());
  (iJetI.pt_pr1_gen  ).push_back(lPruned1      .pt());
  (iJetI.pt_pr2_gen    ).push_back(lPruned2      .pt());
  (iJetI.pt_pr3_gen    ).push_back(lPruned3      .pt());
  (iJetI.pt_pr4_gen    ).push_back(lPruned4      .pt());
  (iJetI.pt_pr1_safe_gen  ).push_back(lPrunedSafe1      .pt());
  (iJetI.pt_pr2_safe_gen    ).push_back(lPrunedSafe2      .pt());
  (iJetI.pt_pr3_safe_gen    ).push_back(lPrunedSafe3      .pt());
  (iJetI.pt_pr4_safe_gen    ).push_back(lPrunedSafe4      .pt());
  (iJetI.pt_sd1_gen  ).push_back(lSoftDropped1      .pt());
  (iJetI.pt_sd2_gen    ).push_back(lSoftDropped2      .pt());
  (iJetI.pt_sd3_gen    ).push_back(lSoftDropped3      .pt());
  (iJetI.pt_sd4_gen    ).push_back(lSoftDropped4      .pt());
  (iJetI.pt_sd5_gen    ).push_back(lSoftDropped5      .pt());
  (iJetI.pt_sd1_safe_gen  ).push_back(lSoftDroppedSafe1      .pt());
  (iJetI.pt_sd2_safe_gen    ).push_back(lSoftDroppedSafe2      .pt());
  (iJetI.pt_sd3_safe_gen    ).push_back(lSoftDroppedSafe3      .pt());
  (iJetI.pt_sd4_safe_gen    ).push_back(lSoftDroppedSafe4      .pt());
  (iJetI.pt_sd5_safe_gen    ).push_back(lSoftDroppedSafe5      .pt());




  (iJetI.etagen      ).push_back(iJet      .eta());
  (iJetI.eta_tr1_gen  ).push_back(lTrim1      .eta());
  (iJetI.eta_tr2_gen    ).push_back(lTrim2      .eta());
  (iJetI.eta_tr3_gen    ).push_back(lTrim3      .eta());
  (iJetI.eta_tr4_gen    ).push_back(lTrim4      .eta());
  (iJetI.eta_tr1_safe_gen  ).push_back(lTrimSafe1      .eta());
  (iJetI.eta_tr2_safe_gen    ).push_back(lTrimSafe2      .eta());
  (iJetI.eta_tr3_safe_gen    ).push_back(lTrimSafe3      .eta());
  (iJetI.eta_tr4_safe_gen    ).push_back(lTrimSafe4      .eta());
  (iJetI.eta_pr1_gen  ).push_back(lPruned1      .eta());
  (iJetI.eta_pr2_gen    ).push_back(lPruned2      .eta());
  (iJetI.eta_pr3_gen    ).push_back(lPruned3      .eta());
  (iJetI.eta_pr4_gen    ).push_back(lPruned4      .eta());
  (iJetI.eta_pr1_safe_gen  ).push_back(lPrunedSafe1      .eta());
  (iJetI.eta_pr2_safe_gen    ).push_back(lPrunedSafe2      .eta());
  (iJetI.eta_pr3_safe_gen    ).push_back(lPrunedSafe3      .eta());
  (iJetI.eta_pr4_safe_gen    ).push_back(lPrunedSafe4      .eta());
  (iJetI.eta_sd1_gen  ).push_back(lSoftDropped1      .eta());
  (iJetI.eta_sd2_gen    ).push_back(lSoftDropped2      .eta());
  (iJetI.eta_sd3_gen    ).push_back(lSoftDropped3      .eta());
  (iJetI.eta_sd4_gen    ).push_back(lSoftDropped4      .eta());
  (iJetI.eta_sd5_gen    ).push_back(lSoftDropped5      .eta());
  (iJetI.eta_sd1_safe_gen  ).push_back(lSoftDroppedSafe1      .eta());
  (iJetI.eta_sd2_safe_gen    ).push_back(lSoftDroppedSafe2      .eta());
  (iJetI.eta_sd3_safe_gen    ).push_back(lSoftDroppedSafe3      .eta());
  (iJetI.eta_sd4_safe_gen    ).push_back(lSoftDroppedSafe4      .eta());
  (iJetI.eta_sd5_safe_gen    ).push_back(lSoftDroppedSafe5      .eta());



  (iJetI.phigen      ).push_back(iJet      .phi());
  (iJetI.phi_tr1_gen  ).push_back(lTrim1      .phi());
  (iJetI.phi_tr2_gen    ).push_back(lTrim2      .phi());
  (iJetI.phi_tr3_gen    ).push_back(lTrim3      .phi());
  (iJetI.phi_tr4_gen    ).push_back(lTrim4      .phi());
  (iJetI.phi_tr1_safe_gen  ).push_back(lTrimSafe1      .phi());
  (iJetI.phi_tr2_safe_gen    ).push_back(lTrimSafe2      .phi());
  (iJetI.phi_tr3_safe_gen    ).push_back(lTrimSafe3      .phi());
  (iJetI.phi_tr4_safe_gen    ).push_back(lTrimSafe4      .phi());
  (iJetI.phi_pr1_gen  ).push_back(lPruned1      .phi());
  (iJetI.phi_pr2_gen    ).push_back(lPruned2      .phi());
  (iJetI.phi_pr3_gen    ).push_back(lPruned3      .phi());
  (iJetI.phi_pr4_gen    ).push_back(lPruned4      .phi());
  (iJetI.phi_pr1_safe_gen  ).push_back(lPrunedSafe1      .phi());
  (iJetI.phi_pr2_safe_gen    ).push_back(lPrunedSafe2      .phi());
  (iJetI.phi_pr3_safe_gen    ).push_back(lPrunedSafe3      .phi());
  (iJetI.phi_pr4_safe_gen    ).push_back(lPrunedSafe4      .phi());
  (iJetI.phi_sd1_gen  ).push_back(lSoftDropped1      .phi());
  (iJetI.phi_sd2_gen    ).push_back(lSoftDropped2      .phi());
  (iJetI.phi_sd3_gen    ).push_back(lSoftDropped3      .phi());
  (iJetI.phi_sd4_gen    ).push_back(lSoftDropped4      .phi());
  (iJetI.phi_sd5_gen    ).push_back(lSoftDropped5      .phi());
  (iJetI.phi_sd1_safe_gen  ).push_back(lSoftDroppedSafe1      .phi());
  (iJetI.phi_sd2_safe_gen    ).push_back(lSoftDroppedSafe2      .phi());
  (iJetI.phi_sd3_safe_gen    ).push_back(lSoftDroppedSafe3      .phi());
  (iJetI.phi_sd4_safe_gen    ).push_back(lSoftDroppedSafe4      .phi());
  (iJetI.phi_sd5_safe_gen    ).push_back(lSoftDroppedSafe5      .phi());


  (iJetI.mgen        ).push_back(lCorr     .m());
  (iJetI.mass_tr1_gen  ).push_back(lTrim1      .m());
  (iJetI.mass_tr2_gen    ).push_back(lTrim2      .m());
  (iJetI.mass_tr3_gen    ).push_back(lTrim3      .m());
  (iJetI.mass_tr4_gen    ).push_back(lTrim4      .m());
  (iJetI.mass_tr1_safe_gen  ).push_back(lTrimSafe1      .m());
  (iJetI.mass_tr2_safe_gen    ).push_back(lTrimSafe2      .m());
  (iJetI.mass_tr3_safe_gen    ).push_back(lTrimSafe3      .m());
  (iJetI.mass_tr4_safe_gen    ).push_back(lTrimSafe4      .m());
  (iJetI.mass_pr1_gen  ).push_back(lPruned1      .m());
  (iJetI.mass_pr2_gen    ).push_back(lPruned2      .m());
  (iJetI.mass_pr3_gen    ).push_back(lPruned3      .m());
  (iJetI.mass_pr4_gen    ).push_back(lPruned4      .m());
  (iJetI.mass_pr1_safe_gen  ).push_back(lPrunedSafe1      .m());
  (iJetI.mass_pr2_safe_gen    ).push_back(lPrunedSafe2      .m());
  (iJetI.mass_pr3_safe_gen    ).push_back(lPrunedSafe3      .m());
  (iJetI.mass_pr4_safe_gen    ).push_back(lPrunedSafe4      .m());
  (iJetI.mass_sd1_gen  ).push_back(lSoftDropped1      .m());
  (iJetI.mass_sd2_gen    ).push_back(lSoftDropped2      .m());
  (iJetI.mass_sd3_gen    ).push_back(lSoftDropped3      .m());
  (iJetI.mass_sd4_gen    ).push_back(lSoftDropped4      .m());
  (iJetI.mass_sd5_gen    ).push_back(lSoftDropped5      .m());
  (iJetI.mass_sd1_safe_gen  ).push_back(lSoftDroppedSafe1      .m());
  (iJetI.mass_sd2_safe_gen    ).push_back(lSoftDroppedSafe2      .m());
  (iJetI.mass_sd3_safe_gen    ).push_back(lSoftDroppedSafe3      .m());
  (iJetI.mass_sd4_safe_gen    ).push_back(lSoftDroppedSafe4      .m());
  (iJetI.mass_sd5_safe_gen    ).push_back(lSoftDroppedSafe5      .m()); 



  (iJetI.mrawgen     ).push_back(iJet      .m());
  (iJetI.mtrimgen    ).push_back(lTrim     .m());
  (iJetI.mtrimsafegen).push_back(lTrimSafe .m());
  (iJetI.mcleangen   ).push_back(lClean    .m());
  (iJetI.mconstgen   ).push_back(lConstit  .m());
}


// ------------------------------------------------------------------------------------------
void fillGenJetsInfo(vector<PseudoJet> &iJets, JetDefinition jet_def_, vector<PseudoJet> &iParticles, JetInfo &iJetInfo, JetCleanser &gsn_cleanser, int nPU ){

  // -- Compute rho, rho_m for SafeAreaSubtraction
  AreaDefinition area_def(active_area_explicit_ghosts,GhostedAreaSpec(SelectorAbsRapMax(5.0)));
  JetDefinition jet_def_for_rho(kt_algorithm, 0.4);
  Selector rho_range =  SelectorAbsRapMax(5.0);
  ClusterSequenceArea clust_seq_rho(iParticles, jet_def_for_rho, area_def);
  JetMedianBackgroundEstimator bge_rho(rho_range, clust_seq_rho);
  JetMedianBackgroundEstimator bge_rhom(rho_range, clust_seq_rho);
  BackgroundJetPtMDensity m_density;
  bge_rhom.set_jet_density_class(&m_density);
  
  //// use GridMedianBackgroundEstimator (faster), however doesn't work with SafeAreaSubtraction
  //GridMedianBackgroundEstimator bge_rho(5.0,0.8);
  //bge_rho.set_particles(iParticles);
  //GridMedianBackgroundEstimator bge_rhom(5.0,0.8);
  //bge_rhom.set_particles(iParticles);
  
  // -- Background estimator for constituents subtractor
  JetMedianBackgroundEstimator bge_rhoC(rho_range,jet_def_for_rho, area_def);
  BackgroundJetScalarPtDensity *scalarPtDensity = new BackgroundJetScalarPtDensity();
  bge_rhoC.set_jet_density_class(scalarPtDensity);
  bge_rhoC.set_particles(iParticles);
    
  // -- Clear jet info for each event                                                                                                                                                                                                  
  clear(iJetInfo);
  
  iJetInfo.npu = nPU;

  // -- Loop over jets in the event and set jets variables                                                                                                                                                                      
  for (unsigned int j = 0; j < iJets.size(); j++){
    setGenJet( iJets[j], iJetInfo,  jet_def_, bge_rho, bge_rhom, bge_rhoC, gsn_cleanser);
    //cout << iTree.GetName() << "  " << (iJetInfo.pt)[j] << "  "<< (iJetInfo.ptcorr)[j] <<endl;                                                                                                                                      
  }

}
// ------------------------------------------------------------------------------------------


void fillRecoJetsInfo(vector<PseudoJet> &iJets, JetDefinition jet_def_, vector<PseudoJet> &iParticles, JetInfo &iJetInfo, JetInfo iGenJetInfo, bool isCHS, FactorizedJetCorrector *jetCorr, JetCorrectionUncertainty *ijetUnc,
		      JetCleanser &gsn_cleanser, int nPU ){
  
  // -- Compute rho, rho_m for SafeAreaSubtraction
  AreaDefinition area_def(active_area_explicit_ghosts,GhostedAreaSpec(SelectorAbsRapMax(5.0)));
  JetDefinition jet_def_for_rho(kt_algorithm, 0.4);
  Selector rho_range =  SelectorAbsRapMax(5.0);
  ClusterSequenceArea clust_seq_rho(iParticles, jet_def_for_rho, area_def);
  JetMedianBackgroundEstimator bge_rho(rho_range, clust_seq_rho);
  JetMedianBackgroundEstimator bge_rhom(rho_range, clust_seq_rho);
  BackgroundJetPtMDensity m_density;
  bge_rhom.set_jet_density_class(&m_density);
  
  //// use GridMedianBackgroundEstimator (faster), however doesn't work with SafeAreaSubtraction
  //GridMedianBackgroundEstimator bge_rho(5.0,0.8);
  //bge_rho.set_particles(iParticles);
  //GridMedianBackgroundEstimator bge_rhom(5.0,0.8);
  //bge_rhom.set_particles(iParticles);
  
  // -- Background estimator for constituents subtractor
  JetMedianBackgroundEstimator bge_rhoC(rho_range,jet_def_for_rho, area_def);
  BackgroundJetScalarPtDensity *scalarPtDensity = new BackgroundJetScalarPtDensity();
  bge_rhoC.set_jet_density_class(scalarPtDensity);
  bge_rhoC.set_particles(iParticles);
    
  // -- Clear jet info for each event                                                                                                                                                                                                  
  clear(iJetInfo);
  
  iJetInfo.npu = nPU;

  // -- Loop over jets in the event and set jets variables                                                                                                                                                                      
  for (unsigned int j = 0; j < iJets.size(); j++){
    setRecoJet( iJets[j], iJetInfo, iGenJetInfo, jet_def_,bge_rho, bge_rhom, bge_rhoC, isCHS, jetCorr, ijetUnc, gsn_cleanser);
    //cout << iTree.GetName() << "  " << (iJetInfo.pt)[j] << "  "<< (iJetInfo.ptcorr)[j] <<endl;                                                                                                                                      
  }

}

// ------------------------------------------------------------------------------------------
void setupCMSSWJetReadOut(TTree *iTree, float R ) {
  
  cout << "Setting up to read jet collection : " << Form("Jet0%d",int(R*10)) << endl;
  fJet  = new TClonesArray("baconhep::TJet");
  iTree->SetBranchAddress(Form("Jet0%d",int(R*10)), &fJet);
  fJetBr  = iTree->GetBranch(Form("Jet0%d",int(R*10)));
}
// ------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------
void readCMSSWJet(int entry, TTree *iTree, TTree &oTree,  std::vector<fastjet::PseudoJet> genJets, JetInfo &iJetI) {


  // -- Clear jet info for each event
  clear(iJetI);

  // -- Read event and fill jet info
  iTree->GetEntry(entry);

  for (int i = 0; i < fJet->GetEntriesFast(); i++){
    TJet *pJet = (TJet*)((*fJet)[i]);
    
    // -- fill jet info                                                                                                                                                                                                       
    (iJetI.pt        ).push_back(pJet->pt);
    (iJetI.ptcorr    ).push_back(pJet->pt);
    (iJetI.ptraw     ).push_back(pJet->ptRaw);
    (iJetI.eta       ).push_back(pJet->eta);
    (iJetI.phi       ).push_back(pJet->phi);
    (iJetI.m         ).push_back(pJet->mass);
    (iJetI.nparticles).push_back(pJet->nParticles);
    (iJetI.nneutrals ).push_back(pJet->nNeutrals);
    (iJetI.ncharged  ).push_back(pJet->nCharged);
    

    // for now fill this branches with dummy value
    (iJetI.ptclean   ).push_back(-999.);
    (iJetI.pttrim    ).push_back(-999.);
    (iJetI.pttrimsafe).push_back(-999.);
    (iJetI.ptconst   ).push_back(-999.);
    (iJetI.ptunc     ).push_back(-999.);
    (iJetI.eta       ).push_back(-999.);
    (iJetI.phi       ).push_back(-999.);
    (iJetI.mraw      ).push_back(-999.);
    (iJetI.mclean    ).push_back(-999.);
    (iJetI.mtrim     ).push_back(-999.);
    (iJetI.mtrimsafe ).push_back(-999.);
    (iJetI.mpruned   ).push_back(-999.);
    (iJetI.mprunedsafe).push_back(-999.);
    (iJetI.msoftdrop).push_back(-999.);
    (iJetI.msoftdropsafe).push_back(-999.);
    (iJetI.mconst    ).push_back(-999.);
  
    //-- gen matching
    int imatch = -1;
    double mindr = 0.3;
    TLorentzVector *recojet = new TLorentzVector();
    recojet->SetPtEtaPhiM(pJet->pt, pJet->eta, pJet->phi, pJet->mass);
    for (unsigned int ig = 0; ig < genJets.size(); ig++){
      TLorentzVector *genjet = new TLorentzVector();
      genjet->SetPtEtaPhiM(genJets[ig].pt(), genJets[ig].eta(), genJets[ig].phi(), genJets[ig].m());
      double dr = recojet->DeltaR(*genjet);
      if (dr < mindr){
	mindr = dr;
	imatch = ig;
      }
      delete genjet;
    }
    
    delete recojet;

    if (imatch > -1){
      (iJetI.ptgen    ).push_back(genJets[imatch].pt());
      (iJetI.etagen   ).push_back(genJets[imatch].eta());
      (iJetI.phigen   ).push_back(genJets[imatch].phi());
      (iJetI.mgen     ).push_back(genJets[imatch].m());
      (iJetI.imatch   ).push_back(imatch);
    }
    else {
      (iJetI.ptgen    ).push_back(-999.);
      (iJetI.etagen   ).push_back(-999.);
      (iJetI.phigen   ).push_back(-999.);
      (iJetI.mgen     ).push_back(-999.);
      (iJetI.imatch   ).push_back(imatch);
    }
  }

  // --- fill tree 
  oTree.Fill();
  
}
// ------------------------------------------------------------------------------------------



// ------------------------------------------------------------------------------------------
bool FillChain(TChain& chain, const std::string& inputFileList)
{
  std::ifstream inFile(inputFileList.c_str());
  std::string buffer;

  if(!inFile.is_open())
    {
      std::cerr << "** ERROR: Can't open '" << inputFileList << "' for input" << std::endl;
      return false;
    }
  
  while(1)
    {
      inFile >> buffer;
      if(!inFile.good()) break;
      chain.Add(buffer.c_str());
    }

  return true;
}
// ------------------------------------------------------------------------------------------




//---------------------------------------------------------------------------------------------------------------
//--- MAIN PROGRAM
//---------------------------------------------------------------------------------------------------------------
int main (int argc, char ** argv) {

  // args 
  std::string inputFilesList = argv[1];        // input file name
  int maxEvents              = atoi(argv[2]);  // max events
  cout<<"Bibhu Maximum events = "<<maxEvents<<endl;

  std::string fOut           = argv[3];        // output name
  float jetR                 = atof(argv[4]);  // jet cone size      
  bool doCMSSWJets           = atoi(argv[5]);  // if want to analyze PF Jets from CMSSW

  // --- Read list of files to be analyzed and fill TChain
  TChain* lTree = new TChain("Events");
  FillChain(*lTree, inputFilesList);
  if (lTree->GetEntries() < maxEvents || maxEvents == -1) maxEvents = lTree->GetEntries(); 

  cout << "This analysis will run on "<< maxEvents << " events" <<endl; 

  // --- Load branches
  fPFCand = new PFLoader (lTree,"Puppi_cff.py");
  fGen    = new GenLoader(lTree);
  if (doCMSSWJets) setupCMSSWJetReadOut(lTree, jetR);

  TEventInfo *eventInfo = new TEventInfo();
  lTree->SetBranchAddress("Info",&eventInfo);

  // --- Setup JEC on the fly
 // std::string cmsenv = "/afs/cern.ch/user/p/pharris/pharris/public/bacon/prod/CMSSW_6_2_7_patch2/src/";
  std::string cmsenv = "/afs/cern.ch/user/b/bmahakud/public/JEC/";

  std::vector<JetCorrectorParameters> corrParams;
 // corrParams.push_back(JetCorrectorParameters(cmsenv+"BaconProd/Utils/data/Summer13_V1_MC_L1FastJet_AK5PF.txt"));
  corrParams.push_back(JetCorrectorParameters(cmsenv+"POSTLS162_V5_L1FastJet_AK7PF.txt"));
 // corrParams.push_back(JetCorrectorParameters(cmsenv+"BaconProd/Utils/data/Summer13_V1_MC_L2Relative_AK5PF.txt"));
   corrParams.push_back(JetCorrectorParameters(cmsenv+"POSTLS162_V5_L2Relative_AK7PF.txt"));
 // corrParams.push_back(JetCorrectorParameters(cmsenv+"BaconProd/Utils/data/Summer13_V1_MC_L3Absolute_AK5PF.txt"));
    corrParams.push_back(JetCorrectorParameters(cmsenv+"POSTLS162_V5_L3Absolute_AK7PF.txt"));

  //corrParams.push_back(JetCorrectorParameter(cmsenv+'BaconProd/Utils/data/Summer13_V1_DATA_L2L3Residual_AK5PF.txt'));
 // JetCorrectorParameters     param(cmsenv+"BaconProd/Utils/data/Summer13_V1_DATA_Uncertainty_AK5PF.txt");
  JetCorrectorParameters     param(cmsenv+"POSTLS162_V5_Uncertainty_AK7PF.txt");

  FactorizedJetCorrector   *jetCorr = new FactorizedJetCorrector(corrParams);
  JetCorrectionUncertainty *jetUnc  = new JetCorrectionUncertainty(param);

  // --- Setup JetAlgos
  JetDefinition jet_def(antikt_algorithm,jetR);         // the jet definition....
  JetDefinition jet_def_Pruning(antikt_algorithm,0.3);//this is a jet algorithm for pruning. Smaller radius to be used
  AreaDefinition area_def(active_area_explicit_ghosts,GhostedAreaSpec(SelectorAbsRapMax(5.0)));
  
  // --- Setup cleansing
  JetDefinition subjet_def(kt_algorithm,0.2);
  JetCleanser gsn_cleanser(subjet_def,JetCleanser::gaussian_cleansing,JetCleanser::input_nc_separate);
  gsn_cleanser.SetGaussianParameters(0.617,0.62,0.15,0.22);

  // --- Setup output trees
  TFile *fout = new TFile(fOut.c_str(),"RECREATE");

  TTree *genTree   = new TTree("gen"  , "gen"  );
  TTree *pfTree    = new TTree("pf"   , "pf"   );
  TTree *chsTree   = new TTree("chs"  , "chs"  );
  TTree *puppiTree = new TTree("puppi", "puppi");
  TTree *cmsswTree = new TTree("cmsswpf", "cmsswpf");

  JetInfo JGenInfo, JPFInfo, JCHSInfo, JPuppiInfo, JCMSSWPFInfo;    
  setupTree(genTree,   JGenInfo    , "" );
  setupTree(pfTree,    JPFInfo     , "" );
  setupTree(chsTree,   JCHSInfo    , "" );
  setupTree(puppiTree, JPuppiInfo  , "" );
  if (doCMSSWJets) setupTree(cmsswTree, JCMSSWPFInfo, "" );

  
  // --- start loop over events
  for(int ientry = 0; ientry < maxEvents; ientry++) { 

    if(ientry % 50 == 0) 
      std::cout << "===> Processed " << ientry << " - Done : " << (float(ientry)/float(maxEvents))*100 << "%" << std::endl;
   if(ientry % 20 == 0) std::cout << ientry << std::endl;
    // -- For each event build collections of particles (gen, puppi, etc..) to cluster
    fPFCand->load(ientry);
    fGen   ->load(ientry); 
    vector<PseudoJet> gen_event       = fGen   ->genFetch();
    vector<PseudoJet> pf_event        = fPFCand->pfFetch();
    vector<PseudoJet> chs_event       = fPFCand->pfchsFetch(-1);
    vector<PseudoJet> puppi_event     = fPFCand->puppiFetch();

    // -- Cluster jets
    ClusterSequenceArea pGen    (gen_event    , jet_def, area_def);
    ClusterSequenceArea pPup    (puppi_event  , jet_def, area_def);
    ClusterSequenceArea pPF     (pf_event     , jet_def, area_def);
    ClusterSequenceArea pCHS    (chs_event    , jet_def, area_def);

    vector<PseudoJet> genJets     = sorted_by_pt(pGen    .inclusive_jets(25.));
    vector<PseudoJet> puppiJets   = sorted_by_pt(pPup    .inclusive_jets(25.));
    vector<PseudoJet> pfJets      = sorted_by_pt(pPF     .inclusive_jets(25.));
    vector<PseudoJet> chsJets     = sorted_by_pt(pCHS    .inclusive_jets(25.));

    lTree->GetEntry(ientry);
    int nPU = eventInfo->nPU;

    // save jet info in a tree
    fillGenJetsInfo(genJets, jet_def_Pruning, gen_event, JGenInfo, gsn_cleanser, nPU);
    fillRecoJetsInfo(puppiJets, jet_def_Pruning, puppi_event, JPuppiInfo, JGenInfo, false, jetCorr, jetUnc, gsn_cleanser,nPU);
    fillRecoJetsInfo(pfJets , jet_def_Pruning, pf_event   , JPFInfo   , JGenInfo, false, jetCorr, jetUnc, gsn_cleanser,nPU);
    fillRecoJetsInfo(chsJets, jet_def_Pruning, chs_event  , JCHSInfo  , JGenInfo, true , jetCorr, jetUnc, gsn_cleanser,nPU);

    genTree->Fill();
    puppiTree->Fill();
    pfTree->Fill();
    chsTree->Fill();

    if (doCMSSWJets)
      readCMSSWJet(ientry, lTree, *cmsswTree, genJets, JCMSSWPFInfo);
    
  }


  // --- Write trees 
  fout->cd();

  genTree  ->Write();
  pfTree   ->Write();
  chsTree  ->Write();
  puppiTree->Write();

  if (doCMSSWJets)  cmsswTree->Write();
}  
