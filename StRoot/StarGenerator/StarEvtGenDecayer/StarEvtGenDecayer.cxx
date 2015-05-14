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
#include<TClonesArray.h>
#include "TVirtualMCDecayer.h"
#include "TClonesArray.h"
#include "TString.h"
#include "vector"

#include "StarEvtGenDecayer.h"
using namespace std;

StarEvtGenDecayer::StarEvtGenDecayer() : mEvtGen(NULL)
{
}

StarEvtGenDecayer::~StarEvtGenDecayer()
{
}

void StarEvtGenDecayer::Input_DecayTree(TString Decay_Table)
{
   mEvtGen->readUDecay(Decay_Table);

   return;
}
void StarEvtGenDecayer::Init()
{
   LOG_INFO << " Init Done" << endm;
}
void StarEvtGenDecayer::Decay(int pdgid, TLorentzVector*_p)
{
   EvtVector4R p_init(_p->E(), _p->Px(), _p->Py(), _p->Pz());
   static EvtId ParentID = EvtPDL::evtIdFromLundKC(pdgid);
   EvtParticle* root_part = EvtParticleFactory::particleFactory(ParentID, p_init);
   root_part->setDiagonalSpinDensity();
   mEvtGen->generateDecay(root_part);
   mParticle = root_part;
   return ;
}
Int_t StarEvtGenDecayer::ImportParticles(TClonesArray *_array)
{
   //save Decay daughter
   assert(_array);
   TClonesArray &array = *_array;
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
   mParticle->deleteTree();
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
Float_t StarEvtGenDecayer::GetPartialBranchingRatio(Int_t ipdg)
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
