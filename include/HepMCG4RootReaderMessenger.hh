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

#ifndef HEPMC_G4_ROOT_READER_MESSENGER_H
#define HEPMC_G4_ROOT_READER_MESSENGER_H

#include "G4UImessenger.hh"

class HepMCG4RootReader;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;

/**
   @brief     Communicator between UI and FCCRootReader.
 	@details   A messenger class handling the commands from the UI to FCCPythiaInterface. Based on G4 examples/extended/eventgenerator/HepMC/HepMCEx01/include/HepMCG4AsciiReaderMessenger.hh.
 	@author    Anna Zaborowska
*/

class HepMCG4RootReaderMessenger : public G4UImessenger {
public:
   /**
      A constructor. The directory and the commands names are set here.
      @param aGenerator A pointer to the FCCRootReader class object.
   */
   HepMCG4RootReaderMessenger(HepMCG4RootReader* aGenerator);
   ~HepMCG4RootReaderMessenger();
   /**
      A method calling the methods from the FCCRootReader class, depending on the command.
      @param aCommand A pointer to the command typed by the user in the UI.
      @param aNewValues A new value of the command set by the user.
   */
   void SetNewValue(G4UIcommand* aCommand, G4String aNewValues);
   /**
      A method calling the methods from the FCCRootReader class, depending on the command.
      @param aCommand A pointer to the command typed by the user in the UI.
   */
   G4String GetCurrentValue(G4UIcommand* aCommand);

private:
   /**
      A pointer to the FCCRootReader class that is connected to the UI.
   */
   HepMCG4RootReader* fGenerator;
   /**
      A directory for the commands associated with this messenger.
   */
   G4UIdirectory* fDirectory;
   /**
      A command that takes an integer parameter. Used to set the verbose level.
   */
   G4UIcmdWithAnInteger* fVerboseCommand;
   /**
      A command that takes an string parameter. Sets the name of the ROOT file with the event.
   */
   G4UIcmdWithAString* fOpenCommand;

};

#endif
