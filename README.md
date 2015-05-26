###Authors:  
  Xiaozhi Bai (xiaozhi@uic.edu)  
  Mustafa Mustafa (mmustafa@lbl.gov),  
  Zhenyu Ye       (yezhenyu2003@gmail.com)

###How to use EvtGen external decayer class in STAR(RCF)  

To setup your directory:  

```bash
mkdir TEST
cd TEST
git clone https://github.com/XiaozhiBai/StarEvtGen.git
cd StarEvtGen
starver DEV
source setup.csh
./cons.csh
```

You need to load the following shared libraries:  
```bash
gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
loadSharedLibraries();
gSystem->Load("/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/evtgen/1.3.0/lib/libEvtGen.so");
gSystem->Load("/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/evtgen/1.3.0/lib/libEvtGenExternal.so");
gSystem->Load("/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/pythia8/186/lib/libpythia8.so");
gSystem->Load(".sl64_gcc447/lib/libStarEvtGenDecayer.so");
```

###Code use example:     

Includes:  
```c++
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
#include "EvtGenExternal/EvtExternalGenList.hh"
```

Instantiation:  

```c++
EvtStdlibRandomEngine* eng = new EvtStdlibRandomEngine();
eng->setSeed(NULL);
EvtRandom::setRandomEngine((EvtRandomEngine*)eng);
EvtAbsRadCorr* radCorrEngine = 0;
std::list<EvtDecayBase*> extraModels;
  
EvtExternalGenList genList;
radCorrEngine = genList.getPhotosModel();
extraModels = genList.getListOfModels();
  
TString Decay_2010_DEC="/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/evtgen/1.3.0/DECAY_2010.DEC";
TString Evt_pdl="/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/evtgen/1.3.0/evt.pdl";
EvtGen *myGenerator=new EvtGen(Decay_2010_DEC,Evt_pdl,(EvtRandomEngine*)eng,radCorrEngine, &extraModels);
StarEvtGenDecayer *myStGenerator = new StarEvtGenDecayer(myGenerator); 
```
