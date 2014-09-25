Geant4-Pythia8
==============

Geant 4 example of event generator moved from Pythia 6 to 8

____________________________________________________________________

1. HOW TO BEGIN
____________________________________________________________________

1.1. How to make an example
==============

mkdir build
cd build
source /afs/cern.ch/sw/lcg/contrib/gcc/4.7.2/x86_64-slc6/setup.sh
source /afs/cern.ch/sw/lcg/external/geant4/10.0.p02/x86_64-slc6-gcc47-opt/CMake-setup.sh
cmake -DHEPMC_ROOT_DIR='/afs/cern.ch/sw/lcg/external/HepMC/2.06.08/x86_64-slc6-gcc47-opt/' -DCMAKE_INSTALL_PREFIX=. ..


1.2. How to run an example
==============
1.2.1. Reading from ASCII file produced by Pythia6->HepMC
./HepMCEx02 hepmc_ascii_Pythia6.in

1.2.2. Reading from ASCII file produced by Pythia8->HepMC
./HepMCEx02 hepmc_ascii_Pythia8.in

1.2.3. Graphically
./HepMVEx02
        /control/execute vis.mac
        /control/execute hepmc_ascii_pythia6.in
        /control/execute hepmc_ascii_pythia8.in


1.3. How to produce ASCII file with Pythia 6 
==============
1.3.1. Basic example
cd ../data_Pythia6ToAscii/
mkdir build
cd build
export PYTHIA6='/afs/cern.ch/user/a/azaborow/OWN-pythia6/pythia6'
cmake  -DCMAKE_INSTALL_PREFIX=. ..

Edit data_Pythia6ToAscii/example_MyPythia.cxx to change any generation detail and run make

1.3.2. To produce an output
cd ..
build/example_MyPythia 


1.4. How to produce ASCII file with Pythia 8
==============
1.4.1. Basic example

cd ../../data_Pythia8ToAscii/
mkdir build
cd build
cmake -DHEPMC_ROOT_DIR='/afs/cern.ch/sw/lcg/external/HepMC/2.06.08/x86_64-slc6-gcc47-opt/' -DPYTHIA8='/afs/cern.ch/sw/lcg/external/MCGenerators_lcgcmt67b/pythia8/186/x86_64-slc6-gcc47-opt/' -DCMAKE_INSTALL_PREFIX=. ..

Edit main42.cmnd to change any generation detail


1.4.2. To produce an output

export PYTHIA8DATA=/afs/cern.ch/sw/lcg/external/MCGenerators_lcgcmt67b/pythia8/186/x86_64-slc6-gcc47-opt/xmldoc
build/main42 main42.cmnd example_MyPythia8.dat

____________________________________________________________________

