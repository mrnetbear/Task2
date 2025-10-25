#include "../include/RunAction.hh"
#include "G4ThreeVector.hh"
#include "../include/PrimaryGeneratorAction.hh"
#include "Randomize.hh"
#include <random>

namespace TASK2 {
	RunAction::RunAction() {

		// access analysis manager
		auto analysisManager = G4AnalysisManager::Instance();

		// set default settings
		analysisManager->SetDefaultFileType("root");
		analysisManager->SetNtupleMerging(true);
		analysisManager->SetVerboseLevel(1);
		analysisManager->SetFileName("NTuples");

		// create nTuple to store the data:
		analysisManager->CreateNtuple("Scintillator energy deposit", "Hits");
		// The letters D, I, S, F correspond to types
		analysisManager->CreateNtupleDColumn("Energy"); //   id = 0
		analysisManager->CreateNtupleDColumn("PositionX"); //id = 1
		analysisManager->CreateNtupleDColumn("PositionY"); //id = 2
		analysisManager->CreateNtupleDColumn("PositionZ"); //id = 3
		analysisManager->CreateNtupleDColumn("Energy1"); //id = 4
		//analysisManager->CreateNtupleDColumn("counts_max"); 
		analysisManager->FinishNtuple();

	}

	RunAction::~RunAction() {
	}

	void RunAction::BeginOfRunAction(const G4Run* aRun) {
		auto analysisManager = G4AnalysisManager::Instance();

		analysisManager->OpenFile();
	}

	void RunAction::EndOfRunAction(const G4Run* aRun) {

		auto analysisManager = G4AnalysisManager::Instance();

		// write to output file
		analysisManager->Write();
		analysisManager->CloseFile();

	}

}