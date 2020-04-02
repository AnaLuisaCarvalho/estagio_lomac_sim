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
#include "G4SubtractionSolid.hh"
#include "G4ThreeVector.hh"

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

  // Geometric parameters for tile+wrapper
  G4double small_side = 288*mm, big_side = 302*mm, height = 147*mm, thickness = 5*mm;
  G4double e = 200*um; // thickness of the wrapper
  // Geometric parameters for fiber
  G4double diam_out = 1*mm; // fiber full diameter including both claddings
  G4double diam_in = (1-(2*0.02))*mm;
  G4double diam_core = (1-(4*0.02))*mm;
  
  // ----------------- //
  // ---- Wrapper ---- //
  // ----------------- //
  // Material
  G4Material *wrap_mat = nist->FindOrBuildMaterial("G4_MYLAR"); // Need to define TYVEK and put here
  // Create wrapper volume
  G4Trd *wrap_shape = new G4Trd("wrap_out",(thickness/2)+(e/2),(thickness/2)+(e/2),(small_side/2)+(e/2),(big_side/2)+(e/2),(height/2)+(e/2));
  // Create logical volume
  G4LogicalVolume *wrap_vol = new G4LogicalVolume(wrap_shape,wrap_mat,"wrap");

  // ---------------- //
  // ----- Tile ----- //
  // ---------------- //

  // Chemical elements
  // Carbon
  G4double aC = 12.011*g/mole; 
  G4Element *elC = new G4Element("Carbon","C",6.,aC);
  // Hydrogen
  G4double aH = 1.01*g/mole;
  G4Element *elH = new G4Element("Hydrogen","H",1.,aH);
  // Nitrogen
  G4double aN = 14.007*g/mole;
  G4Element *elN = new G4Element("Nitrogen","N",7.,aN);
  // Oxygen
  G4double aO = 15.999*g/mole;
  G4Element *elO = new G4Element("Oxygen","O",8.,aO);

  // Material
  // PTP (para terphenyl)
  G4double dPTP = 1.24*g/cm3;
  G4Material *PTP = new G4Material("PTP",dPTP,2);
  PTP->AddElement(elC,18);
  PTP->AddElement(elH,14);
  // POPOP
  G4double dPOPOP = 1.204*g/cm3;
  G4Material *POPOP = new G4Material("POPOP",dPOPOP,4);
  POPOP->AddElement(elC,24);
  POPOP->AddElement(elH,16);
  POPOP->AddElement(elN,2);
  POPOP->AddElement(elO,2);
  // Polystyrene
  G4Material *polystyrene = nist->FindOrBuildMaterial("G4_POLYSTYRENE");
  // Compound (polystyrene+PTP(1.5%)+POPOP(0.05%))
  G4double dTile = 1.0*g/cm3; // Approximate only, should get more precise value
  G4Material *tile_mat = new G4Material("tile_mat",dTile,3);
  tile_mat->AddMaterial(polystyrene,98.45*perCent);
  tile_mat->AddMaterial(PTP,1.5*perCent);
  tile_mat->AddMaterial(POPOP,0.05*perCent);

  // Create tile volume
  G4Trd *tile_shape = new G4Trd("tile",thickness/2,thickness/2,small_side/2,big_side/2,height/2);
  // Create logical volume (geometric volume + material)
  G4LogicalVolume *tile_vol = new G4LogicalVolume(tile_shape,tile_mat,"tile");
  // Create physical volume and place tile inside wrapper
  G4VPhysicalVolume* tile_phys = new G4PVPlacement(0,G4ThreeVector(),tile_vol,"tile",wrap_vol,false,0,checkOverlaps);

  //----------------//
  //---- Fiber -----//
  //----------------//
  // Probably need to give as input the spectrum

  return wrap_vol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
