#ifndef TileFCCPmtSD_h
#define TileFCCPmtSD_h 1

#include "G4VSensitiveDetector.hh"

#include "TileFCCPmtHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class TileFCCPmtSD : public G4VSensitiveDetector
{
public:
  TileFCCPmtSD(const G4String& name,
	      const G4String& hitsCollectionName);
  virtual ~TileFCCPmtSD();

  // methods from base class                                                
  virtual void   Initialize(G4HCofThisEvent* hitCollection);
  virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
  virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

private:
 TileFCCPmtHitsCollection* fHitsCollection;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
