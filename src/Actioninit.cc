
#include "../include/ActionInit.hh"
#include "../include/PrimaryGeneratorAction.hh"
#include "../include/SteppingAction.hh"
#include "../include/EventAction.hh"
#include "../include/RunAction.hh"
#include <random>
#include "Randomize.hh"



namespace TASK2 {

	void ActionInit::Build() const {
		

		// Multithreaded

		// set the Geant4 actions
		SetUserAction(new PrimaryGeneratorAction());


		RunAction* runAction = new RunAction(); //��� ��� �������� 

		SetUserAction(new RunAction());

		EventAction* eventAction = new EventAction();
		SetUserAction(eventAction);

		SetUserAction(new SteppingAction(eventAction));

	};

	void ActionInit::BuildForMaster() const {
		// Sequential
		RunAction* runAction = new RunAction; //��� ��� �������� 
		SetUserAction(new RunAction());

	}

}