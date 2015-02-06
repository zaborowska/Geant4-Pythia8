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
/// \file eventgenerator/HepMC/HepMCEx03/include/H03MuonHit.hh
/// \brief Definition of the H03MuonHit class
//
#ifndef H03_MUON_HIT_H
#define H03_MUON_HIT_H

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class H03MuonHit : public G4VHit {
public:
  H03MuonHit();
  H03MuonHit(G4int imod, G4String aname, const G4ThreeVector& pxyz,
            const G4ThreeVector& xyz, G4double atof);
  ~H03MuonHit();

  H03MuonHit(const H03MuonHit& right);
  const H03MuonHit& operator=(const H03MuonHit& right);
  G4int operator==(const H03MuonHit& right) const;

  void* operator new(size_t);
  void operator delete(void* aHit);

  // set/get functions...
  void SetModuleID(G4int i);
  G4int GetModuleID() const;

  void SetParticle(G4String aname);
  G4String GetParticle() const;

  void SetMomentum(const G4ThreeVector& pxyz);
  G4ThreeVector GetMomentum() const;

  void SetPosition(const G4ThreeVector& xyz);
  G4ThreeVector GetPosition() const;

  void SetTOF(G4double atof);
  G4double GetTOF() const;

  // methods...
  virtual void Draw();
  virtual void Print();

private:
  G4int moduleID;
  G4String pname;
  G4ThreeVector momentum;
  G4ThreeVector position;
  G4double tof;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void H03MuonHit::SetModuleID(G4int i) { moduleID=i; }
inline G4int H03MuonHit::GetModuleID() const { return moduleID; }

inline void H03MuonHit::SetParticle(G4String aname) { pname=aname; }
inline G4String H03MuonHit::GetParticle() const { return pname; }

inline void H03MuonHit::SetMomentum(const G4ThreeVector& pxyz)
{ momentum=pxyz; }
inline G4ThreeVector H03MuonHit::GetMomentum() const { return momentum; }

inline void H03MuonHit::SetPosition(const G4ThreeVector& xyz) { position=xyz; }
inline G4ThreeVector H03MuonHit::GetPosition() const { return position; }

inline void H03MuonHit::SetTOF(G4double atof) { tof=atof; }
inline G4double H03MuonHit::GetTOF() const { return tof; }

typedef G4THitsCollection<H03MuonHit> H03MuonHitsCollection;
extern G4Allocator<H03MuonHit> H03MuonHitAllocator;

inline void* H03MuonHit::operator new(size_t)
{
  void* aHit;
  aHit= (void*)H03MuonHitAllocator.MallocSingle();
  return aHit;
}

inline void H03MuonHit::operator delete(void* aHit)
{
  H03MuonHitAllocator.FreeSingle((H03MuonHit*) aHit);
}

#endif
