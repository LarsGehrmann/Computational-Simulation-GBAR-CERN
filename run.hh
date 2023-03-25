#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4LogicalVolume.hh"
#include "G4GenericMessenger.hh"


class MyRunAction : public G4UserRunAction
{
public:
	MyRunAction(G4double argdModerator, G4double argAvgE, G4double argDistTargetOrigin, G4double distTarMod, G4double argScaleB);
	~MyRunAction();
	//G4AnalysisManager* man;
	virtual void BeginOfRunAction(const G4Run* run);
	virtual void EndOfRunAction(const G4Run*);

private:
	//G4double eDepMod, eDepModGamma, eDepModElectron, eDepModPositron;
	//G4int noAnnihilationTar, noPairProductionTar, noAnnihilationMod, noPairProductionMod, noAnnihilationModEnd, noPairProductionModEnd;
	G4double dModerator, avgE, distTargetOrigin, distTarMod, scaleB;


	G4double* eDepModTotal; G4double* eDepModGammaTotal;  G4double* eDepModElectronTotal; G4double* eDepModPositronTotal; G4int* noAnnihilationTar;
	G4int* noPairProductionTar; G4int* noAnnihilationMod; G4int* noPairProductionMod; G4int* noAnnihilationModEnd; G4int* noPairProductionModEnd;
	double** annihiMod; double** eDepModGamma; double** eDepModElectron; double** eDepModPositron;

	G4GenericMessenger* fMessenger;
	G4String outputNameValues;
	G4String outputNameParameters;
	G4String outputNameHisto;
	G4String outputNameSample;
	G4String outputNameAnnihis;
	G4String outputNameSampleWalls;
};

#endif

