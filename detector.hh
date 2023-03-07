#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VSensitiveDetector.hh"
#include "G4ParticleDefinition.hh"
#include "G4DynamicParticle.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4GenericMessenger.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"

extern G4double eDepMod;
extern G4double eDepModGamma;
extern G4double eDepModElectron;
extern G4double eDepModPositron;
extern G4int noAnnihilationMod;
extern G4int noPairProductionMod;

class MySensitiveDetector : public G4VSensitiveDetector
{
public:
		MySensitiveDetector(G4String);
		~MySensitiveDetector();

		G4int getPositronCount();
		G4double getDepositedEnergy();

private:
	virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
	G4int lastEPlusEvNo;

	G4GenericMessenger* fMessenger;

	

	const G4DynamicParticle* dynamicParticle;
	G4ParticleDefinition* particle;



};

#endif
