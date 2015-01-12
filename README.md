PYTHIA 8 in Geant4 example
============

1. Installation
-------------------

        mkdir build
        cd build
        
        source /afs/cern.ch/sw/lcg/external/geant4/10.0.p02/x86_64-slc6-gcc47-opt/CMake-setup.sh
        export PYTHIA8DATA=/afs/cern.ch/sw/lcg/external/MCGenerators_lcgcmt67b/pythia8/186/x86_64-slc6-gcc47-opt/xmldoc
        
        cmake -DHEPMC_ROOT_DIR='/afs/cern.ch/sw/lcg/external/HepMC/2.06.08/x86_64-slc6-gcc47-opt/' -DPYTHIA8='/afs/cern.ch/sw/lcg/external/MCGenerators_lcgcmt67b/pythia8/186/x86_64-slc6-gcc47-opt/' -DCMAKE_INSTALL_PREFIX=. ..
        make

2. Choosing the primary generator
-------------------

2.1. Pythia 8 called for each event

Detail of Pythia processes and beam/target, energy need to be specified in Geant macro. Examples:

       hepmc_pythia8.in :

        /generator/select pythia8
        /generator/pythia8/read "HardQCD:all = on"
        /generator/pythia8/read "PhaseSpace:pTHatMin = 20."
        /generator/pythia8/init 2212 2212 14000.

2.2. Pythia8 event saved in HepMC format to ROOT file, read by Geant4:

       hepmc_ascii_Pythia8.in:

         /generator/select hepmcAscii
         /generator/hepmcAscii/open data_Pythia8ToAscii/example_MyPythia8.dat
         /run/beamOn 1


3. Geometry
-------------------

Geometry is read from the GDML file. All GDMLs are stored in gdml/ directory:

FCCSD.gdml - Complex detector with various EM calorimeters, hadron calorimeters, muon detectors (all sensitive detectors)

FCCOnedetector.gdl - Only one EM calorimeter (sensitive detector)

simple.gdml - Simple box as a detector


4. Running an example
-------------------

4.1 Without GUI

    For a simple geometry (box):

        ./FCCfastsim ../gdml/simple.gdml pythia.in

    For a complex geometry (with sensitive detectors):

        ./FCCfastsim ../gdml/FCCSD.gdml root.in

4.2 With GUI

    For a simple geometry (box):

        ./FCCfastsim ../gdml/simple.gdml

    For a complex geometry (with sensitive detectors):

        ./FCCfastsim ../gdml/FCCSD.gdml
