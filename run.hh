#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4LogicalVolume.hh"
#include "G4GenericMessenger.hh"

extern G4double distTarMod;
extern G4double dModerator;
extern G4double sigmaPos;
extern G4double avgE;

extern G4double eDepMod;
extern G4double eDepModGamma;
extern G4double eDepModElectron;
extern G4double eDepModPositron;

extern G4int noAnnihilationTar;
extern G4int noPairProductionTar;

extern G4int noAnnihilationMod;
extern G4int noPairProductionMod;

extern G4int noAnnihilationModEnd;
extern G4int noPairProductionModEnd;

extern G4double scaleB;
extern G4double distTargetOrigin;

class MyRunAction : public G4UserRunAction
{
public:
	MyRunAction();
	~MyRunAction();
	G4AnalysisManager* man;
	virtual void BeginOfRunAction(const G4Run* run);
	virtual void EndOfRunAction(const G4Run*);

private:
	G4GenericMessenger* fMessenger;
	G4String outputNameValues;
	G4String outputNameParameters;
	G4String outputNameHisto;
	G4String outputNameSample;
};

#endif
