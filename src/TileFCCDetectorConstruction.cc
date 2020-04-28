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

#include "TileFCCDetectorConstruction.hh"

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
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4Tubs.hh"

#include <math.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCDetectorConstruction::TileFCCDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCDetectorConstruction::~TileFCCDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* TileFCCDetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // 
  // Elements and materials
  // 
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
  // Fluor
  G4double aF = 18.998*g/mole;
  G4Element *elF = new G4Element("Fluor","F",9.,aF);

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

  // Polystyrene (PS)                                                    
  G4Material *polystyrene = nist->FindOrBuildMaterial("G4_POLYSTYRENE");

  // Polytetrafluoroethylene  
  G4double dFP = 1.43*g/cm3;    
  G4Material *FP = new G4Material("FP",dFP,2);
  FP->AddElement(elC,2);
  FP->AddElement(elF,4);
  // PMMA
  G4double dPMMA = 1190*kg/m3;    
  G4Material *PMMA = new G4Material("PMMA",dPMMA,3);  
  PMMA->AddElement(elC,5); 
  PMMA->AddElement(elH,8);
  PMMA->AddElement(elO,2);
  // Optical properties
  G4MaterialPropertiesTable *PMMA_MPT = new G4MaterialPropertiesTable();


  // Polyvinyk toluene (for scintillator BC-408)
  G4Material *polyvinyltoluene = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  // Add optical properties
  G4MaterialPropertiesTable *polyvinyltoluene_MPT = new G4MaterialPropertiesTable();

  // Photon energy in eV
  std::vector<double> energy_eV{3.3597967097*eV,3.2197580637*eV,3.1360502262*eV,3.0885728018*eV,3.0621624649*eV,3.0401327101*eV,3.0197151614*eV,3.0021025178*eV,2.9796742906*eV,2.9514436152*eV,2.8869388999*eV,2.8335914099*eV,2.8231955849*eV,2.8040187464*eV,2.7655443964*eV,2.711447172*eV,2.664384718*eV,2.6151200832*eV,2.5501551206*eV,2.455643586*eV};
  
  // Scintillator emission spectrum
  std::vector<double> scint_fast{3.5510692032,8.6216639054,16.0499640588,26.1932676525,35.0075149819,45.0524126744,55.624896693,66.0201732098,76.0656474993,86.6421676975,99.5252684059,84.76323002,73.5009436972,63.6517046132,52.5804641222,41.8705578,29.5732797226,19.9191226499,12.212518307,5.232041884};

  // Refractive index
  std::vector<double> rindex(energy_eV.size(),1.58);
  // Bulk absorption length
  std::vector<double> abslength(energy_eV.size(),380.*cm);

  polyvinyltoluene_MPT->AddProperty("FASTCOMPONENT",&(energy_eV[0]),&(scint_fast[0]),energy_eV.size());
  polyvinyltoluene_MPT->AddConstProperty("SCINTILLATIONYIELD",10000./MeV);
  polyvinyltoluene_MPT->AddConstProperty("RESOLUTIONSCALE",1.0);
  polyvinyltoluene_MPT->AddConstProperty("FASTTIMECONSTANT",1.0*ns);
  polyvinyltoluene_MPT->AddProperty("RINDEX",&(energy_eV[0]),&(rindex[0]),energy_eV.size());
  polyvinyltoluene_MPT->AddProperty("ABSLENGTH",&(energy_eV[0]),&(abslength[0]),energy_eV.size());
  polyvinyltoluene->SetMaterialPropertiesTable(polyvinyltoluene_MPT);

  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double env_sizeXY = 50*cm, env_sizeZ = 50*cm;
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  // Geometric parameters for tile+wrapper      
  G4double small_side = 288*mm, big_side = 302*mm, height = 147*mm, thickness = 5*mm;
  G4double e = 200*um; // thickness of the wrapper                                              

  // 
  // Tile
  // 
  // Material: compound (polystyrene+PTP(1.5%)+POPOP(0.05%)) 
  //G4double dTile = 1.0*g/cm3; // Approximate only, should get more precise values
  G4Material *tile_mat = polyvinyltoluene;
  // G4Material *tile_mat = new G4Material("tile_mat",dTile,3);
  // tile_mat->AddMaterial(polystyrene,98.45*perCent);
  // tile_mat->AddMaterial(PTP,1.5*perCent);
  // tile_mat->AddMaterial(POPOP,0.05*perCent);

  // Create tile volume            
  G4Trd *tile_shape = new G4Trd("tile",thickness/2,thickness/2,small_side/2,big_side/2,height/2);
  // Create logical volume (geometric volume + material)   
  G4LogicalVolume *tile_vol = new G4LogicalVolume(tile_shape,tile_mat,"tile");

  G4OpticalSurface* tile_wrap = new G4OpticalSurface("tile_wrap");
  // Add properties                                                                                                   
  tile_wrap->SetType(dielectric_LUT);
  tile_wrap->SetModel(LUT);
  tile_wrap->SetFinish(polishedtyvekair);
  G4LogicalSkinSurface* tile_surf = new G4LogicalSkinSurface("tile_wrap",tile_vol,tile_wrap); 
  G4MaterialPropertiesTable *tile_wrap_MPT = new G4MaterialPropertiesTable();

  std::vector<double> reflectivity(energy_eV.size(),1.0); // Maybe should be replaced with more realistic number
  std::vector<double> efficiency(energy_eV.size(),0.0);
  
  tile_wrap_MPT->AddProperty("REFLECTIVITY",&(energy_eV[0]),&(reflectivity[0]),energy_eV.size());
  tile_wrap_MPT->AddProperty("EFFICIENCY",&(energy_eV[0]),&(efficiency[0]),energy_eV.size());
  tile_wrap->SetMaterialPropertiesTable(tile_wrap_MPT);

  // Create physical volume
  G4VPhysicalVolume* tile_phys = new G4PVPlacement(0,G4ThreeVector(),tile_vol,"tile",logicWorld,false,0,checkOverlaps);

  //
  // Fiber
  //
  // Geometric parameters for fiber          
  G4double diam_out = 1*mm; // fiber full diameter including both claddings                      
  G4double diam_in = (1-(2*0.02))*mm;
  G4double diam_core = (1-(4*0.02))*mm;  
  G4double fiber_length = 200*mm; //20 cm ? Does this make sense?

  // Outer cladding: fluorinated polymer (FP)
  // Using Polytetrafluoroethylene because it is the simplest and most widely used in optical fibers (ref?)
  G4Tubs *out_clad_shape = new G4Tubs("out_clad_shape",0.,diam_out/2,fiber_length/2,0.,2*M_PI);
  G4LogicalVolume *out_clad_vol = new G4LogicalVolume(out_clad_shape,FP,"out_clad_vol");

  // Inner cladding: polymethylmethacrylate (PMMA)                                                                       
  G4Tubs *in_clad_shape = new G4Tubs("in_clad_shape",0.,diam_in/2,fiber_length/2,0.,2*M_PI);
  G4LogicalVolume *in_clad_vol = new G4LogicalVolume(in_clad_shape,PMMA,"in_clad_vol");
  G4OpticalSurface *in_clad_opsurf = new G4OpticalSurface("in_clad_opsurf");
  in_clad_opsurf->SetType(dielectric_dielectric);
  in_clad_opsurf->SetModel(glisur); 
  in_clad_opsurf->SetFinish(polished); 
  G4LogicalSkinSurface *in_clad_surf = new G4LogicalSkinSurface("in_clad_surf",in_clad_vol,in_clad_opsurf);

  // Core: polystylene (PS)
  G4Tubs *core_shape = new G4Tubs("core_shape",0.,diam_core/2,fiber_length/2,0.,2*M_PI);
  G4LogicalVolume *core_vol = new G4LogicalVolume(core_shape,polystyrene,"core_vol");
  G4OpticalSurface *core_opsurf = new G4OpticalSurface("core_opsurf");
  core_opsurf->SetType(dielectric_dielectric);
  core_opsurf->SetModel(glisur); 
  core_opsurf->SetFinish(polished); // assumes perfectly smooth surface (does this make sense?)
  G4LogicalSkinSurface *core_surf = new G4LogicalSkinSurface("core_surf",core_vol,core_opsurf);

  // Create fiber physical volume (outer cladding, other will be placed inside)
  G4VPhysicalVolume *fiber_phys = new G4PVPlacement(0,G4ThreeVector(),out_clad_vol,"fiber",logicWorld,false,0,checkOverlaps);
  // Place inner cladding inside
  G4VPhysicalVolume *in_clad_phys = new G4PVPlacement(0,G4ThreeVector(),in_clad_vol,"in_clad",out_clad_vol,false,0,checkOverlaps);
  // Place core
  G4VPhysicalVolume *core_phys = new G4PVPlacement(0,G4ThreeVector(),core_vol,"core",in_clad_vol,false,0,checkOverlaps);

  fScoringVolume = tile_vol;
  
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

