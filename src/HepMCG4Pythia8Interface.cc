//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file eventgenerator/HepMC/HepMCEx01/src/HepMCG4PythiaInterface.cc
/// \brief Implementation of the HepMCG4PythiaInterface class
//
// $Id: HepMCG4PythiaInterface.cc 77801 2013-11-28 13:33:20Z gcosmo $
//

#ifdef G4LIB_USE_PYTHIA8

#include "HepMCG4Pythia8Interface.hh"
#include "HepMCG4Pythia8Messenger.hh"

#include "HepMC/GenEvent.h"

/*//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// additional pythia calls
#define pygive pygive_
#define pyrget pyrget_
#define pyrset pyrset_

extern "C" {
  void pygive(const char*, int);
  void pyrget(int*, int*);
  void pyrset(int*, int*);
}

void call_pygive(G4String s) { pygive(s.c_str(), s.length()); }
void call_pyrget(int a, int b) { pyrget(&a, &b); }
void call_pyrset(int a, int b) { pyrset(&a, &b); }
*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
HepMCG4Pythia8Interface::HepMCG4Pythia8Interface()
   : verbose(0)//, mpylist(0)
{
  pythia.readString("HardQCD:all = on");
  pythia.readString("PhaseSpace:pTHatMin = 20.");
  messenger= new HepMCG4Pythia8Messenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
HepMCG4Pythia8Interface::~HepMCG4Pythia8Interface()
{
  delete messenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void HepMCG4Pythia8Interface::CallPythiaReadString(G4String par)
{
   pythia.readString(par);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void HepMCG4Pythia8Interface::CallPythiaInit(G4int beam,
                                        G4int target, G4double eCM)
{
   pythia.init(beam,target, eCM);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void HepMCG4Pythia8Interface::CallPythiaStat(G4int istat)
{
   pythia.stat();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void HepMCG4Pythia8Interface::SetRandomSeed(G4int iseed)
{
   pythia.readString("Random:setSeed = on");
   pythia.readString("Random:seed = "+iseed);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// void HepMCG4Pythia8Interface::CallPyrget(G4int lun, G4int move)
// {
//    //call_pyrget(lun, move);
// }

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// void HepMCG4Pythia8Interface::CallPyrset(G4int lun, G4int move)
// {
//    //call_pyrset(lun, move);
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void HepMCG4Pythia8Interface::PrintRandomStatus(std::ostream& ostr) const
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void HepMCG4Pythia8Interface::SetUserParameters()
{
  G4cout << "set user parameters of PYTHIA common." << G4endl
         << "nothing to be done in default."
         << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
HepMC::GenEvent* HepMCG4Pythia8Interface::GenerateHepMCEvent()
{
   //static G4int nevent= 0; // event counter - not needed in Pythia 8

   //call_pyevnt(); // generate one event with Pythia
   pythia.next();
   //if(mpylist >=1 && mpylist<= 3) call_pylist(mpylist); ---- ale po co to?

  // call_pyhepc(1);

  // HepMC::GenEvent* evt= hepevtio.read_next_event();
  // evt-> set_event_number(nevent++);

  HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
  ToHepMC.fill_next_event( pythia, hepmcevt );
  if(verbose>0) hepmcevt-> print();

  return hepmcevt;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void HepMCG4Pythia8Interface::Print() const
{
  G4cout << "Pythia8Interface::Print()..." << G4endl;
}

#endif
