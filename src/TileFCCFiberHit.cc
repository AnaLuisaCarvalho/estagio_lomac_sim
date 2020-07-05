#include "TileFCCFiberHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<TileFCCFiberHit>* TileFCCFiberHitAllocator=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TileFCCFiberHit::TileFCCFiberHit()
  : G4VHit(),
    fEdep(0.),
    fPos(G4ThreeVector())
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......  

TileFCCFiberHit::~TileFCCFiberHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCFiberHit::TileFCCFiberHit(const TileFCCFiberHit& hit)
  : G4VHit()
{
  fEdep      = hit.fEdep;
  fPos       = hit.fPos;
  fID        = hit.fID;
  fProcess   = hit.fProcess;
  fTrackStatus = hit.fTrackStatus;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

const TileFCCFiberHit& TileFCCFiberHit::operator=(const TileFCCFiberHit& hit)
{
  fEdep      = hit.fEdep;
  fPos       = hit.fPos;
  fID        = hit.fID;
  fProcess   = hit.fProcess;
  fTrackStatus = hit.fTrackStatus;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......  

void TileFCCFiberHit::Print()
{
  G4cout
    << "Edep: "
    << std::setw(7) << G4BestUnit(fEdep,"Energy")
    << " Position: "
    << std::setw(7) << G4BestUnit( fPos,"Length")
    << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

