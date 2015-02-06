PYTHIA 8 in Geant4 example
============

1. Installation
-------------------

        mkdir build
        cd build

        source /afs/cern.ch/sw/lcg/contrib/gcc/4.9/x86_64-slc6-gcc49-opt/setup.sh
        source /afs/cern.ch/sw/lcg/external/geant4/10.1/x86_64-slc6-gcc49-opt/CMake-setup.sh
        source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.25/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh
        export PYTHIA8DATA=/afs/cern.ch/sw/lcg/external/MCGenerators_lcgcmt67b/pythia8/186/x86_64-slc6-gcc47-opt/xmldoc
        export ROOTSYS=/afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.25/x86_64-slc6-gcc48-opt/root/

        cmake -DHEPMC_ROOT_DIR='/afs/cern.ch/sw/lcg/external/HepMC/2.06.08/x86_64-slc6-gcc47-opt/' \
          -DPYTHIA8='/afs/cern.ch/sw/lcg/external/MCGenerators_lcgcmt67b/pythia8/186/x86_64-slc6-gcc47-opt/'  \
          -DCMAKE_CXX_COMPILER='/afs/cern.ch/sw/lcg/contrib/gcc/4.9/x86_64-slc6-gcc49-opt/bin/g++' \
          -DCMAKE_INSTALL_PREFIX=. ..

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
        /run/beamOn 1

2.2. Pythia8 event saved in HepMC format to ASCII file, read by Geant4:

       hepmc_ascii.in:

         /generator/select hepmcAscii
         /generator/hepmcAscii/open ../tools/pythia8ToAscii/example_MyPythia8.dat
         /run/beamOn 1

2.3. Pythia8 event saved in HepMC format to ROOT file, read by Geant4:

       hepmc_root.in:

         /generator/select hepmcRoot
         /generator/hepmcRoot/open ../data/pythia8ToRoot/PythiaInHepMC_140GeV.root
         /run/beamOn 1


4. Running an example
-------------------

4.1 Without GUI

        ./HepMCEx03 hepmc_pythia8.in

4.2 With GUI

        ./HepMCEx03
