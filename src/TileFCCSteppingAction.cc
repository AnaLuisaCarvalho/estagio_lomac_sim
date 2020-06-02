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
/// \file TileFCCSteppingAction.cc
/// \brief Implementation of the TileFCCSteppingAction class

#include "TileFCCSteppingAction.hh"
#include "TileFCCEventAction.hh"
#include "TileFCCDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalPhoton.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCSteppingAction::TileFCCSteppingAction(TileFCCEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCSteppingAction::~TileFCCSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TileFCCSteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) { 
    const TileFCCDetectorConstruction* detectorConstruction
      = static_cast<const TileFCCDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }

  const std::vector<const G4Track*>* secondaries = step->GetSecondaryInCurrentStep();

  if (secondaries->size()>0) {
    for(unsigned int i=0; i<secondaries->size(); ++i) {
      if (secondaries->at(i)->GetParentID()>0) {
	if(secondaries->at(i)->GetDynamicParticle()->GetParticleDefinition()
	   == G4OpticalPhoton::OpticalPhotonDefinition()){
	  if (secondaries->at(i)->GetCreatorProcess()->GetProcessName() == "Scintillation"){

	    fEventAction->AddOpPhotonEdep(secondaries->at(i)->GetTotalEnergy());
	  }
	}
      }
    }
  }

  // get volume of the current step
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

  // check if we are in scoring volume (tile volume)
  if (volume != fScoringVolume) return;

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);  

  // save hit position
  G4ThreeVector vec_hit = step->GetTrack()->GetPosition();
  G4double x_hit = vec_hit.x();
  G4double y_hit = vec_hit.y();
  G4double z_hit = vec_hit.z();
  fEventAction->AddHit(x_hit,y_hit,z_hit);  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

