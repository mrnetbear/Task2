#ifndef TASK2_STEPPING_ACTION_HH
#define TASK2_STEPPING_ACTION_HH 1

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"
#include "EventAction.hh"


namespace TASK2 {


	class SteppingAction : public G4UserSteppingAction {
	public:
		SteppingAction(EventAction* eventAction = nullptr);
		~SteppingAction();

		void UserSteppingAction(const G4Step*) override;

	private:
		G4LogicalVolume* fGammaDetector = nullptr;
		G4LogicalVolume* fWorld = nullptr;

		EventAction* feventAction = nullptr;

	};

}


#endif // TASK2_STEPPING_ACTION_HH
