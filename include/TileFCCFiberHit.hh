#ifndef TileFCCFiberHit_h
#define TileFCCFiberHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"
#include "G4String.hh"

class TileFCCFiberHit : public G4VHit
{
public:
  TileFCCFiberHit();
  TileFCCFiberHit(const TileFCCFiberHit&);
  virtual ~TileFCCFiberHit();

  // operators                               
  const TileFCCFiberHit& operator=(const TileFCCFiberHit&);
  //G4bool operator==(const TileFCCFiberHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);
  // methods from base class                                                    
  //virtual void Draw();
  virtual void Print();

  // Set methods                                                                                     
  void SetEdep     (G4double de)      { fEdep = de; };
  void SetPos      (G4ThreeVector xyz){ fPos = xyz; };
  void SetID       (G4int id)         { fID = id;   };
  void SetProcess  (G4String p)       { fProcess = p; };

  // Get methods                                                                                 
  G4double GetEdep() const     { return fEdep; };
  G4ThreeVector GetPos() const { return fPos; };
  G4int GetID() const          { return fID;  };  
  G4String GetProcess() const  { return fProcess; };

private:

  G4double      fEdep;
  G4ThreeVector fPos;
  G4int         fID;
  G4String      fProcess;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......     
typedef G4THitsCollection<TileFCCFiberHit> TileFCCFiberHitsCollection;

extern G4ThreadLocal G4Allocator<TileFCCFiberHit>* TileFCCFiberHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......    
inline void* TileFCCFiberHit::operator new(size_t)
{
  if(!TileFCCFiberHitAllocator)
    TileFCCFiberHitAllocator = new G4Allocator<TileFCCFiberHit>;
  return (void *) TileFCCFiberHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......            
inline void TileFCCFiberHit::operator delete(void *hit)
{
  TileFCCFiberHitAllocator->FreeSingle((TileFCCFiberHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......    
#endif
