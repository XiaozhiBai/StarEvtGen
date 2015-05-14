/**
   \class StarEvtGenDecayer

   \brief STAR wrapper for EvtGen Decayer

   Authors: Xiaozhi Bai (xiaozhi@uic.edu),
            Mustafa Mustafa (mmustafa@lbl.gov),
*/

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
   virtual ~StarEvtGenDecayer();

   virtual void Init();
   virtual void Decay(Int_t pdg, TLorentzVector* p);
   virtual Int_t ImportParticles(TClonesArray* particles);
   virtual void SetForceDecay(Int_t type);
   virtual void ForceDecay();
   virtual Float_t GetPartialBranchingRatio(Int_t ipart);
   virtual Float_t GetLifetime(Int_t pdgid);
   virtual void ReadDecayTable();


   void Input_DecayTree(TString Dec_file1);
  private:
   EvtGen *mEvtGen;
   int pdg;
   int mDebug;
   EvtParticle *mParticle;
   TClonesArray*        mDecayDaughter;
};
#endif
