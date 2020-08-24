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
#include "TileFCCTileSD.hh"
#include "TileFCCFiberSD.hh"
#include "TileFCCPmtSD.hh"

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
#include "G4Para.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"

#include <math.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <algorithm>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCDetectorConstruction::TileFCCDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0),
  fFiberVolume(0)
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

  G4double wls_Energy[] = {2.00*eV,2.87*eV,2.90*eV,3.47*eV};
  const G4int wlsnum = sizeof(wls_Energy)/sizeof(G4double);

  // Material
  // Air
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4MaterialPropertiesTable *air_MPT = new G4MaterialPropertiesTable();
  
  G4double rindex_air[] = {1.0,1.0,1.0,1.0};
  G4double abslength_air[] = {1000.*cm,1000.*cm,1000.*cm,1000.*cm};

  air_MPT->AddProperty("RINDEX",wls_Energy,rindex_air,wlsnum);
  air_MPT->AddProperty("ABSLENGTH",wls_Energy,abslength_air,wlsnum);

  world_mat->SetMaterialPropertiesTable(air_MPT);

  // Aluminum
  G4Material *Al = nist->FindOrBuildMaterial("G4_Al");
  //G4MaterialPropertiesTable *Al_MPT = new G4MaterialPropertiesTable();
  G4double rindex_real_Al[] = {1.19,0.58,0.53,0.36};
  G4double rindex_im_Al[] = {7.07,5.18,4.97,4.19};

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

  // Polystyrene (PS) - fiber core                                                    
  G4Material *polystyrene = nist->FindOrBuildMaterial("G4_POLYSTYRENE");

  G4MaterialPropertiesTable *polystyrene_MPT = new G4MaterialPropertiesTable();
  G4double RefractiveIndexFiber[]={ 1.60, 1.60, 1.60, 1.60};
  assert(sizeof(RefractiveIndexFiber) == sizeof(wls_Energy));
  G4double AbsFiber[]={9.00*m,9.00*m,0.1*mm,0.1*mm};
  //G4double AbsFiber[]={0.1*mm,0.1*mm,0.1*mm,0.1*mm};
  assert(sizeof(AbsFiber) == sizeof(wls_Energy));
  G4double AbsFiberClad[]={20.0*m,20.0*m,20.0*m,20.0*m};
  assert(sizeof(AbsFiberClad) == sizeof(wls_Energy));
  G4double EmissionFib[]={1.0, 1.0, 0.0, 0.0};
  assert(sizeof(EmissionFib) == sizeof(wls_Energy));

  polystyrene_MPT->AddProperty("RINDEX",wls_Energy,RefractiveIndexFiber,wlsnum);
  polystyrene_MPT->AddProperty("WLSABSLENGTH",wls_Energy,AbsFiber,wlsnum);
  polystyrene_MPT->AddProperty("WLSCOMPONENT",wls_Energy,EmissionFib,wlsnum);
  polystyrene_MPT->AddConstProperty("WLSTIMECONSTANT",0.5*ns);

  polystyrene->SetMaterialPropertiesTable(polystyrene_MPT);

  // Polyethylene
  G4Material *polyethylene = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

  // Polytetrafluoroethylene  
  G4double dFP = 1.43*g/cm3;    
  G4Material *FP = new G4Material("FP",dFP,2);
  FP->AddElement(elC,2);
  FP->AddElement(elF,4);
  
  G4double RefractiveIndexClad2[]={ 1.42, 1.42, 1.42, 1.42};
  assert(sizeof(RefractiveIndexClad2) == sizeof(wls_Energy));
  G4MaterialPropertiesTable *FP_MPT = new G4MaterialPropertiesTable();
  FP_MPT->AddProperty("RINDEX",wls_Energy,RefractiveIndexClad2,wlsnum);
  FP_MPT->AddProperty("ABSLENGTH",wls_Energy,AbsFiberClad,wlsnum);
  FP->SetMaterialPropertiesTable(FP_MPT);

  // PMMA
  G4double dPMMA = 1190*kg/m3;    
  G4Material *PMMA = new G4Material("PMMA",dPMMA,3);  
  PMMA->AddElement(elC,5); 
  PMMA->AddElement(elH,8);
  PMMA->AddElement(elO,2);
  
  // Optical properties
  G4double RefractiveIndexClad1[]={ 1.49, 1.49, 1.49, 1.49};
  assert(sizeof(RefractiveIndexClad2) == sizeof(wls_Energy));
  G4MaterialPropertiesTable *PMMA_MPT = new G4MaterialPropertiesTable();
  PMMA_MPT->AddProperty("RINDEX",wls_Energy,RefractiveIndexClad1,wlsnum);
  PMMA_MPT->AddProperty("ABSLENGTH",wls_Energy,AbsFiberClad,wlsnum);
  PMMA->SetMaterialPropertiesTable(PMMA_MPT);

  // Polyvinyk toluene (for scintillator BC-408)
  G4Material *polyvinyltoluene = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  // Add optical properties
  G4MaterialPropertiesTable *polyvinyltoluene_MPT = new G4MaterialPropertiesTable();
  
  G4double rIndexPstyrene[]={ 1.58, 1.58, 1.58, 1.58};
  assert(sizeof(rIndexPstyrene) == sizeof(wls_Energy));
  G4double absorption1[]={380.*cm, 380.*cm, 380.*cm, 380.*cm};
  assert(sizeof(absorption1) == sizeof(wls_Energy));
  G4double scintilFast[]={0.00, 0.00, 1.00, 1.00};
  assert(sizeof(scintilFast) == sizeof(wls_Energy));

  polyvinyltoluene_MPT->AddProperty("RINDEX",wls_Energy,rIndexPstyrene,wlsnum);
  polyvinyltoluene_MPT->AddProperty("ABSLENGTH",wls_Energy,absorption1,wlsnum);
  polyvinyltoluene_MPT->AddProperty("FASTCOMPONENT",wls_Energy, scintilFast,wlsnum);
  polyvinyltoluene_MPT->AddConstProperty("SCINTILLATIONYIELD",10000./MeV);
  polyvinyltoluene_MPT->AddConstProperty("RESOLUTIONSCALE",1.0);
  polyvinyltoluene_MPT->AddConstProperty("FASTTIMECONSTANT", 10.*ns);

  polyvinyltoluene->SetMaterialPropertiesTable(polyvinyltoluene_MPT);

  polyvinyltoluene->GetIonisation()->SetBirksConstant(0.126*mm/MeV);

  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double env_sizeXY = 50*cm, env_sizeZ = 50*cm;
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  
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
  G4double small_side = 288*mm, big_side = 302*mm, height = 147*mm, thickness = 3*mm;
  G4double height1 = 300*mm;
  G4double d_side = (big_side-small_side)/2;
  G4double alpha = atan(d_side/height);
  G4double e = 200*um; // thickness of the wrapper                                              
  G4double e_air = 1*mm; // thickness of air layer between tile and tyvek? Does not for e_air=0
  // Geometric parameters for fiber          
  G4double diam_out = 1*mm; // fiber full diameter including both claddings                      
  G4double diam_in = (1-(2*0.02))*mm;
  G4double diam_core = (1-(4*0.02))*mm;  

  G4double fiber_length = 200*mm;
  G4double fiber_length_1 = 500*mm;

  // Rotation/translation matrices
  G4RotationMatrix *fiber_rot = new G4RotationMatrix();
  fiber_rot->rotateX(alpha*rad); // rotation around x axis
  fiber_rot->rotateY(0.*rad);
  fiber_rot->rotateZ(0.*rad);
  G4ThreeVector fiber_tran = G4ThreeVector(-2.0*mm,(((small_side+d_side+(diam_out/cos(alpha)))/2)-5.0*cm),0.);

  G4RotationMatrix *fiber_rot1 = new G4RotationMatrix();
  fiber_rot1->rotateX(-alpha*rad); // rotation around x axis
  fiber_rot1->rotateY(0.*rad);
  fiber_rot1->rotateZ(0.*rad);
  G4ThreeVector fiber_tran1 = G4ThreeVector(-2.0*mm,-(((small_side+d_side+(diam_out/cos(alpha)))/2)-5.0*cm),0.);

  //
  // Wrapper
  //
  // Outer volume of wrapper
  G4VSolid *wrap_shape_out = new G4Trd("wrap_shape_out",(thickness+2*(e+e_air))/2,(thickness+2*(e+e_air))/2,(small_side+2*(e+e_air)+2*diam_out)/2,(big_side+2*(e+e_air)+2*diam_out)/2,(height+2*(e+e_air))/2);
  // Inner volume of wrapper
  G4VSolid *wrap_shape_in = new G4Trd("wrap_shape_in",(thickness+2*e_air)/2,(thickness+2*e_air)/2,(small_side+2*e_air+2*diam_out)/2,(big_side+2*e_air+2*diam_out)/2,(height+2*e_air)/2);  
  // Air that goes inside wrapper volume
  G4Trd *air_shape = new G4Trd("air_shape",(thickness+2*e_air)/2,(thickness+2*e_air)/2,(small_side+2*e_air+2*diam_out)/2,(big_side+2*e_air+2*diam_out)/2,(height+2*e_air)/2);
  G4LogicalVolume *air_vol = new G4LogicalVolume(air_shape,world_mat,"air_vol");
  //air_vol->SetVisAttributes(G4VisAttributes::GetInvisible());  

  // Outer volume of wrapper
  G4VSolid *wrap_shape_out_max = new G4Trd("wrap_shape_out",(thickness+2*(e+e_air))/2,(thickness+2*(e+e_air))/2,(small_side+2*(e+e_air)+2*diam_out)/2,(big_side+2*(e+e_air)+2*diam_out)/2,(height1+2*(e+e_air))/2);
  // Cylinder used to make hole in wrapper for fiber to come out
  G4Tubs *out_clad_shape_single_1 = new G4Tubs("out_clad_shape_single_1",0.,diam_out/2,fiber_length_1/2,0.,2*M_PI);
  // Intersection between wrapper outter volume and fiber (to create hole shape)
  G4VSolid *out_clad_shape_1 = new G4IntersectionSolid("out_clad_shape_single_1&&wrap_shape",wrap_shape_out_max,out_clad_shape_single_1,fiber_rot,G4ThreeVector());
  G4VSolid *out_clad_shape_2 = new G4IntersectionSolid("out_clad_shape_2",wrap_shape_out_max,out_clad_shape_single_1,fiber_rot1,G4ThreeVector());

  // Creating wrapper with empty hole in the middle and small cylinder hole for fiber
  G4VSolid *wrap_shape = new G4SubtractionSolid("wrap_shape",wrap_shape_out,out_clad_shape_1,0,fiber_tran);
  
  // Wrapper material 
  G4Material *wrap_mat = polyethylene;

  G4LogicalVolume *wrap_vol = new G4LogicalVolume(wrap_shape,wrap_mat,"wrap");
  G4VisAttributes *wrap_vol_vis = new G4VisAttributes(G4Colour(1,0,0));
  wrap_vol->SetVisAttributes(wrap_vol_vis);
  //wrap_vol->SetVisAttributes(G4VisAttributes::GetInvisible());
  
  // Wrapper physical volume
  G4VPhysicalVolume *wrap_phys = new G4PVPlacement(0,G4ThreeVector(),wrap_vol,"wrap",logicWorld,false,0,checkOverlaps);
  // Air physical volume, placed inside wrapper
  G4VPhysicalVolume *air_phys = new G4PVPlacement(0,G4ThreeVector(),air_vol,"air",wrap_vol,false,0,checkOverlaps);

  // Set optical properties of wrapper-air boundary
  G4OpticalSurface* wrap_air = new G4OpticalSurface("wrap_air");
  // Add properties                                                                                                   
  wrap_air->SetType(dielectric_LUT);
  wrap_air->SetModel(LUT);
  wrap_air->SetFinish(polishedtyvekair);
  
  G4LogicalBorderSurface* wrap_air_surf = new G4LogicalBorderSurface("wrap_air_surf",air_phys,wrap_phys,wrap_air); 
  G4MaterialPropertiesTable *wrap_air_MPT = new G4MaterialPropertiesTable();

  G4double reflectivity[] = {1.0, 1.0, 1.0, 1.0};  
  G4double efficiency[] = {1.0, 1.0, 1.0, 1.0};  

  wrap_air_MPT->AddProperty("REFLECTIVITY",wls_Energy,reflectivity,wlsnum);
  wrap_air_MPT->AddProperty("EFFICIENCY",wls_Energy,efficiency,wlsnum);
  wrap_air->SetMaterialPropertiesTable(wrap_air_MPT);

  // 
  // Tile
  // 
  // Material: compound (polystyrene+PTP(1.5%)+POPOP(0.05%)) 
  G4Material *tile_mat = polyvinyltoluene;
  // Create tile volume            
  G4Trd *tile_shape = new G4Trd("tile_shape",thickness/2,thickness/2,small_side/2,big_side/2,height/2);
  // Create logical volume (geometric volume + material)   
  G4LogicalVolume *tile_vol = new G4LogicalVolume(tile_shape,tile_mat,"tile");
  
  // Create sensitive detector
  TileFCCTileSD *tile_sens = new TileFCCTileSD("tile_sens","TileHitsCollection");
  tile_vol->SetSensitiveDetector(tile_sens);
  G4SDManager::GetSDMpointer()->AddNewDetector(tile_sens);

  G4VisAttributes* tile_vol_vis = new G4VisAttributes(G4Colour(0,1,1));
  tile_vol->SetVisAttributes(tile_vol_vis);
  // Create physical volume and place it inside wrapper
  G4VPhysicalVolume* tile_phys = new G4PVPlacement(0,G4ThreeVector(),tile_vol,"tile",air_vol,false,0,checkOverlaps);
  
  // Surface between tile and air
  G4OpticalSurface* tile_air = new G4OpticalSurface("tile_air");
  // Add properties                                                                                                   
  tile_air->SetType(dielectric_dielectric);
  tile_air->SetModel(glisur);
  tile_air->SetFinish(polished);
  G4LogicalBorderSurface* tile_air_surf = new G4LogicalBorderSurface("tile_air_surf",tile_phys,air_phys,tile_air); 

  G4double reflectivity_tile_air[] = {1.0, 1.0, 1.0, 1.0};  
  G4double efficiency_tile_air[] = {1.0, 1.0, 1.0, 1.0};  
    
  G4MaterialPropertiesTable *tile_air_MPT = new G4MaterialPropertiesTable();
  tile_air_MPT->AddProperty("REFLECTIVITY",wls_Energy,reflectivity_tile_air,wlsnum);
  tile_air_MPT->AddProperty("EFFICIENCY",wls_Energy,efficiency_tile_air,wlsnum);
  tile_air->SetMaterialPropertiesTable(tile_air_MPT);

  //
  // Fiber
  //
  // Outer cladding: fluorinated polymer (FP)
  // Using Polytetrafluoroethylene because it is the simplest and most widely used in optical fibers
  //G4Tubs *out_clad_shape_single = new G4Tubs("out_clad_shape_single",0.,diam_out/2,fiber_length/2,0.,2*M_PI); 
  //G4VSolid *out_clad_shape = new G4IntersectionSolid("out_clad_shape_single&&air_shape",air_shape,out_clad_shape_single,fiber_rot,G4ThreeVector());
  //G4VSolid *out_clad_shape1 = new G4IntersectionSolid("out_clad_shape1",air_shape,out_clad_shape_single,fiber_rot1,G4ThreeVector());
  //G4LogicalVolume *out_clad_vol = new G4LogicalVolume(out_clad_shape,FP,"out_clad_vol");
  //G4LogicalVolume *out_clad_vol1 = new G4LogicalVolume(out_clad_shape1,FP,"out_clad_vol1");

                                                
 //

  // Reflecting mirror at the end of the fiber
  G4Tubs *mirror_shape_single = new G4Tubs("mirror_shape_single",0.,diam_out/2,1.0*mm,0.,2*M_PI);
  G4VSolid *mirror_shape = new G4IntersectionSolid("mirror_shape",air_shape,mirror_shape_single,fiber_rot,G4ThreeVector(-2.0*mm,-5.0*cm,0));
  G4LogicalVolume *mirror_vol = new G4LogicalVolume(mirror_shape,Al,"mirror_vol");

  // Reflecting PMT at the end of the fiber
  G4Tubs *PMT_shape_single = new G4Tubs("PMT_shape_single",0.,(diam_out*10)/2,(2.0*mm)/2,0.,2*M_PI);
  G4VSolid *PMT_shape = new G4IntersectionSolid("PMT_shape",air_shape,PMT_shape_single,fiber_rot,G4ThreeVector());
  G4LogicalVolume *PMT_vol = new G4LogicalVolume(PMT_shape,FP,"PMT_vol");
    
  // Inner cladding: polymethylmethacrylate (PMMA)                                              
  G4Tubs *in_clad_shape_single = new G4Tubs("in_clad_shape_single",0.,diam_in/2,fiber_length/2,0.,2*M_PI);
  G4VSolid *in_clad_shape = new G4IntersectionSolid("in_clad_shape_single&&air_shape",air_shape,in_clad_shape_single,fiber_rot,G4ThreeVector());
  G4VSolid *in_clad_shape1 = new G4IntersectionSolid("in_clad_shape1",air_shape,in_clad_shape_single,fiber_rot1,G4ThreeVector());
  G4LogicalVolume *in_clad_vol = new G4LogicalVolume(in_clad_shape,PMMA,"in_clad_vol");
  G4LogicalVolume *in_clad_vol1 = new G4LogicalVolume(in_clad_shape1,PMMA,"in_clad_vol1");  

  // Core: polystylene (PS)
  G4Tubs *core_shape_single = new G4Tubs("core_shape_single",0.,diam_core/2,fiber_length/2,0.,2*M_PI);
  G4VSolid *core_shape = new G4IntersectionSolid("core_shape_single&&air_shape",air_shape,core_shape_single,fiber_rot,G4ThreeVector());
  G4VSolid *core_shape1 = new G4IntersectionSolid("core_shape1",air_shape,core_shape_single,fiber_rot1,G4ThreeVector());
  G4LogicalVolume *core_vol = new G4LogicalVolume(core_shape,polystyrene,"core_vol");
  G4LogicalVolume *core_vol1 = new G4LogicalVolume(core_shape1,polystyrene,"core_vol1");
  
  // Create fiber physical volume (outer cladding, other will be placed inside)
  // No rotation needed here because it was already applied when creating the intersection solid (fiber+air volume)
  //G4VPhysicalVolume *fiber_phys = new G4PVPlacement(0,fiber_tran,out_clad_vol,"fiber_top",air_vol,false,0,checkOverlaps);
 
  // Place inner cladding inside
  //G4VPhysicalVolume *in_clad_phys = new G4PVPlacement(0,G4ThreeVector(),in_clad_vol,"in_clad_top",out_clad_vol,false,0,checkOverlaps);
  // Place core
  G4VPhysicalVolume *core_phys = new G4PVPlacement(0,G4ThreeVector(),core_vol,"core_top",air_vol,false,0,checkOverlaps);
  core_vol->SetVisAttributes(new G4VisAttributes( G4Color::Magenta() ) );
  // Place mirror at the end
  G4VPhysicalVolume *mirror_phys = new G4PVPlacement(0,G4ThreeVector(0.,((small_side+d_side+(diam_out/cos(alpha)))/2)+((height+2*e_air)*tan(alpha))/2,(height+2*e_air)/2),mirror_vol,"mirror_top",logicWorld,false,0,checkOverlaps);

  G4OpticalSurface *Al_surf = new G4OpticalSurface("Al_mirror_surf");
  Al_surf->SetType(dielectric_metal);
  Al_surf->SetFinish(polished);
  Al_surf->SetModel(glisur);
  //G4LogicalBorderSurface* mirror_fiber_surf = new G4LogicalBorderSurface("mirror_fiber_surf",fiber_phys,mirror_phys,Al_surf);
  G4MaterialPropertiesTable *Al_surf_MPT = new G4MaterialPropertiesTable();
  Al_surf_MPT->AddProperty("REALRINDEX",wls_Energy,rindex_real_Al,wlsnum);
  Al_surf_MPT->AddProperty("IMAGINARYRINDEX",wls_Energy,rindex_im_Al,wlsnum);
  Al_surf->SetMaterialPropertiesTable(Al_surf_MPT);

  // Place fiber that comes out of wrapper
  //G4VPhysicalVolume *fiber_phys_1_top = new G4PVPlacement(0,G4ThreeVector(0.,((small_side+d_side+(diam_out/cos(alpha)))/2)-((height+2*e_air)*tan(alpha)),-(height+2*e_air)),out_clad_vol,"fiber_1_top",logicWorld,false,0,checkOverlaps);

  // Place fiber that comes out of wrapper
  G4VPhysicalVolume *PMT_phys = new G4PVPlacement(0,G4ThreeVector(0.,((small_side+d_side+(diam_out/cos(alpha)))/2)-((height+2*e_air)*tan(alpha))-((height*tan(alpha))/2)-(2.*mm*tan(alpha)),-(height+2*e_air)-(height/2)-(2.*mm)),PMT_vol,"PMT_top",logicWorld,false,0,checkOverlaps);
  
  // Create sensitive detector
  TileFCCFiberSD *fiber_sens = new TileFCCFiberSD("fiber_sens","FiberHitsCollection");
  core_vol->SetSensitiveDetector(fiber_sens);
  G4SDManager::GetSDMpointer()->AddNewDetector(fiber_sens);

  // Create sensitive detector
  TileFCCPmtSD *PMT_sens = new TileFCCPmtSD("PMT_sens","PmtHitsCollection");
  PMT_vol->SetSensitiveDetector(PMT_sens);
  G4SDManager::GetSDMpointer()->AddNewDetector(PMT_sens);

  fScoringVolume = tile_vol;
  fFiberVolume = core_vol;
  
  return physWorld;
  
  }
