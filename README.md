###Authors:  
  Xiaozhi Bai (xiaozhi@uic.edu)  
  Mustafa Mustafa (mmustafa@lbl.gov),  
  Zhenyu Ye       (yezhenyu2003@gmail.com)

### Presentations:  
#### STAR Protected:  
- [EvtGen As External Decayer in StarSim](https://www.star.bnl.gov/protected/heavy/xiao00/Run14/STAR_S_C_meeting_6_10.pdf), Xiaozhi, S&amp;C , 2015-06-10.  

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

Please see `StRoot/StEvtGenTest/StEvtGenTest.cxx` for an example for how to instantiate this class.  
You will need to compile with the provided custmomized `cons.csh`.  
