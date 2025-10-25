
#include "../include/EventAction.hh"
#include "../include/PrimaryGeneratorAction.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"

namespace TASK2 {

	G4int fParticleCount;
	//G4int counts = 0;
	EventAction::EventAction() {
		fEnergy = 0.;
	//	fParticleCount = 0;
	}

	void EventAction::BeginOfEventAction(const G4Event* anEvent) {
		// begin of event actions here
		fEnergy = 0.;
	//	fParticleCount = 0;
	}
	
	// setting energy and position
	void EventAction::AddEnergy(G4double e) { fEnergy += e; }
	
	void EventAction::SetPosition(G4ThreeVector p) { fPosition = p; }

	void EventAction::SetSource(G4bool src) { fSource = src; }

	void EventAction::EndOfEventAction(const G4Event* anEvent) {
		// if there was any energy deposited, tell the analysis manager.

		unsigned int particleCounter = 0;
		auto analysisManager = G4AnalysisManager::Instance();
	
		// add all the info to the analysis nTuples
		// set the column id's (see runaction)
		G4int energyColumnId = 0;
		G4int posXColumnId = 1;
		G4int posYColumnId = 2;
		G4int posZColumnId = 3;
		G4int energyColumnId1 = 4;

		const auto primaryGenerator = static_cast<const PrimaryGeneratorAction*>(
			G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction()
		);
			
		fSource = primaryGenerator->GetParticleSource();

		if (fSource) analysisManager->FillNtupleDColumn(energyColumnId, fEnergy);
		else analysisManager->FillNtupleDColumn(energyColumnId1, fEnergy);
		analysisManager->FillNtupleDColumn(posXColumnId, fPosition.getX());
		analysisManager->FillNtupleDColumn(posYColumnId, fPosition.getY());
		analysisManager->FillNtupleDColumn(posZColumnId, fPosition.getZ());

		// finally, go to the next ntuple row
		analysisManager->AddNtupleRow();
		//G4cout << "Number of particles in this event: " << fParticleCount << G4endl;
		//fParticleCount++;
	}
}