/**
   \class StarEvtGenDecayer

   \brief STAR wrapper for EvtGen Decayer

   Authors: Xiaozhi Bai (xiaozhi@uic.edu),
            Mustafa Mustafa (mmustafa@lbl.gov),
            Zhenyu Ye       (yezhenyu2003@gmail.com)
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

   void setVertex(TLorentzVector* r);
   void setDecayTable(TString decayTable);

  private:
   EvtStdlibRandomEngine* mEvtGenRandomEngine;
   EvtGen* mEvtGen;
   EvtParticle* mParticle;
   EvtVector4R r_init;
   bool   mOwner;
};

inline void StarEvtGenDecayer::setDecayTable(TString decayTable) { mEvtGen->readUDecay(decayTable); }
inline void StarEvtGenDecayer::setVertex(TLorentzVector* r) {r_init.set(r->T(),r->X(),r->Y(),r->Z()); }
#endif
