#include "../include/PrimaryGeneratorAction.hh"
#include "Randomize.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include <random>
#include "G4RandomDirection.hh"


//---------------------some detector parameters--------------------- 

namespace TASK2
{

	PrimaryGeneratorAction::PrimaryGeneratorAction() { //executes once
	
	//---------------------particle parameters---------------------
		G4int nParticles = 1; //particles ammount
		fParticleGun = new G4ParticleGun(nParticles);

		const G4String& particleName = "gamma"; //particle
		//G4double energy = 1461. * keV; //particle energy

		G4double posZ = - (5 * cm); 
		G4ThreeVector position = G4ThreeVector(0, 0, posZ); //particle gun position

		G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
		G4ParticleDefinition* particle  = particleTable->FindParticle(particleName);
		fParticleGun->SetParticleDefinition(particle);
		//fParticleGun->SetParticleEnergy(energy);
		fParticleGun->SetParticlePosition(position);
		
	}

	PrimaryGeneratorAction::~PrimaryGeneratorAction() {
		delete fParticleGun;
	}
     
	void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event){ //this function is called at the begining of each event

		
		G4ThreeVector momentumDirection = G4ThreeVector(0, 0, 1);

		G4double energy1 = 661 * keV, energy2 = 1461 * keV; //particle energy

		if ((double)G4UniformRand() > .5){
			fParticleGun->SetParticleEnergy(energy1);
			fSource = true;
		}
		else{
			fParticleGun->SetParticleEnergy(energy2);
			fSource = false; 
		}
		//fParticleGun -> SetParticlePosition(sourcePosition);
		fParticleGun->SetParticleMomentumDirection(momentumDirection); 
		fParticleGun->GeneratePrimaryVertex(event); 
	} 
}