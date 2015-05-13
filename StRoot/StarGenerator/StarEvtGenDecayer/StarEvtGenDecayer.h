  /*
   * This is just a test macro for the eventGen

  5/1/2015 by Xiaozhi

  ----------------*/
#ifndef StarEvtGenDecayer__h
#define StarEvtGenDecayer__h  

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
#include "TVirtualMCDecayer.h"
#include "TClonesArray.h"
#include "TString.h"
#include "vector"

class StarEvtGenDecayer : public TVirtualMCDecayer
{
 public:
  StarEvtGenDecayer();
  ~StarEvtGenDecayer();     
  
  void Init();
  void Decay( Int_t pdg, TLorentzVector *p=0 );
  Int_t ImportParticles(  TClonesArray *array = 0 );
  void SetForceDecay( Int_t type );
  void ForceDecay();
  Float_t GetPartialBranchingRatio( Int_t pdgid );
  Float_t GetLifetime( Int_t pdgid );
  void ReadDecayTable();
  //---------- added by xiaozhi-----------
 
  void Input_DecayTree(TString Dec_file1);
 private:
  int pdg; 
  EvtGen *mEvent;
  int mDebug;
  EvtParticle *mParticle;
  TClonesArray*        mDecayDaughter;
};     
#endif





