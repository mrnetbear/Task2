#ifndef TASK2_ACTION_INIT_HH
#define TASK2_ACTION_INIT_HH 1

#include "G4VUserActionInitialization.hh"

namespace TASK2 {
	class ActionInit : public G4VUserActionInitialization {
	public:
		ActionInit() = default;
		~ActionInit() override = default;

		void Build() const override;
		void BuildForMaster() const override;
	
	};
}

#endif // TASK2_ACTION_INIT_HH
