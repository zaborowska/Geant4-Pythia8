Geant4-Pythia8
==============

Geant 4 example of event generator moved from Pythia 6 to 8

____________________________________________________________________

1. Installation
-------------------

        mkdir build
        cd build
        source /afs/cern.ch/sw/lcg/external/geant4/10.0.p02/x86_64-slc6-gcc47-opt/CMake-setup.sh
        export PYTHIA8DATA=/afs/cern.ch/sw/lcg/external/MCGenerators_lcgcmt67b/pythia8/186/x86_64-slc6-gcc47-opt/xmldoc
        cmake -DHEPMC_ROOT_DIR='/afs/cern.ch/sw/lcg/external/HepMC/2.06.08/x86_64-slc6-gcc47-opt/' -DPYTHIA8='/afs/cern.ch/sw/lcg/external/MCGenerators_lcgcmt67b/pythia8/186/x86_64-slc6-gcc47-opt/' -DCMAKE_INSTALL_PREFIX=. ..
        make



2. How to run an example
-------------------

2.1. Reading from ASCII file produced by Pythia8->HepMC

        ./HepMCEx03 hepmc_ascii_Pythia8.in

2.2. Pythia 8 called for every event in Geant 4

        ./HepMCEx03 hepmc_pythia8.in

2.3. Graphically

        ./HepMVEx03
                /control/execute vis.mac
                /control/execute hepmc_ascii_pythia8.in
                /control/execute hepmc_pythia8.in


3. Producing ASCII file
-------------------

3.1. Installation

        cd ../../data_Pythia8ToAscii/
        mkdir build
        cd build
        cmake -DHEPMC_ROOT_DIR='/afs/cern.ch/sw/lcg/external/HepMC/2.06.08/x86_64-slc6-gcc47-opt/' -DPYTHIA8='/afs/cern.ch/sw/lcg/external/MCGenerators_lcgcmt67b/pythia8/186/x86_64-slc6-gcc47-opt/' - -DCMAKE_INSTALL_PREFIX=. ..

Edit main42.cmnd to change any generation detail


3.2. Produce an output

        build/main42 main42.cmnd example_MyPythia8.dat

