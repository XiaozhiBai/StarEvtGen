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

//ClassImp(StarEvtGenDecayer)

int main(int argc, char* argv[])
{
  
  if(argc!=4)
  {
	  cout<<"Usage: "<<argv[0]<<" #NumOfEvents #PDGID #DAUGHTERID"<<endl;
	  return 1;
  }

  // StarEvtGenDecayer *Decay;
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
  
  
    StarEvtGenDecayer Event(myGenerator,atoi(argv[1]),ParentID,DaughterID);
  return 0;
}
