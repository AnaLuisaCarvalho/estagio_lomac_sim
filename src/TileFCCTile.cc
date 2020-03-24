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
//
/// \file TileFCCDetectorConstruction.cc
/// \brief Implementation of the TileFCCDetectorConstruction class

#include "TileFCCTile.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCTile::TileFCCTile()
: fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCTile::~TileFCCTile()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* TileFCCTile::Construct()
{  
  G4bool checkOverlaps = true;
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // ---------------- //
  // ----- Tile ----- //
  // ---------------- //

  // Geometric parameters
  G4double small_side = 288*mm, big_side = 302*mm, height = 147*mm, thickness = 5*mm;
  // Material
  G4Material *tile_mat = nist->FindOrBuildMaterial("G4_POLYSTYRENE"); // Need to put here exact material
  // Create tile volume
  G4Trd *tile_shape = new G4Trd("tile",thickness/2,thickness/2,small_side/2,big_side/2,height/2);
  // Create logical volume (geometric volume + material)
  G4LogicalVolume *tile_vol = new G4LogicalVolume(tile_shape,tile_mat,"tile");
  // Create physical volume
  //G4VPhysicalVolume* tile_phys = new G4VPlacement(0,G4ThreeVector(),tile_vol,"tile",0,false,0,checkOverlaps);

  // ----------------- //
  // ---- Wrapper ---- //
  // ----------------- //
  // Geometry
  G4double e = 1*mm; // thickness of the wrapper
  // Material
  G4Material *wrap_mat = nist->FindOrBuildMaterial("G4_MYLAR"); // Need to define TYVEK and put here
  // Create wrapper volume

  // Create logical volume
  
  // Place it around tile

  return tile_vol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
