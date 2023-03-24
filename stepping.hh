#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "event.hh"
#include "G4Step.hh"
#include "G4SteppingManager.hh"
#include "G4VPhysicalVolume.hh"

#include "G4AnalysisManager.hh"

#include "construction.hh"
#include "G4RunManager.hh"

#include "G4GenericMessenger.hh"

/*
extern G4int argNoAnnihilationTar;
extern G4int argNoPairProductionTar;
extern G4int argNoAnnihilationMod;
extern G4int argNoPairProductionMod;
extern G4int argNoAnnihilationModEnd;
extern G4int argNoPairProductionModEnd;
*/



class MySteppingAction : public G4UserSteppingAction
{
public:
	MySteppingAction(MyEventAction* eventAction, G4int argChoiceGeometry);

	~MySteppingAction();
	virtual void UserSteppingAction(const G4Step*);
	G4AnalysisManager* man;
private:
	G4int choiceGeometry;
	G4GenericMessenger* fMessenger;
	/*
	G4double* eDepModTotal; G4double* eDepModGammaTotal; G4double* eDepModElectronTotal; G4double* eDepModPositronTotal; G4int* noAnnihilationTar;
	G4int* noPairProductionTar; G4int* noAnnihilationMod; G4int* noPairProductionMod; G4int* noAnnihilationModEnd; G4int* noPairProductionModEnd;
	double** annihiMod; double** eDepModGamma; double** eDepModElectron; double** eDepModPositron;
	*/
	bool saveHistograms;

	G4String volumeName;
	G4int noSampleWalls = 5;
	G4int * lastEventID;		// for every wall store separate lastEventID
};

#endif
