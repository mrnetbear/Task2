#ifndef TASK2_PHYSICS_LIST_HH
#define TASK2_PHYSICS_LIST_HH 1

#include "G4VModularPhysicsList.hh"

namespace TASK2
{
	class PhysicsList : public G4VModularPhysicsList
	{
	public:
		PhysicsList();
		virtual ~PhysicsList();

		// Mandatory methods to override;
		virtual void ConstructParticle() override;
		virtual void ConstructProcess() override;
	};
}

#endif // TASK2_PHYSICS_LIST_HH