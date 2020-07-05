#include "TileFCCPmtSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCPmtSD::TileFCCPmtSD(const G4String& name,const G4String& hitsCollectionName)
  : G4VSensitiveDetector(name),
    fHitsCollection(NULL)
{
  collectionName.insert(hitsCollectionName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
TileFCCPmtSD::~TileFCCPmtSD()
{}

void TileFCCPmtSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection  
  fHitsCollection = new TileFCCPmtHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce     
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 
G4bool TileFCCPmtSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  // energy deposit                                                               
  G4double edep = aStep->GetTrack()->GetTotalEnergy();
  
  //if (edep==0.) return false;
  
  TileFCCPmtHit* newHit = new TileFCCPmtHit();

  newHit->SetEdep(edep);
  newHit->SetPos (aStep->GetPostStepPoint()->GetPosition());
  newHit->SetID(aStep->GetTrack()->GetParentID());
  
  if(aStep->GetTrack()->GetCreatorProcess()==NULL){
    newHit->SetProcess("NULL");
  }else{ 
    newHit->SetProcess(aStep->GetTrack()->GetCreatorProcess()->GetProcessName());
  }

  fHitsCollection->insert( newHit );

  //newHit->Print();
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......  
void TileFCCPmtSD::EndOfEvent(G4HCofThisEvent*)
{
  if( verboseLevel > 1 ){
    G4int nofHits = fHitsCollection->entries();
    G4cout << G4endl
	   << "-------->Hits Collection: in this event they are " << nofHits
	   << " hits in the tile: " << G4endl;
    for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print(); 
  }
}
