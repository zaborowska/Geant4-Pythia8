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
/// \file eventgenerator/HepMC/HepMCEx01/include/HepMCG4PythiaInterface.hh
/// \brief Definition of the HepMCG4PythiaInterface class
//
// $Id: HepMCG4PythiaInterface.hh 77801 2013-11-28 13:33:20Z gcosmo $
//

#ifndef HEPMC_G4_PYTHIA8_INTERFACE_H
#define HEPMC_G4_PYTHIA8_INTERFACE_H

#include "HepMCG4Interface.hh"
#include "Pythia8/Pythia8ToHepMC.h"
#include "Pythia8/Pythia.h"

class HepMCG4Pythia8Messenger;

/// A generic interface class with Pythia8 event generator via HepMC.

class HepMCG4Pythia8Interface : public HepMCG4Interface {
protected:
   G4int verbose;
   //G4int mpylist;
   //HepMC::IO_HEPEVT hepevtio;
   HepMC::Pythia8ToHepMC ToHepMC;
   Pythia8::Pythia pythia;

  HepMCG4Pythia8Messenger* messenger;

  // In default, this is automatic conversion, Pythia->HEPEVT->HepMC,
  // by HepMC utilities.
  virtual HepMC::GenEvent* GenerateHepMCEvent();

public:
  HepMCG4Pythia8Interface();
  ~HepMCG4Pythia8Interface();

  // set/get methods
  void SetVerboseLevel(G4int i);
  G4int GetVerboseLevel() const;

  // void SetPylist(G4int i);
  // G4int GetPylist() const;

  // call pyxxx
  void CallPythiaInit(G4int beam, G4int target, G4double eCM);
  void CallPythiaStat(G4int istat);

  // random numbers operations
  void SetRandomSeed(G4int iseed);
  void CallPythiaReadString(G4String par);
  // void CallPyrget(G4int lun, G4int move);
  // void CallPyrset(G4int lun, G4int move);
  void PrintRandomStatus(std::ostream& ostr=G4cout) const;

  // setup user parameters (empty in default).
  // Implement your parameters in a delived class if you want.
  virtual void SetUserParameters();

  virtual void Print() const;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void HepMCG4Pythia8Interface::SetVerboseLevel(G4int i)
{
  verbose= i;
}

inline G4int HepMCG4Pythia8Interface::GetVerboseLevel() const
{
  return verbose;
}

// inline void HepMCG4Pythia8Interface::SetPylist(G4int i)
// {
//   mpylist= i;
// }

// inline G4int HepMCG4Pythia8Interface::GetPylist() const
// {
//   return mpylist;
// }

#endif
