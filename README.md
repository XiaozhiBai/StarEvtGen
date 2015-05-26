###Authors:  
  Xiaozhi Bai (xiaozhi@uic.edu)  
  Mustafa Mustafa (mmustafa@lbl.gov),  
  Zhenyu Ye       (yezhenyu2003@gmail.com)

###How to run EvtGen external decayer class in STAR(RCF)  

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

You need to load the following share libraries:  
```bash
gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
loadSharedLibraries();
gSystem->Load("/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/evtgen/1.3.0/lib/libEvtGen.so");
gSystem->Load("/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/evtgen/1.3.0/lib/libEvtGenExternal.so");
gSystem->Load("/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/pythia8/186/lib/libpythia8.so");
gSystem->Load(".sl64_gcc447/lib/libStarEvtGenDecayer.so");
```
