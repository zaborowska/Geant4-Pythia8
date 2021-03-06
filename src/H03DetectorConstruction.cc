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
/// \file eventgenerator/HepMC/HepMCEx03/src/H03DetectorConstruction.cc
/// \brief Implementation of the H03DetectorConstruction class
//
#include "G4Box.hh"
#include "G4ChordFinder.hh"
#include "G4Element.hh"
#include "G4FieldManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4TransportationManager.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "H03Field.hh"
#include "H03DetectorConstruction.hh"
#include "H03MuonSD.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// constants (detector parameters)
// [experimental hall]
static const G4double R_EXPHALL= 5.*m;
static const G4double DZ_EXPHALL= 10.*m;

// [calorimeter]
static const G4double RIN_BARREL_CAL= 2.*m;
static const G4double ROUT_BARREL_CAL= 3.*m;
static const G4double DZ_BARREL_CAL= 5.*m;

static const G4double RIN_ENDCAP_CAL= 1.*m;
static const G4double ROUT_ENDCAP_CAL= 3.*m;
static const G4double DZ_ENDCAP_CAL= 0.5*m;

// [muon system]
static const G4double RIN_BARREL_MUON= 4.3*m;
static const G4double ROUT_BARREL_MUON= 4.5*m;
static const G4double DX_BARREL_MUON= RIN_BARREL_MUON*std::cos(67.5*deg)-5.*cm;
static const G4double DY_BARREL_MUON= 10.*cm;
static const G4double DZ_BARREL_MUON= 7.*m;

