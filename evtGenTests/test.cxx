/*/-----------------

  This class is for the eventGen production

  Auther:  Xiaozhi 5/1/2015 xiaozhi@uic.edu

  ----------------*/

#include "EvtGen/EvtGen.hh"

#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtParticleFactory.hh"
#include "EvtGenBase/EvtPatches.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtRandom.hh"
#include "EvtGenBase/EvtReport.hh"
#include "EvtGenBase/EvtHepMCEvent.hh"
#include "EvtGenBase/EvtStdlibRandomEngine.hh"
#include "EvtGenBase/EvtAbsRadCorr.hh"
#include "EvtGenBase/EvtDecayBase.hh"

#ifdef EVTGEN_EXTERNAL
#include "EvtGenExternal/EvtExternalGenList.hh"
#endif

#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <vector>
#include <fstream>

#include <TFile.h>
#include <TH1F.h>
#include"TParticle.h"
#include"TLorentzVector.h"
#include"TClonesArray.h"
#include "TVirtualMCDecayer.h"
#include "TClonesArray.h"
#include "TString.h"
#include "vector"
#include "TRandom.h"
#include "StarEvtGenDecayer.h"
#include "TNtuple.h"
#include "TFile.h"
#include "time.h"

 
using namespace std;
const double accp_eta=1.0;
const int MaxDaughter=10;
void get_kinematics(Double_t& pt, Double_t& eta, Double_t& phi, Double_t& px, Double_t& py, Double_t& pz);

