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

#include "TVirtualMCDecayer.h"
#include "TClonesArray.h"
#include "TString.h"
#include "vector"

#include "StarEvtGenDecayer.h"

using namespace std;

void StarEvtGenDecayer::Input_DecayTree(EvtGen &EventGenerator, TString DEC_file1 , TString DEC_file2)
{
   cout << "Decay_tree" << " " << DEC_file2 << "  " << DEC_file2 << endl;
   EventGenerator.readUDecay(DEC_file1);
   EventGenerator.readUDecay(DEC_file2);

   return;
}
StarEvtGenDecayer::StarEvtGenDecayer(EvtGen &Event, int Nevent, EvtId ParentID, EvtId DaughterID)
{
   ///
   std::cout << " " << Nevent << "  " << ParentID << "  " << DaughterID << "  " << endl;
   TString DEC_file1 = "exampleFiles/GENERIC.DEC";
   TString DEC_file2 = "exampleFiles/JPSITOLL.DEC";
   Input_DecayTree(Event, DEC_file1, DEC_file2);
   TLorentzVector mom;//(EvtPDL::getMass(ParentID),0.001,0.01,0.01);
   mom.SetPxPyPzE(0.001, 0.011, 0.012, 0.9);

   cout << mom.Perp() << endl;
   Init();

   Make_Decay(Event, Nevent, ParentID, DaughterID, mom);
}
void StarEvtGenDecayer::Make_Decay(EvtGen &Event, int Nevent, EvtId ParentID, EvtId DaughterID, TLorentzVector mom)
{

   cout << "Number of Evet    " << Nevent << endl;
   double e = mom.E();
   double px = mom.Px();
   double py = mom.Py();
   double pz = mom.Pz();
   cout << e << "  " << px << py << pz << endl;
// TClonesArray *_array;

   EvtVector4R p_init(EvtPDL::getMass(ParentID), px, py, pz);

   // return;
   for (int iEvent = 0; iEvent < Nevent; iEvent++)
   {
      std::vector<TParticle *> Daughter_ve;
      //   TParticle * daughter;
      EvtParticle* root_part = EvtParticleFactory::particleFactory(ParentID, p_init);
      root_part->setVectorSpinDensity();
      Event.generateDecay(root_part);
      EvtParticle *p = root_part;
      while (p != 0)
      {


         TParticle * daughter =      Save_daughter(p);

         // cout<< "  "<<iEvent<< "  "<< p->getId()<<endl;

         Daughter_ve.push_back(daughter);
         // cout<< daughter->Pt()<<endl;
         p = p->nextIter(root_part);

      }

      cout << "  vctor size" << Daughter_ve.size() << "  " << endl;
      for (size_t i = 0; i < Daughter_ve.size(); i++)
      {
         cout << Daughter_ve[i]->GetPdgCode() << endl;
      }

      root_part->deleteTree();
   }
}

TParticle*  StarEvtGenDecayer::Save_daughter(EvtParticle* p)
{
   if (!p)
   {
      cout << "No Particle" << endl;
      exit(0);
   }
   // do{
   int pdg_daughter = EvtPDL::getLundKC(p->getId());
   double PE = p->getP4Lab().get(0);
   double PX = p->getP4Lab().get(1);
   double PY = p->getP4Lab().get(2);
   double PZ = p->getP4Lab().get(3);
   double ct = p->get4Pos().get(0);
   double x = p->get4Pos().get(1);
   double y = p->get4Pos().get(2);
   double z = p->get4Pos().get(3);
   //  EvtParticle *Mother1= p->getParent();
   // EvtParticle *Mother2= Mother1->getParent();
   int pdg_Mother1 = 1; // EvtPDL::getLundKC(Mother1->getId());
   int pdg_Mother2 = 2; // =EvtPDL::getLundKC(Mother2->getId());
   TParticle *Daughter = new TParticle(pdg_daughter, 999, pdg_Mother1, pdg_Mother2, 3, 4, PX, PY, PZ, PE, x, y, z, ct);
   // Daughter_ve.push_back(Daughter);
   // p=p->nextIter(root_part);
   // }while(p!=0);
   return Daughter;

}


StarEvtGenDecayer::StarEvtGenDecayer(EvtGen &mEvent)
{
}
void StarEvtGenDecayer::Init()
{
   cout << " Init Done" << endl;
}
void StarEvtGenDecayer::Decay(int pdgid, TLorentzVector*_p)
{
}
Int_t StarEvtGenDecayer::ImportParticles(TClonesArray *_array)
{
   //save Decay daughter

   TClonesArray &array = *_array;
   array.Clear();

   return 0;
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
