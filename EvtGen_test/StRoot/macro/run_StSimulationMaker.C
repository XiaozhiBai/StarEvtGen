void run_StSimulationMaker(int parent_pdg=421,int NEvent=2000000,TString outfile="test_production.root")
{
   std::cout<< outfile<<std::endl;
   gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
   loadSharedLibraries();
   gSystem->Load(".sl64_gcc447/lib/libStSimulationMaker.so");
   gSystem->Load("/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/evtgen/1.3.0/lib/libEvtGen.so");
   gSystem->Load("/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/evtgen/1.3.0/lib/libEvtGenExternal.so");
   gSystem->Load("/star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/pythia8/186/lib/libpythia8.so");
   gSystem->Load(".sl64_gcc447/lib/libStarEvtGenDecayer.so");

   StSimulationMaker* MC = new StSimulationMaker(parent_pdg,NEvent,outfile);
  MC->OpenFile();


  MC->make();
  MC->SaveTree();
}
