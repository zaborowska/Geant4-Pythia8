Geant4-Pythia8
==============

Geant 4 example of event generator moved from Pythia 6 to 8

____________________________________________________________________

1. Installation
-------------------

1.1 Geant 4 example

        mkdir build
        cd build
        source /afs/cern.ch/sw/lcg/contrib/gcc/4.7.2/x86_64-slc6/setup.sh
        source /afs/cern.ch/sw/lcg/external/geant4/10.0.p02/x86_64-slc6-gcc47-opt/CMake-setup.sh
        cmake -DHEPMC_ROOT_DIR='/afs/cern.ch/sw/lcg/external/HepMC/2.06.08/x86_64-slc6-gcc47-opt/' -DCMAKE_INSTALL_PREFIX=. ..


2. How to run an example
-------------------

2.1. Reading from ASCII file produced by Pythia6->HepMC

        ./HepMCEx02 hepmc_ascii_Pythia6.in

2.2. Reading from ASCII file produced by Pythia8->HepMC

        ./HepMCEx02 hepmc_ascii_Pythia8.in

2.3. Graphically

        ./HepMVEx02
                /control/execute vis.mac
                /control/execute hepmc_ascii_pythia6.in
                /control/execute hepmc_ascii_pythia8.in


3. Producing ASCII file
-------------------

3.1. PYTHIA 6

3.1.1. Installation

        cd ../data_Pythia6ToAscii/
        mkdir build
        cd build
        cmake -DHEPMC_ROOT_DIR='/afs/cern.ch/sw/lcg/external/HepMC/2.06.08/x86_64-slc6-gcc47-opt/' -DPYTHIA6='/afs/cern.ch/sw/lcg/external/MCGenerators_lcgcmt67b/pythia6/428.2/x86_64-slc6-gcc47-opt/' -DCMAKE_INSTALL_PREFIX=. ..


Edit data_Pythia6ToAscii/example_MyPythia.cxx to change any generation detail and run make

3.1.2. Produce an output

in data_Pythia6ToAscii directory

        build/example_MyPythia 


3.2. PYTHIA 8

3.2.1. Installation

        cd ../../data_Pythia8ToAscii/
        mkdir build
        cd build
        cmake -DHEPMC_ROOT_DIR='/afs/cern.ch/sw/lcg/external/HepMC/2.06.08/x86_64-slc6-gcc47-opt/' -DPYTHIA8='/afs/cern.ch/sw/lcg/external/MCGenerators_lcgcmt67b/pythia8/186/x86_64-slc6-gcc47-opt/' - -DCMAKE_INSTALL_PREFIX=. ..

Edit main42.cmnd to change any generation detail


3.2.2. Produce an output

        export PYTHIA8DATA=/afs/cern.ch/sw/lcg/external/MCGenerators_lcgcmt67b/pythia8/186/x86_64-slc6-gcc47-opt/xmldoc
        build/main42 main42.cmnd example_MyPythia8.dat

