/**
   \class StarEvtGenDecayer

   \brief STAR wrapper for EvtGen Decayer

   Authors: Xiaozhi Bai (xiaozhi@uic.edu),
            Mustafa Mustafa (mmustafa@lbl.gov)
*/

#ifndef StarEvtGenDecayer__h
#define StarEvtGenDecayer__h

#include <cstddef>

#include "TVirtualMCDecayer.h"
#include "TString.h"
#include "EvtGen/EvtGen.hh"

class TLorentzVector;
class TClonesArray;
class EvtStdlibRandomEngine;
class EvtParticle;

class StarEvtGenDecayer : public TVirtualMCDecayer
{
  public:
   StarEvtGenDecayer(EvtGen* evtGen = NULL);
   virtual ~StarEvtGenDecayer();

   virtual void Init();
   virtual void Decay(Int_t pdgId, TLorentzVector* p);
   virtual Int_t ImportParticles(TClonesArray* particles);
   virtual void SetForceDecay(Int_t type);
   virtual void ForceDecay();
   virtual Float_t GetPartialBranchingRatio(Int_t ipart);
   virtual Float_t GetLifetime(Int_t pdgid);
   virtual void ReadDecayTable();

   void setDecayTable(TString decayTable);

  private:
   EvtStdlibRandomEngine* mEvtGenRandomEngine;
   EvtGen* mEvtGen;
   EvtParticle* mParticle;
   bool   mOwner;
};

inline void StarEvtGenDecayer::setDecayTable(TString decayTable) { mEvtGen->readUDecay(decayTable); }
#endif
