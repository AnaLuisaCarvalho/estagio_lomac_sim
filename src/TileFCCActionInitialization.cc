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
/// \file TileFCCActionInitialization.cc
/// \brief Implementation of the TileFCCActionInitialization class

#include "TileFCCActionInitialization.hh"
#include "TileFCCPrimaryGeneratorAction.hh"
#include "TileFCCRunAction.hh"
#include "TileFCCEventAction.hh"
#include "TileFCCSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCActionInitialization::TileFCCActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCActionInitialization::~TileFCCActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TileFCCActionInitialization::BuildForMaster() const
{

  TileFCCEventAction* eventAction = new TileFCCEventAction();
  TileFCCRunAction* runAction = new TileFCCRunAction(eventAction);
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TileFCCActionInitialization::Build() const
{
  SetUserAction(new TileFCCPrimaryGeneratorAction);
 
  TileFCCEventAction* eventAction = new TileFCCEventAction();
  SetUserAction(eventAction);
 
  TileFCCRunAction* runAction = new TileFCCRunAction(eventAction);
  SetUserAction(runAction);

  SetUserAction(new TileFCCSteppingAction(eventAction));
  
  //SetUserAction(new TileFCCSteppingAction(eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
