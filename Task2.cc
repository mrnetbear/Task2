// Task2.cc : Defines the entry point for the application.
//

#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "include/DetectorConstruction.hh"
#include "include/PhysicsList.hh"

#include "include/ActionInit.hh"

#include <random>
#include <unistd.h>
#include "Randomize.hh"


#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"//Многопоточный
#else
#include "G4RunManager.hh"//Непараллельный, однопоточное моделирование
#endif


using namespace TASK2;

// for printing
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine); 
	CLHEP::HepRandom::setTheSeed(time(0) + getpid()); 

	// Initialize (or don't) a UI
	G4UIExecutive* ui = nullptr;
	if (argc == 1) {
		ui = new G4UIExecutive(argc, argv);
	}

	// ======================================================================
	// RunManager, + 3 Required additions:
	// PrimaryGeneratorAction,
	// PhysicsList,
	// DetectorConstruction.
	// ======================================================================

#ifdef G4MULTITHREADED
	G4MTRunManager* runManager = new G4MTRunManager;
	//Выбор максимального числа потоков в выполняемой системе (на компьютере)
	// либо можно вручную задать число потоков
	runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
#else
	G4RunManager* runManager = new G4RunManager;
#endif



	//G4MTRunManager* runManager = new G4MTRunManager;
	//Выбор максимального числа потоков в выполняемой системе (на компьютере)
	// либо можно вручную задать число потоков
	//runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());

	
	// set 3 required initialization classes
	runManager->SetUserInitialization(new DetectorConstruction());
	runManager->SetUserInitialization(new PhysicsList());
	runManager->SetUserInitialization(new ActionInit());

	// ======================================================================
	// OTHER CLASSES:
	// Vismanager, scoringmanager, etc.
	// ======================================================================

	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

	// START UI =============================================================

	// get pointer to UI manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	// Run macro or start UI
	if (!ui) {
		// batch mode
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command + fileName);
	}
	else {
		// run visualization
		UImanager->ApplyCommand("/control/execute vis.mac");

		// use UI
		ui->SessionStart();
		delete ui;
	}

	// clean up
	delete visManager;
	delete runManager;


	return 0;
}
