Geant4-Pythia8
==============

Geant 4 example of event generator moved from Pythia 6 to 8

____________________________________________________________________

mkdir build
cd build
source /afs/cern.ch/sw/lcg/contrib/gcc/4.7.2/x86_64-slc6/setup.sh
source /afs/cern.ch/sw/lcg/external/geant4/10.0.p02/x86_64-slc6-gcc47-opt/CMake-setup.sh
cmake -DHEPMC_ROOT_DIR='/afs/cern.ch/sw/lcg/external/HepMC/2.06.08/x86_64-slc6-gcc47-opt/' -DCMAKE_INSTALL_PREFIX=. ..


____________________________________________________________________
./HepMCEx02 hepmc_ascii_Pythia6.in
./HepMCEx02 hepmc_ascii_Pythia8.in
./HepMVEx02
        /control/execute vis.mac
        /control/execute hepmc_ascii_pythia6.in

____________________________________________________________________

cd ../data_Pythia6ToAscii/
mkdir build
cd build
export PYTHIA6='/afs/cern.ch/user/a/azaborow/OWN-pythia6/pythia6'
cmake  -DCMAKE_INSTALL_PREFIX=. ..

____________________________________________________________________

cd ../../data_Pythia8ToAscii/
mkdir build
cd build
cmake -DHEPMC_ROOT_DIR='/afs/cern.ch/sw/lcg/external/HepMC/2.06.08/x86_64-slc6-gcc47-opt/' -DPYTHIA8='/afs/cern.ch/sw/lcg/external/MCGenerators_lcgcmt67b/pythia8/186/x86_64-slc6-gcc47-opt/' -DCMAKE_INSTALL_PREFIX=. ..

____________________________________________________________________

