/*/-----------------

  This class is for the eventGen Decay

  Auther:  Xiaozhi 5/1/2015

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

 using namespace std;

const double accp_eta=1.0;
//ClassImp(StEvtGenDecayer)
void get_kinematics(Double_t& pt, Double_t& eta, Double_t& phi, Double_t& px, Double_t& py, Double_t& pz);

int main(int argc, char* argv[])
{
  if(argc!=4)
  {
	  cout<<"Usage: "<<argv[0]<<" #NumOfEvents #PDGID #DAUGHTERID"<<endl;
	  return 1;
  }

  // StEvtGenDecayer *Decay;
  //************************************************ set up the EvetGen *****************************// 
  EvtStdlibRandomEngine * eng = new EvtStdlibRandomEngine();
  EvtRandom::setRandomEngine((EvtRandomEngine*)eng);
  EvtAbsRadCorr* radCorrEngine = 0;
  std::list<EvtDecayBase*> extraModels;

#ifdef EVTGEN_EXTERNAL
  EvtExternalGenList genList;
  radCorrEngine = genList.getPhotosModel();
  extraModels = genList.getListOfModels();
#endif
  //************************************************ set up the EvetGen *****************************// 
  
  //Initialize the generator - read in the decay table and particle properties
  
  EvtGen myGenerator("../../DECAY_2010.DEC","../../evt.pdl", (EvtRandomEngine*)eng,radCorrEngine, &extraModels);
  static EvtId ParentID=EvtPDL::evtIdFromLundKC(atoi(argv[2]));
  static EvtId DaughterID=EvtPDL::evtIdFromLundKC(atoi(argv[3]));
  int ParentID_pdg=atoi(argv[2]);


  
  //  StarEvtGenDecayer Event(myGenerator,atoi(argv[1]),ParentID,DaughterID);
  StarEvtGenDecayer *Decay_Event=new StarEvtGenDecayer();//myGenerator,atoi(argv[1]),ParentID,DaughterID);
 
  // TString Decay_file="exampleFiles/PI0DALITZ.DEC";

  TString Decay_file= "D0.DEC";


  Decay_Event->Input_DecayTree(Decay_file);
  
  Double_t pt=0;
  Double_t eta=0;
  Double_t phi=0;
  Double_t px=0;
  Double_t py=0;
  Double_t pz=0;
  
  // input the flat pt (0,20);
  get_kinematics(pt,eta,phi,px,py,pz);
  Double_t m0= EvtPDL::getMass(ParentID);
  Double_t E=sqrt(m0*m0+px*px+py*py+pz*pz);
 
  
  TClonesArray *_array=new TClonesArray("TParticle");
  TLorentzVector *p_mom=new TLorentzVector(px,py,pz,E);
  
  for(Int_t iEvet=0;iEvet<100;iEvet++){
    
    cout<< "----------------------------Event index-"<<iEvet<<"Event index---------------------------------"<<endl;
    Decay_Event->Decay(ParentID_pdg,p_mom);
    int Ndaughter= Decay_Event->ImportParticles(_array);
    cout<<_array->GetEntries()<<endl;
    for(int iDaughter=0;iDaughter<Ndaughter;iDaughter++)
      {
	TParticle* particle = (TParticle*)_array->At(iDaughter);
	cout<< ""<<particle->GetPdgCode()<<particle->GetFirstMother()<< "  "<<particle->Pt()<<endl;
      }
  }
  return 0;
}
void get_kinematics(Double_t& pt, Double_t& eta, Double_t& phi, Double_t& px, Double_t& py, Double_t& pz)
{
  gRandom->SetSeed();
  pt = gRandom->Uniform(0,20);
  eta = gRandom->Uniform(-accp_eta,accp_eta);
  phi = TMath::TwoPi() * gRandom->Rndm();
  px = pt * cos(phi);
  py = pt * sin(phi);
  pz = pt / tan(2 * atan(exp(-eta)));
}
