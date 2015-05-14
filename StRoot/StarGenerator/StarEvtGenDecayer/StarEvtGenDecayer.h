/**
   \class StarEvtGenDecayer

   \brief STAR wrapper for EvtGen Decayer

   Authors: Xiaozhi Bai (xiaozhi@uic.edu),
            Mustafa Mustafa (mmustafa@lbl.gov),
*/

#ifndef StarEvtGenDecayer__h
#define StarEvtGenDecayer__h

#include "TVirtualMCDecayer.h"
#include "TString.h"

class EvtGen;
class EvtParticle;
class TLorentzVector;
class TClonesArray;

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
