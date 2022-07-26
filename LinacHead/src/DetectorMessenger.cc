#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
DetectorMessenger::DetectorMessenger(DetectorConstruction* pDetectorConstruction)
: G4UImessenger(),fDetectorConstruction(pDetectorConstruction)
{
    H5PhaseSpaceDir            = new G4UIdirectory("/Parameters/");
    H5PhaseSpaceZStopCmd       = new G4UIcmdWithADoubleAndUnit("/Parameters/ZStop",this);  
    H5PhaseSpaceZStopCmd ->SetParameterName("ZStop",false);
    H5PhaseSpaceZStopCmd ->SetUnitCategory("Length");
    H5PhaseSpaceZStopCmd ->SetRange("");
    H5PhaseSpaceZStopCmd ->AvailableForStates(G4State_PreInit,G4State_Idle);
    H5PhaseSpaceNameCmd        = new G4UIcmdWithAString("/Parameters/H5PhaseSpaceName",this);
    H5PhaseSpaceNameCmd ->SetParameterName("H5PhaseSpaceName",false);
    H5PhaseSpaceNameCmd ->SetDefaultValue("example");
    NameOfGeomFromTextFileCmd  = new G4UIcmdWithAString("/Parameters/NameOfGeomFromTextFile",this);
    NameOfGeomFromTextFileCmd ->SetParameterName("NameOfGeomFromTextFile",false);
    NameOfGeomFromTextFileCmd ->SetDefaultValue("");

    NumberOfEventsPerThread_Cmd = new G4UIcmdWithAnInteger("/Parameters/NumberOfEventsPerThread",this);  
    NumberOfEventsPerThread_Cmd->SetGuidance("Set NumberOfEventsPerThread.");
    NumberOfEventsPerThread_Cmd ->SetParameterName("NumberOfEventsPerThread",false);
    NumberOfEventsPerThread_Cmd ->SetRange("NumberOfEventsPerThread>=0");
    NumberOfEventsPerThread_Cmd ->AvailableForStates(G4State_PreInit,G4State_Idle);
}

DetectorMessenger::~DetectorMessenger()
{
    delete H5PhaseSpaceNameCmd;
    delete H5PhaseSpaceZStopCmd;
    delete NameOfGeomFromTextFileCmd;
    delete H5PhaseSpaceDir;    
    delete NumberOfEventsPerThread_Cmd;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
    if( command ==  H5PhaseSpaceZStopCmd)
    {
        fDetectorConstruction->SetH5PhaseSpaceZStop(H5PhaseSpaceZStopCmd->GetNewDoubleValue(newValue));
    }
    else  if( command == H5PhaseSpaceNameCmd )
    {
        fDetectorConstruction->SetH5PhaseSpaceName(newValue);
    }
    else  if( command == NameOfGeomFromTextFileCmd )    
    {
        fDetectorConstruction->SetNameOfGeomFromTextFile(newValue);
    }
    else  if( command == NumberOfEventsPerThread_Cmd )
    {
        fDetectorConstruction-> SetNumberOfEventsPerThread(NumberOfEventsPerThread_Cmd->GetNewIntValue(newValue));
    }        
}       
