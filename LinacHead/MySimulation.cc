// This is the program to simulate Gamma ART-6000TM
// Version: 2.0
// Date: 02/09/2022
// Author: Hung Bui Tien
// Email: hungbuitien19081997@gmail.com
// Organization: Hanoi University of Science and Technology 


#include <iostream>

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4Types.hh"
#include "Randomize.hh"
#include <ctime>

#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "PhysicsList.hh"


using namespace std;

int main(int argc, char** argv)
{
	G4Random::setTheEngine(new CLHEP::RanecuEngine);

	//#ifdef G4MULTITHREADED
	//	G4MTRunManager* runManager = new G4MTRunManager;
	//	int _numberOfThreads=G4Threading::G4GetNumberOfCores();
	//	runManager->SetNumberOfThreads( _numberOfThreads);
	//#else
		G4RunManager* runManager = new G4RunManager;
	//#endif
	
	// Detect interactive mode (if no macro provided) and define UI session
    //
	G4UIExecutive* ui = 0;

	// Set mandatory initialization classes
	//
	runManager->SetUserInitialization(new DetectorConstruction());
	runManager->SetUserInitialization(new PhysicsList());
	runManager->SetUserInitialization(new ActionInitialization()); 

	// Process macro or start UI session
	//
	if (argc == 1)
	{
		ui = new G4UIExecutive(argc, argv);
	}

	// Initialize visualization
	//
	G4VisManager* visManager = new G4VisExecutive();
	visManager->Initialize();

	// Get the pointer to the User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	if (ui)
	{
		// interactive mode : define UI session
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
		delete ui;
	}
	else
	{
		// batch mode
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command + fileName);

		int _NumberOfRunningWorkerThreads=G4Threading::GetNumberOfRunningWorkerThreads();
		DetectorConstruction * pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
		int TotalNumberOfToBeProcessedEvents=pDetectorConstruction->NumberOfEventsPerThread*_NumberOfRunningWorkerThreads;
		pDetectorConstruction-> NUMBER_OF_THREADS=_NumberOfRunningWorkerThreads;
		runManager->SetEventModulo(pDetectorConstruction->NumberOfEventsPerThread);
		runManager->BeamOn(TotalNumberOfToBeProcessedEvents);
	}
	
	delete visManager;
	delete runManager;

	return 0;
}