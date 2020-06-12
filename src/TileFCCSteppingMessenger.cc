
#include "TileFCCSteppingMessenger.hh"
#include "TileFCCSteppingAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"

TileFCCSteppingMessenger::TileFCCSteppingMessenger(TileFCCSteppingAction* step)
  : fStepping(step)
{
  fOneStepPrimariesCmd = new G4UIcmdWithABool("/TileFCC/oneStepPrimaries",this);
  fOneStepPrimariesCmd->
    SetGuidance("Only allows primaries to go one step before being killed.");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TileFCCSteppingMessenger::~TileFCCSteppingMessenger(){
  delete fOneStepPrimariesCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void
TileFCCSteppingMessenger::SetNewValue(G4UIcommand* command,G4String newValue){
  if( command == fOneStepPrimariesCmd ){
    fStepping->SetOneStepPrimaries(fOneStepPrimariesCmd
				   ->GetNewBoolValue(newValue));
  }
}
