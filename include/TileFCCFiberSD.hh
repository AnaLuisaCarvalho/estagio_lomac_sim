#ifndef TileFCCFiberSD_h
#define TileFCCFiberSD_h 1

#include "G4VSensitiveDetector.hh"

#include "TileFCCFiberHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class TileFCCFiberSD : public G4VSensitiveDetector
{
public:
  TileFCCFiberSD(const G4String& name,
	      const G4String& hitsCollectionName);
  virtual ~TileFCCFiberSD();

  // methods from base class                                                
  virtual void   Initialize(G4HCofThisEvent* hitCollection);
  virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
  virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

private:
 TileFCCFiberHitsCollection* fHitsCollection;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
