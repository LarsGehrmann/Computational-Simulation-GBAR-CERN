#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4GenericMessenger.hh"
#include <fstream>
#include <iostream>
#include <random>
#include <string>

extern G4double distTargetOrigin;
extern G4double avgE;
//extern G4int choiceParticle;


class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
	public:
		MyPrimaryGenerator(G4int argChoiceParticle, G4double argDistTargetOrigin, G4double argAvgE);
		~MyPrimaryGenerator();

		virtual void GeneratePrimaries(G4Event*);

	private:
		G4int choiceParticle = -1;
		G4double distTargetOrigin;
		G4double avgE;

		G4ParticleGun *fParticleGun;
		G4GenericMessenger* fMessenger;
		int posCounter;
		int posNumber = 24380;
		double **posTable;  // x y z, px, py, pz, E

};
#endif