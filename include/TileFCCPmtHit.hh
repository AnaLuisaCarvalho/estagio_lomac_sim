#ifndef TileFCCPmtHit_h
#define TileFCCPmtHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"
#include "G4String.hh"

class TileFCCPmtHit : public G4VHit
{
public:
  TileFCCPmtHit();
  TileFCCPmtHit(const TileFCCPmtHit&);
  virtual ~TileFCCPmtHit();

  // operators                               
  const TileFCCPmtHit& operator=(const TileFCCPmtHit&);
  //G4bool operator==(const TileFCCPmtHit&) const;

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
typedef G4THitsCollection<TileFCCPmtHit> TileFCCPmtHitsCollection;

extern G4ThreadLocal G4Allocator<TileFCCPmtHit>* TileFCCPmtHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......    
inline void* TileFCCPmtHit::operator new(size_t)
{
  if(!TileFCCPmtHitAllocator)
    TileFCCPmtHitAllocator = new G4Allocator<TileFCCPmtHit>;
  return (void *) TileFCCPmtHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......            
inline void TileFCCPmtHit::operator delete(void *hit)
{
  TileFCCPmtHitAllocator->FreeSingle((TileFCCPmtHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......    
#endif
