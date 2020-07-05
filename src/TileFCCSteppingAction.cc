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
#include "TileFCCSteppingMessenger.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalPhoton.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCSteppingAction::TileFCCSteppingAction(TileFCCEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0),
  fFiberVolume(0),
  fOneStepPrimaries(true)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCSteppingAction::~TileFCCSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TileFCCSteppingAction::UserSteppingAction(const G4Step* step)
{
  G4Track *track = step->GetTrack();

  if (!fScoringVolume) { 
    const TileFCCDetectorConstruction* detectorConstruction
      = static_cast<const TileFCCDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }

  G4StepPoint* PrePoint = step->GetPreStepPoint();
  G4VPhysicalVolume* PrePV = PrePoint->GetPhysicalVolume();

  G4StepPoint* PostPoint = step->GetPostStepPoint();
  G4VPhysicalVolume* PostPV = PrePoint->GetPhysicalVolume();
  
  // Get secondaries
  const std::vector<const G4Track*>* secondaries = step->GetSecondaryInCurrentStep();

  if (secondaries->size()>0) {
    for(unsigned int i=0; i<secondaries->size(); ++i) {
      if (secondaries->at(i)->GetParentID()>0) {
	if(secondaries->at(i)->GetDynamicParticle()->GetParticleDefinition()
	   == G4OpticalPhoton::OpticalPhotonDefinition()){
	  
	  if (secondaries->at(i)->GetCreatorProcess()->GetProcessName() == "Scintillation"){

	    fEventAction->AddOpPhotonEdep(secondaries->at(i)->GetTotalEnergy());
	    fEventAction->AddSecondaryScint();

	  }else if(secondaries->at(i)->GetCreatorProcess()->GetProcessName() == "OpWLS"){
	    
	    fEventAction->AddWLSPhotonEdep(secondaries->at(i)->GetTotalEnergy());
	    fEventAction->AddSecondaryWLS();

	  }
	}
      }
    }
  }

  // get volume of the current step
  G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  if(PostPV->GetName()=="PMT_top"){

    // Kill photons once they hit the PMT
    track->SetTrackStatus(fKillTrackAndSecondaries);

  }

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();

  // check if we are in scoring volume (tile volume)
  if (volume == fScoringVolume){
  
    if(track->GetParentID()==0){

      fEventAction->AddEdep(edepStep);  
      
      // save hit position
      G4ThreeVector vec_hit = step->GetTrack()->GetPosition();
      G4double x_hit = vec_hit.x();
      G4double y_hit = vec_hit.y();
      G4double z_hit = vec_hit.z();
      fEventAction->AddHit(x_hit,y_hit,z_hit);
    }
    
  }else if(volume == fFiberVolume){

    fEventAction->AddEdepFiber(edepStep);

  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

