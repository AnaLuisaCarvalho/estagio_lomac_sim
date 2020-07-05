#include "TileFCCPmtHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<TileFCCPmtHit>* TileFCCPmtHitAllocator=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TileFCCPmtHit::TileFCCPmtHit()
  : G4VHit(),
    fEdep(0.),
    fPos(G4ThreeVector())
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......  

TileFCCPmtHit::~TileFCCPmtHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TileFCCPmtHit::TileFCCPmtHit(const TileFCCPmtHit& hit)
  : G4VHit()
{
  fEdep      = hit.fEdep;
  fPos       = hit.fPos;
  fID        = hit.fID;
  fProcess   = hit.fProcess;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

const TileFCCPmtHit& TileFCCPmtHit::operator=(const TileFCCPmtHit& hit)
{
  fEdep      = hit.fEdep;
  fPos       = hit.fPos;
  fID        = hit.fID;
  fProcess   = hit.fProcess;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......  

void TileFCCPmtHit::Print()
{
  G4cout
    << "Edep: "
    << std::setw(7) << G4BestUnit(fEdep,"Energy")
    << " Position: "
    << std::setw(7) << G4BestUnit( fPos,"Length")
    << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

