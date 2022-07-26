#include "PhysicsListMessenger.hh"
#include "PhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAnInteger.hh"

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
PhysicsListMessenger::PhysicsListMessenger(PhysicsList* pPhys)
:pPhysicsList(pPhys)
{
  physDir = new G4UIdirectory("/Physics/");
  physDir->SetGuidance("Commands to activate physics models and set cuts");
  gammaCutCmd = new G4UIcmdWithADoubleAndUnit("/Physics/setGCut",this);  
  gammaCutCmd->SetGuidance("Set gamma cut.");
  gammaCutCmd->SetParameterName("Gcut",false);
  gammaCutCmd->SetUnitCategory("Length");
  gammaCutCmd->SetRange("Gcut>0.0");
  gammaCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  electCutCmd = new G4UIcmdWithADoubleAndUnit("/Physics/setECut",this);  
  electCutCmd->SetGuidance("Set electron cut.");
  electCutCmd->SetParameterName("Ecut",false);
  electCutCmd->SetUnitCategory("Length");
  electCutCmd->SetRange("Ecut>0.0");
  electCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  protoCutCmd = new G4UIcmdWithADoubleAndUnit("/Physics/setPCut",this);  
  protoCutCmd->SetGuidance("Set positron cut.");
  protoCutCmd->SetParameterName("Pcut",false);
  protoCutCmd->SetUnitCategory("Length");
  protoCutCmd->SetRange("Pcut>0.0");
  protoCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
  allCutCmd = new G4UIcmdWithADoubleAndUnit("/Physics/setCuts",this);  
  allCutCmd->SetGuidance("Set cut for all.");
  allCutCmd->SetParameterName("cut",false);
  allCutCmd->SetUnitCategory("Length");
  allCutCmd->SetRange("cut>0.0");
  allCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
 // Bremspe command
  Bremspe_NsplitCmd = new G4UIcmdWithAnInteger("/Physics/Bremspe_Nsplit",this);  
  Bremspe_NsplitCmd->SetGuidance("Splitting factor");
  Bremspe_NsplitCmd->SetParameterName("Bremspe_Nsplit",false);
  Bremspe_NsplitCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
	//Bremspe_NsplitCmd->SetDefaultUnit("");
	//Bremspe_NsplitCmd->SetDefaultValue(80);

  Bremspe_EnabledCmd = new G4UIcmdWithABool("/Physics/Bremspe_Enabled",this);  
  Bremspe_EnabledCmd->SetGuidance("enable or disable Bremspe technique");
  Bremspe_EnabledCmd->SetParameterName("Bremspe_Enabled",false);
  Bremspe_EnabledCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 
  //Bremspe_EnabledCmd->SetDefaultUnit("");
	//Bremspe_EnabledCmd->SetDefaultValue(true);
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
PhysicsListMessenger::~PhysicsListMessenger()
{
  delete gammaCutCmd;
  delete electCutCmd;
  delete protoCutCmd;
  delete allCutCmd;
  delete physDir;    
  delete Bremspe_EnabledCmd;
  delete Bremspe_NsplitCmd;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
void PhysicsListMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue)
{       
      if( command == gammaCutCmd )
        { pPhysicsList->SetCutForGamma(gammaCutCmd->GetNewDoubleValue(newValue));}  
 else if( command == electCutCmd )
        { pPhysicsList->SetCutForElectron(electCutCmd->GetNewDoubleValue(newValue));}
 else if( command == protoCutCmd )
        { pPhysicsList->SetCutForPositron(protoCutCmd->GetNewDoubleValue(newValue));}
 else if( command == allCutCmd )
        {
         G4double cut = allCutCmd->GetNewDoubleValue(newValue);
         pPhysicsList->SetCutForGamma(cut);
         pPhysicsList->SetCutForElectron(cut);
         pPhysicsList->SetCutForPositron(cut);
         } 
 else if(command ==Bremspe_NsplitCmd) { 
         pPhysicsList->SetBremspe_Nsplit(Bremspe_NsplitCmd->GetNewIntValue(newValue));
        } 
 else if (command== Bremspe_EnabledCmd) {
         pPhysicsList->SetBremspe_Enabled(Bremspe_EnabledCmd->GetNewBoolValue(newValue));
        }
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
