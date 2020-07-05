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
/// \file TileFCCEventAction.hh
/// \brief Definition of the TileFCCEventAction class

#ifndef TileFCCEventAction_h
#define TileFCCEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include <vector>

//class TileFCCRunAction;

/// Event action class
///

class TileFCCEventAction : public G4UserEventAction
{
  public:
    TileFCCEventAction();
    virtual ~TileFCCEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }
    void AddEdepFiber(G4double edep_fiber) { fEdepFiber += edep_fiber; }
    void AddHit(G4double hitX, G4double hitY, G4double hitZ) {
      fHitX = hitX;
      fHitY = hitY;
      fHitZ = hitZ;
    }

    void AddOpPhotonEdep(G4double photon_edep) { fOpPhotonEdep += photon_edep; }
    void AddWLSPhotonEdep(G4double wlsphoton_edep) { fWLSPhotonEdep += wlsphoton_edep; }

    void AddSecondaryScint() { fNScintPhotons+=1; }
    void AddSecondaryWLS() { fNWLSPhotons+=1; }

    std::vector<G4double>& GetTileEdep(){ return fTileEdep; } 
    std::vector<G4double>& GetFiberEdep(){ return fFiberEdep; } 
    std::vector<G4double>& GetPMTEdep(){ return fPMTEdep; } 
  
  private:
  //TileFCCRunAction* fRunAction;
    G4double     fEdep;
    G4double fEdepFiber;
    G4double fHitX;
    G4double fHitY;
    G4double fHitZ;
    G4double fOpPhotonEdep;
    G4double fWLSPhotonEdep;
    G4int fNScintPhotons;
    G4int fNWLSPhotons;
    G4int fNPMTPhotons;
    std::vector<G4double> fTileEdep;
    std::vector<G4double> fFiberEdep;
    std::vector<G4double> fPMTEdep;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
