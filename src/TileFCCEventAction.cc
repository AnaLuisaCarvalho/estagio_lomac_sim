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
/// \file TileFCCEventAction.cc
/// \brief Implementation of the TileFCCEventAction class

#include "TileFCCEventAction.hh"
#include "TileFCCRunAction.hh"
#include "TileFCCAnalysis.hh"
#include "TileFCCTileHit.hh"
#include "TileFCCFiberHit.hh"
#include "TileFCCPmtHit.hh"

#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Find hit collection
G4VHitsCollection* GetHC(const G4Event* event, G4int collId){
  auto hce = event->GetHCofThisEvent();
  if (!hce) {
    G4ExceptionDescription msg;
    msg << "No hits collection of this event found." << G4endl;
    G4Exception("B5EventAction::EndOfEventAction()",
		"B5Code001", JustWarning, msg);
    return nullptr;
  }

  auto hc = hce->GetHC(collId);
  if ( ! hc) {
    G4ExceptionDescription msg;
    msg << "Hits collection " << collId << " of this event not found." << G4endl;
    G4Exception("B5EventAction::EndOfEventAction()",
                "B5Code001", JustWarning, msg);
  }
  return hc;
}

TileFCCEventAction::TileFCCEventAction()
: G4UserEventAction(),
  fEdep(0.),
  fEdepFiber(0.),
  fHitX(-999.),
  fHitY(-999.),
  fHitZ(-999.),
  fOpPhotonEdep(0.),
  fWLSPhotonEdep(0.)
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCEventAction::~TileFCCEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TileFCCEventAction::BeginOfEventAction(const G4Event*)
{    
  fEdep = 0.;
  fOpPhotonEdep = 0.;
  fWLSPhotonEdep = 0.;
  fNScintPhotons = 0;
  fNWLSPhotons = 0;
  fNPMTPhotons = 0;
  fHitX = -999.;
  fHitY = -999.;
  fHitZ = -999.;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TileFCCEventAction::EndOfEventAction(const G4Event* event)
{   
  // accumulate statistics in run action
  // fRunAction->AddEdep(fEdep);
  // fRunAction->AddEdepFiber(fEdepFiber);
  // fRunAction->AddOpPhotonEdep(fOpPhotonEdep);
  // fRunAction->AddWLSPhotonEdep(fWLSPhotonEdep);  
  // fRunAction->AddSecondaryScint();
  // fRunAction->AddSecondaryWLS();
  
  G4int eventID = event->GetEventID();

  G4int id_tile = G4SDManager::GetSDMpointer()->GetCollectionID("TileHitsCollection");
  G4VHitsCollection* hc_tile = event->GetHCofThisEvent()->GetHC(id_tile);

  G4int id_fiber = G4SDManager::GetSDMpointer()->GetCollectionID("FiberHitsCollection");
  G4VHitsCollection* hc_fiber = event->GetHCofThisEvent()->GetHC(id_fiber);  

  G4int id_pmt = G4SDManager::GetSDMpointer()->GetCollectionID("PmtHitsCollection");
  G4VHitsCollection* hc_pmt = event->GetHCofThisEvent()->GetHC(id_pmt);  

  G4int count_scint_photons = 0;
  //std::vector<G4double> fTileEdep = {};
  // Loop over collection
  for(int i=0; i<hc_tile->GetSize(); i++){

    auto hit = static_cast<TileFCCTileHit*>(hc_tile->GetHit(i));
    G4double edep = hit->GetEdep();
    
    // If it is primary particle (electron)
    if(hit->GetID()==0){
      
      fEdep = edep;
      fHitX = hit->GetPos().x();
      fHitY = hit->GetPos().y();
      fHitZ = hit->GetPos().z();

    }

    if(hit->GetProcess() == "Scintillation"){

      count_scint_photons += 1;
      fTileEdep.push_back(edep/eV);
      
    }

  } // End of loop over hits

  fNScintPhotons = count_scint_photons;  

  G4int count_wls_photons = 0;
  for(int i = 0; i<hc_fiber->GetSize(); i++){

    auto hit = static_cast<TileFCCFiberHit*>(hc_fiber->GetHit(i));
    G4double edep = hit->GetEdep();

    if(hit->GetProcess() == "OpWLS" && hit->GetTrackStatus()==2){

      count_wls_photons += 1;
      fFiberEdep.push_back(edep/eV);
      
    }

  }

  fNWLSPhotons = count_wls_photons;

  G4int count_pmt_photons = 0;
  for(int i = 0; i<hc_pmt->GetSize(); i++){

    auto hit = static_cast<TileFCCPmtHit*>(hc_pmt->GetHit(i));
    G4double edep = hit->GetEdep();

    count_pmt_photons += 1;
    fPMTEdep.push_back(edep/eV);
      
  }

  fNPMTPhotons = count_pmt_photons;

  // get analysis manager  
  auto analysisManager = G4AnalysisManager::Instance();

  // Fill ntuple
  analysisManager->FillNtupleDColumn(0, fEdep/eV);
  analysisManager->FillNtupleDColumn(1, fHitX);
  analysisManager->FillNtupleDColumn(2, fHitY);
  analysisManager->FillNtupleDColumn(3, fHitZ);
  
  analysisManager->FillNtupleDColumn(4, fNScintPhotons);
  analysisManager->FillNtupleDColumn(6, fNWLSPhotons);
  analysisManager->FillNtupleDColumn(8, fNPMTPhotons);
  
  analysisManager->AddNtupleRow();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
