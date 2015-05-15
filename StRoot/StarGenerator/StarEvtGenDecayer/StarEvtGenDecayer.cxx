#include <list>

#include "TParticle.h"
#include "TLorentzVector.h"
#include "TClonesArray.h"

#include "EvtGenBase/EvtStdlibRandomEngine.hh"
#include "EvtGenBase/EvtRandom.hh"
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtAbsRadCorr.hh"
#include "EvtGenExternal/EvtExternalGenList.hh"
#include "EvtGenBase/EvtParticleFactory.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtId.hh"
#include "EvtGenBase/EvtDecayBase.hh"

#include "StarEvtGenDecayer.h"

StarEvtGenDecayer::StarEvtGenDecayer(EvtGen* evtGen): mEvtGenRandomEngine(NULL), mEvtGen(NULL), mParticle(NULL), mOwner(false)
{
  if(mEvtGen) return; // trust that mEvtGen is properly initialized by the user

  mOwner = true;

  mEvtGenRandomEngine = new EvtStdlibRandomEngine();
  EvtRandom::setRandomEngine((EvtRandomEngine*)mEvtGenRandomEngine);
  EvtExternalGenList genList;

  EvtAbsRadCorr* radCorrEngine = genList.getPhotosModel();
  std::list<EvtDecayBase*> extraModels = genList.getListOfModels();
  
  // the hardcoded paths are temporary
  mEvtGen = new EvtGen("../../DECAY_2010.DEC","../../evt.pdl", (EvtRandomEngine*)mEvtGenRandomEngine,radCorrEngine, &extraModels);

}

StarEvtGenDecayer::~StarEvtGenDecayer()
{
  if(mOwner)
  {
    delete mEvtGen;
    delete mEvtGenRandomEngine;
  }
}

void StarEvtGenDecayer::Init()
{
   LOG_INFO << " Init Done" << endm;
}
void StarEvtGenDecayer::Decay(int pdgId, TLorentzVector*_p)
{
   EvtVector4R p_init(_p->E(), _p->Px(), _p->Py(), _p->Pz());

   EvtId parentID = EvtPDL::evtIdFromLundKC(pdgId);
   mParticle = EvtParticleFactory::particleFactory(parentID, p_init);
   mParticle->setDiagonalSpinDensity();
   mEvtGen->generateDecay(mParticle);
}

Int_t StarEvtGenDecayer::ImportParticles(TClonesArray* particles)
{
   //save Decay daughter
   assert(particles);
   TClonesArray &array = *particles;
   array.Clear();
   Int_t nparts = 0;
   for (Int_t i = 0; i < mParticle->getNDaug(); i++)
   {
      new(array[nparts++]) TParticle(
         EvtPDL::getLundKC(mParticle->getDaug(i)->getId()),
         -999,
         EvtPDL::getLundKC(mParticle->getDaug(i)->getParent()->getId()),
         -999,
         -999,
         -999,
         mParticle->getDaug(i)->getP4Lab().get(1),
         mParticle->getDaug(i)->getP4Lab().get(2),
         mParticle->getDaug(i)->getP4Lab().get(3),
         mParticle->getDaug(i)->getP4Lab().get(0),
         mParticle->getDaug(i)->get4Pos().get(1),
         mParticle->getDaug(i)->get4Pos().get(2),
         mParticle->getDaug(i)->get4Pos().get(3),
         mParticle->getDaug(i)->get4Pos().get(0));
   }

   mParticle->deleteTree(); // this deletes the daughter and mParticle itself (the object commits suicide)
   return nparts;
}
void StarEvtGenDecayer::SetForceDecay(Int_t type)
{
   assert(0);
}

void StarEvtGenDecayer::ForceDecay()
{
   assert(0);
}
Float_t StarEvtGenDecayer::GetPartialBranchingRatio(Int_t ipart)
{
   assert(0);
}
void StarEvtGenDecayer::ReadDecayTable()
{
   assert(0);
}
Float_t StarEvtGenDecayer::GetLifetime(Int_t pdg)
{
   return 1.0;
}
