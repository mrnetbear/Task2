#ifndef TASK2_RUN_ACTION_HH
#define TASK2_RUN_ACTION_HH 1

#include "G4UserRunAction.hh"

#include "G4AnalysisManager.hh"


namespace TASK2 {

	class HitsCollection;

	class RunAction : public G4UserRunAction {
	public:
		RunAction();
		~RunAction();

		void BeginOfRunAction(const G4Run* aRun) override;
		void EndOfRunAction(const G4Run* aRun) override;

	private:

	};


}

#endif // TASK2_RUN_ACTION_HH
