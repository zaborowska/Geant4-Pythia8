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
// based on G4 examples/extended/eventgenerator/HepMC/HepMCEx01/src/HepMCG4AsciiReader.cc
//

#include "HepMCG4RootReader.hh"
#include "HepMCG4RootReaderMessenger.hh"

#include <iostream>
#include <fstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
HepMCG4RootReader::HepMCG4RootReader()
   : fVerbose(0)
{
   gSystem->Load("libHepMCdict");
   fMessenger= new HepMCG4RootReaderMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
HepMCG4RootReader::~HepMCG4RootReader()
{
   delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void HepMCG4RootReader::Initialize()
{
   G4cout << fFileName << G4endl;
   fRootInput= new TFile(fFileName.c_str());
   if(fVerbose>0) fRootInput->ls();
   fLinkToEvent = (fRootInput->GetListOfKeys())->FirstLink();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
HepMC::GenEvent* HepMCG4RootReader::GenerateHepMCEvent()
{
   HepMC::GenEvent* evt;
   G4String keyName;
   TKey* key;
   key = (TKey*)fLinkToEvent->GetObject();
   evt = (HepMC::GenEvent*) fRootInput->Get(key->GetName());
   if(fVerbose>0) G4cout << "Getting HepMC EVENT named: " << key->GetName() << G4endl;
   fLinkToEvent=fLinkToEvent->Next();
   if(fVerbose>0) evt->print();
   return evt;
}
