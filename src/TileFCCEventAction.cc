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

#include "G4RunManager.hh"
#include "G4Event.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCEventAction::TileFCCEventAction(TileFCCRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.),
  fHitX(-999.),
  fHitY(-999.),
  fHitZ(-999.),
  fOpPhotonEdep(0.)
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCEventAction::~TileFCCEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TileFCCEventAction::BeginOfEventAction(const G4Event*)
{    
  fEdep = 0.;
  fOpPhotonEdep = 0.;
  fHitX = -999.;
  fHitY = -999.;
  fHitZ = -999.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TileFCCEventAction::EndOfEventAction(const G4Event*)
{   
  // accumulate statistics in run action
  fRunAction->AddEdep(fEdep);
  fRunAction->AddOpPhotonEdep(fOpPhotonEdep);
  
  // get analysis manager                                                                                                 
  auto analysisManager = G4AnalysisManager::Instance();

  // Fill ntuple
  analysisManager->FillNtupleDColumn(0, fEdep);
  analysisManager->FillNtupleDColumn(1, fHitX);
  analysisManager->FillNtupleDColumn(2, fHitY);
  analysisManager->FillNtupleDColumn(3, fHitZ);
  
  analysisManager->FillNtupleDColumn(4, fOpPhotonEdep);
  
  analysisManager->AddNtupleRow();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