int main(int argc, char* argv[])
{
  
  if(argc!=2)
    {
      std::cout<<"Usage: "<<argv[0]<<" #NumOfEvents #PDGID #DAUGHTERID"<<std::endl;
      return 1;
    }
  
  //   // // StEvtGenDecayer *Decay;
  //************************************************ set up the EvetGen *****************************// 
  EvtStdlibRandomEngine * eng = new EvtStdlibRandomEngine();
  eng->setSeed(NULL);
  EvtRandom::setRandomEngine((EvtRandomEngine*)eng);
  EvtAbsRadCorr* radCorrEngine = 0;
  std::list<EvtDecayBase*> extraModels;
  
#ifdef EVTGEN_EXTERNAL
  EvtExternalGenList genList;
  radCorrEngine = genList.getPhotosModel();
  extraModels = genList.getListOfModels();
#endif
  //  ************************************************ set up the EvetGen *****************************// 
  
  //Initialize the generator - read in the decay table and particle properties
  TString Decay_2010_DEC="/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/evtgen/1.3.0/DECAY_2010.DEC";
  TString Evt_pdl="/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/evtgen/1.3.0/evt.pdl";
  EvtGen *myGenerator=new EvtGen(Decay_2010_DEC,Evt_pdl,(EvtRandomEngine*)eng,radCorrEngine, &extraModels);
  StarEvtGenDecayer *Decay_Event=new StarEvtGenDecayer(myGenerator); 
   
  int ParentID_pdg_1=atoi(argv[1]);
   
  static EvtId ParentID_1=EvtPDL::evtIdFromLundKC(atoi(argv[1])); 
   
   
  TString Decay_file="NPE.DEC";
  Decay_Event->Input_DecayTree(Decay_file);
   
  Double_t pt=0;
  Double_t eta=0;
  Double_t phi=0;
  Double_t px=0;
  Double_t py=0;
  Double_t pz=0;
   
  TClonesArray *_array=new TClonesArray("TParticle");
   
  //lost+found/ TFile *file=new TFile("/star/data01/pwg/xiao00/EvtGen_DMeson_production.root","RECREATE");
  TFile *file=new TFile("test_EvtGen_DMeson_production.root","RECREATE");
   
  // TNtuple*   ntp_1 = new TNtuple("D0pTree", "D0pTree","mpdg:mpt:mEta:mPhi:mPx:mPy:mPz:mE:dpdg:dpt:dEta:dPhi:dPx:dPy:dPz:dE:dct"); 
  int Ndaughter_1=0;
   
  TTree* Tree_1 = new TTree("Tree_1","Tree_1");
   
  Int_t   mpdg_1[MaxDaughter];
  double  mPx_1[MaxDaughter];
  double  mPy_1[MaxDaughter];
  double  mPz_1[MaxDaughter];
  double  mE_1[MaxDaughter];  
  // double  dpt_1[MaxDaughter];
  // double  dEta_1[MaxDaughter];
  // double  dPhi_1[MaxDaughter];
  Int_t  dpdg_1[MaxDaughter]; 
  double  dPx_1[MaxDaughter];
  double  dPy_1[MaxDaughter];
  double  dPz_1[MaxDaughter];
  double  dE_1[MaxDaughter];  
  double  dct_1[MaxDaughter];
  Tree_1->Branch("Ndaughter_1",&Ndaughter_1,"Ndaughter_1/I");
  Tree_1->Branch("mpdg_1",mpdg_1,"mpdg_1[Ndaughter_1]/I");
  Tree_1->Branch("mPx_1",mPx_1,"mPx_1[Ndaughter_1]/D");
  Tree_1->Branch("mPy_1",mPy_1,"mPy_1[Ndaughter_1]/D");
  Tree_1->Branch("mPz_1",mPz_1,"mPz_1[Ndaughter_1]/D");
  Tree_1->Branch("mE_1",mE_1,"mE_1[Ndaughter_1]/D");

  Tree_1->Branch("dpdg_1",dpdg_1,"dpdg_1[Ndaughter_1]/I");   
  Tree_1->Branch("dPx_1",dPx_1,"dPx_1[Ndaughter_1]/D");
  Tree_1->Branch("dPy_1",dPy_1,"dPy_1[Ndaughter_1]/D");
  Tree_1->Branch("dPz_1",dPz_1,"dPz_1[Ndaughter_1]/D");
  Tree_1->Branch("dE_1",dE_1,"dE_1[Ndaughter_1]/D");
  Tree_1->Branch("dct_1",dct_1,"dct_1[Ndaughter_1]/D");

  for(Int_t iEvet=0;iEvet<4;iEvet++){  //  Event Loop              
    
    // if(iEvet%100==0)
    cout<< "---------working on Event "<<iEvet<<endl;
  

    //***********************
    // cout << myGenerator<<endl;
    //***************************

    get_kinematics(pt,eta,phi,px,py,pz);
    
    Double_t m0_1= EvtPDL::getMass(ParentID_1);
    Double_t E_1=sqrt(m0_1*m0_1+px*px+py*py+pz*pz);
     
    TLorentzVector *p_mom_1=new TLorentzVector(px,py,pz,E_1);
    //  for D0    
    Decay_Event->Decay(ParentID_pdg_1,p_mom_1);
    Ndaughter_1= Decay_Event->ImportParticles(_array);
  
    for(int iDaughter=0;iDaughter<_array->GetEntries();iDaughter++)
      {
	TParticle* particle = (TParticle*)_array->At(iDaughter);
	mpdg_1[iDaughter]=ParentID_pdg_1;
	mPx_1[iDaughter]=px;
	mPy_1[iDaughter]=py;
	mPz_1[iDaughter]=pz;
	mE_1[iDaughter]=E_1;  
	dpdg_1[iDaughter]=particle->GetPdgCode();
	dPx_1[iDaughter]=particle->Px();
	dPy_1[iDaughter]=particle->Py();
	dPz_1[iDaughter]=particle->Pz();
	dE_1[iDaughter]=particle->Energy();  
	dct_1[iDaughter]=particle->T();
	//	cout<< particle->GetPdgCode()<<endl;
	//float toFill[17]={ParentID_pdg_1,pt,eta,phi,px,py,pz,E_1,particle->GetPdgCode(),particle->Pt(),particle->Eta(),particle->Phi(),particle->Px(),particle->Py(),particle->Pz(),particle->Energy(),particle->T()};	 
	//ntp_1->Fill(toFill);	  
      }   // end Daughterloop

    Tree_1->Fill();
  } // end Evet loop
  
  file->cd();
  // ntp_1->Write();
  Tree_1->Write();  
  file->Close();
  return 0;
}
void get_kinematics(Double_t& pt, Double_t& eta, Double_t& phi, Double_t& px, Double_t& py, Double_t& pz)
{
  gRandom->SetSeed();
  pt = gRandom->Uniform(0.2,20);
  eta = gRandom->Uniform(-accp_eta,accp_eta);
  phi = TMath::TwoPi() * gRandom->Rndm();
  px = pt * cos(phi);
  py = pt * sin(phi);
  pz = pt / tan(2 * atan(exp(-eta)));
}