static const G4double RIN_ENDCAP_MUON=  1.*m;
static const G4double ROUT_ENDCAP_MUON= 4.5*m;
static const G4double DZ_ENDCAP_MUON= 10.*cm;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
H03DetectorConstruction::H03DetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
H03DetectorConstruction::~H03DetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume* H03DetectorConstruction::Construct()
{
  // ==============================================================
  // Materials
  // ==============================================================

  G4double a, iz, z, density;
  G4String name, symbol;
  G4int nel;

  a= 1.01*g/mole;
  G4Element* elH= new G4Element(name="Hydrogen", symbol="H", iz=1., a);

  a= 12.01*g/mole;
  G4Element* elC= new G4Element(name="Carbon", symbol="C", iz=6., a);

  a= 14.01*g/mole;
  G4Element* elN= new G4Element(name="Nitrogen", symbol="N", iz=7., a);

  a = 16.00*g/mole;
  G4Element* elO= new G4Element(name="Oxygen", symbol="O", iz=8., a);

  density= 1.29e-03*g/cm3;
  G4Material* Air= new G4Material(name="Air", density, nel=2);
  Air-> AddElement(elN, .7);
  Air-> AddElement(elO, .3);

  a= 207.19*g/mole;
  density= 11.35*g/cm3;
  G4Material* Lead= new G4Material(name="Lead", z=82., a, density);

  a= 39.95*g/mole;
  density= 1.782e-03*g/cm3;
  G4Material* Ar= new G4Material(name="ArgonGas", z=18., a, density);

  density= 1.032*g/cm3;
  G4Material* Scinti= new G4Material(name="Scintillator", density, nel=2);
  Scinti-> AddElement(elC, 9);
  Scinti-> AddElement(elH, 10);


  // ==============================================================
  // Experimental Hall (world)
  // ==============================================================
  G4Tubs* expHallSolid=
    new G4Tubs("EXP_HALL", 0., R_EXPHALL, DZ_EXPHALL, 0., 360.*deg);

  G4LogicalVolume* expHallLV=
    new G4LogicalVolume(expHallSolid, Air, "EXP_HALL_LV");

  // visualization attributes
  G4VisAttributes* expHallVisAtt=
    new G4VisAttributes(false, G4Colour(1., 1., 1.));
  //expHallVisAtt-> SetForceWireframe(TRUE);
  expHallLV-> SetVisAttributes(expHallVisAtt);

  G4PVPlacement* expHall= new G4PVPlacement(0, G4ThreeVector(), "EXP_HALL_PV",
                                            expHallLV, 0, FALSE, 0);
  //            ...                                    MV, MANY, copy#

  // ==============================================================
  // each detector component
  // ==============================================================
  // calorimeter system
  G4Tubs* barrelCalSolid=
    new G4Tubs("BARREL_CAL", RIN_BARREL_CAL, ROUT_BARREL_CAL,
               DZ_BARREL_CAL, 0., 360.*deg);

  G4Tubs* endcapCalSolid=
    new G4Tubs("ENDCAP_CAL", RIN_ENDCAP_CAL, ROUT_ENDCAP_CAL,
               DZ_ENDCAP_CAL, 0., 360.*deg);

  G4LogicalVolume* barrelCalLV=
    new G4LogicalVolume(barrelCalSolid, Lead, "BARREL_CAL_LV");

  G4LogicalVolume* endcapCalLV=
    new G4LogicalVolume(endcapCalSolid, Lead, "ENDCAP_CAL_LV");

  G4VisAttributes* calVisAtt=
    new G4VisAttributes(true, G4Colour(0., 1., 1.));
  barrelCalLV-> SetVisAttributes(calVisAtt);
  endcapCalLV-> SetVisAttributes(calVisAtt);

  // G4PVPlacement* barrelCal=
    new G4PVPlacement(0, G4ThreeVector(), "BARREL_CAL_PV",
                      barrelCalLV, expHall, FALSE, 0);

  G4ThreeVector posCal(0.,0.,6.*m);
  // G4PVPlacement* endcapCal1=
    new G4PVPlacement(0, posCal, "ENDCAP_CAL_PV",
                      endcapCalLV, expHall, FALSE, 0);

  //G4PVPlacement* endcapCal2=
    new G4PVPlacement(0, -posCal, "ENDCAP_CAL_PV",
                      endcapCalLV, expHall, FALSE, 1);

  // muon system
  G4Box* barrelMuonSolid= new G4Box("BARREL_MUON", DX_BARREL_MUON,
                                     DY_BARREL_MUON,  DZ_BARREL_MUON);
  G4Tubs* endcapMuonSolid=
    new G4Tubs("ENDCAP_MUON", RIN_ENDCAP_MUON, ROUT_ENDCAP_MUON,
               DZ_ENDCAP_MUON, 0., 360.*deg);

  G4LogicalVolume* barrelMuonLV=
    new G4LogicalVolume(barrelMuonSolid, Ar, "BARREL_MUON_LV");

  G4LogicalVolume* endcapMuonLV=
    new G4LogicalVolume(endcapMuonSolid, Ar, "ENDCAP_MUON_LV");

  G4VisAttributes* muonVisAtt=
    new G4VisAttributes(true, G4Colour(1., 1., 0.5));
  //muonVisAtt-> SetForceWireframe(TRUE);
  barrelMuonLV-> SetVisAttributes(muonVisAtt);
  endcapMuonLV-> SetVisAttributes(muonVisAtt);

  const G4double dangle= 45.*deg;
  G4ThreeVector posM(RIN_BARREL_MUON+DY_BARREL_MUON/2., 0., 0.);
  G4RotationMatrix* rotM= new G4RotationMatrix;
  rotM->rotateZ(90.*deg);

  for (G4int k=0; k<8; k++) {
    G4Transform3D transformM(*rotM, posM);
    new G4PVPlacement(transformM, "BARREL_MUON_PV",
                      barrelMuonLV, expHall, FALSE, k);
    rotM->rotateZ(dangle);
    posM.rotateZ(dangle);
  }

  G4ThreeVector posMuon(0.,0.,8.*m);
  // G4PVPlacement* endcapMuon1=
    new G4PVPlacement(0, posMuon, "ENDCAP_MUON_PV",
                      endcapMuonLV, expHall, FALSE, 0);

  // G4PVPlacement* endcapMuon2=
    new G4PVPlacement(0, -posMuon, "ENDCAP_MUON_PV",
                      endcapMuonLV, expHall, FALSE, 1);


  // sensitive Detectors
  G4SDManager* SDman= G4SDManager::GetSDMpointer();

  G4String muonSDname= "/mydet/muon";
  H03MuonSD* muonSD= new H03MuonSD(muonSDname);
  SDman-> AddNewDetector(muonSD);
  barrelMuonLV-> SetSensitiveDetector(muonSD);
  endcapMuonLV-> SetSensitiveDetector(muonSD);

  // magnetic field
  H03Field* myfield = new H03Field;
  G4FieldManager* fieldMgr=
    G4TransportationManager::GetTransportationManager()-> GetFieldManager();
  fieldMgr-> SetDetectorField(myfield);
  fieldMgr-> CreateChordFinder(myfield);

  return expHall;
}
