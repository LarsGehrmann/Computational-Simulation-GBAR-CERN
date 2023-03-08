#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4GenericMessenger.hh"

extern G4double distTargetOrigin;
extern G4double avgE;

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
	public:
		MyPrimaryGenerator();
		~MyPrimaryGenerator();

		virtual void GeneratePrimaries(G4Event*);

	private:
		G4ParticleGun *fParticleGun;
		G4GenericMessenger* fMessenger;

};
#endif