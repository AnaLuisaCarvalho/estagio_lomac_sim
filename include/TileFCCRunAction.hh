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
/// \file TileFCCRunAction.hh
/// \brief Definition of the TileFCCRunAction class

#ifndef TileFCCRunAction_h
#define TileFCCRunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class TileFCCEventAction;

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class TileFCCRunAction : public G4UserRunAction
{
  public:
    TileFCCRunAction(TileFCCEventAction* eventAction);
    virtual ~TileFCCRunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddEdep (G4double edep); 
    void AddEdepFiber (G4double edep_fiber); 
    void AddHit(G4double hitX, G4double hitY, G4double hitZ);
  
    void AddOpPhotonEdep(G4double photon_edep);
    void AddWLSPhotonEdep(G4double wlsphoton_edep);
  
    void AddSecondaryScint();
    void AddSecondaryWLS();

  private:
    G4Accumulable<G4double> fEdep;
    G4double fEdepFiber;
    G4Accumulable<G4double> fEdep2;
    G4double fHitX;
    G4double fHitY;
    G4double fHitZ;
    G4double fOpPhotonEdep;
    G4double fWLSPhotonEdep;
    G4double fNScintPhotons;
    G4double fNWLSPhotons;
    TileFCCEventAction* fEventAction;

};

#endif

