# Base directory where the EvtGen libraries are
BASEDIR = /star/u/xiao00/Run14/work_AuAu200_NPE/Simulation_NPE/Event_Gen/evtgen/1.3.0/

# Read in the config.mk file in the base directory to extract where
# the external libraries are, as well as setting compiler flags etc..

include ${BASEDIR}/config.mk
include extraConfig.mk

# Need to first add EvtGen libraries, then HepMC, then Photos, Tauola and Pythia,
# since Photos depends on HepMC etc..                                            

allLibDir=-L$(HEPMCLIBDIR)
allLibs=$(HEPMCLIBLIST)   

ifeq ("$(EVTGEN_PHOTOS)", "1")
        allLibDir+=-L$(PHOTOSLIBDIR)
        allLibs+=$(PHOTOSLIBLIST)   
endif

ifeq ("$(EVTGEN_PYTHIA)", "1")
        allLibDir+=-L$(PYTHIALIBDIR)
        allLibs+=$(PYTHIALIBLIST)
endif

ifeq ("$(EVTGEN_TAUOLA)", "1")
        allLibDir+=-L$(TAUOLALIBDIR)
        allLibs+=$(TAUOLALIBLIST)
endif

evtgenLibs=-lEvtGen
ifeq ($(EVTGEN_EXTERNAL),1)
	evtgenLibs+=-lEvtGenExternal
	EXTRAFLAGS+= -D EVTGEN_EXTERNAL
endif

GENLIBS = -L${BASEDIR}/lib ${allLibDir} -lgfortran ${allLibs} ${evtgenLibs}

INCLUDEDIR = ${BASEDIR}

CXXFLAGS      += $(ROOTCFLAGS)
CXXFLAGS      += -g
LIBS           = $(ROOTLIBS)
LIBS           += -lEG
NGLIBS         = $(ROOTGLIBS)
NGLIBS        += -lMinuit
GLIBS          = $(filter-out -lNew, $(NGLIBS))

.SUFFIXES: .cxx

# ================================================================================
default: test

test: StarEvtGenDecayer.o test.o
	$(CXX) $(CXXFLAGS) $(EXTRAFLAGS) -o test test.o StarEvtGenDecayer.o $(GENLIBS) $(LIBS)

.cxx.o:
	$(CXX) $(CXXFLAGS) $(EXTRAFLAGS) -c -o $@ $< -I$(INCLUDEDIR) -I$(HEPMCINCDIR)

clean:
	rm -f test *.o
