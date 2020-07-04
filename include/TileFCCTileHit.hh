#ifndef TileFCCTileHit_h
#define TileFCCTileHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class TileFCCTileHit : public G4VHit
{
public:
  TileFCCTileHit();
  TileFCCTileHit(const TileFCCTileHit&);
  virtual ~TileFCCTileHit();

  // operators                               
  const TileFCCTileHit& operator=(const TileFCCTileHit&);
  //G4bool operator==(const TileFCCTileHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  // methods from base class                                                                              
  //virtual void Draw();
  virtual void Print();

  // Set methods                                                                                     
  void SetEdep     (G4double de)      { fEdep = de; };
  void SetPos      (G4ThreeVector xyz){ fPos = xyz; };

  // Get methods                                                                                 
  G4double GetEdep() const     { return fEdep; };
  G4ThreeVector GetPos() const { return fPos; };

private:

  G4double      fEdep;
  G4ThreeVector fPos;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......     
typedef G4THitsCollection<TileFCCTileHit> TileFCCTileHitsCollection;

extern G4ThreadLocal G4Allocator<TileFCCTileHit>* TileFCCTileHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......    
inline void* TileFCCTileHit::operator new(size_t)
{
  if(!TileFCCTileHitAllocator)
    TileFCCTileHitAllocator = new G4Allocator<TileFCCTileHit>;
  return (void *) TileFCCTileHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......            
inline void TileFCCTileHit::operator delete(void *hit)
{
  TileFCCTileHitAllocator->FreeSingle((TileFCCTileHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......    
#endif
