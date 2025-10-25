#ifndef TASK2_EVENT_ACTION_HH
#define TASK2_EVENT_ACTION_HH 1

/*
Class description:

An Event represents one single particle (for now.) As the particle enters
The detector, it will continue to deposit energy until it is stopped. All
that energy will be summed up and kept track of here in the form of a "Hit."
*/

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "RunAction.hh"


namespace TASK2 {

	class EventAction : public G4UserEventAction {
	public:
		EventAction();
		~EventAction() override = default;

		void BeginOfEventAction(const G4Event* anEvent) override;
		void EndOfEventAction(const G4Event* anEvent) override;

		void AddEnergy(G4double energy);
		void SetPosition(G4ThreeVector pos);
		void SetSource(G4bool src);

	private:
		G4double fEnergy;
		G4ThreeVector fPosition;
		G4bool fSource = 1;
	};

	
}

#endif // TASK2_EVENT_ACTION_HH
