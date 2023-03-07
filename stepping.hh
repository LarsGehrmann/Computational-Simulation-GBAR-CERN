#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "event.hh"
#include "G4Step.hh"
#include "G4SteppingManager.hh"
#include "G4VPhysicalVolume.hh"

#include "G4AnalysisManager.hh"

#include "construction.hh"

#include "G4GenericMessenger.hh"


extern G4int noAnnihilationTar;
extern G4int noPairProductionTar;
extern G4int noAnnihilationMod;
extern G4int noPairProductionMod;
extern G4int noAnnihilationModEnd;
extern G4int noPairProductionModEnd;

extern G4double eDep;

class MySteppingAction : public G4UserSteppingAction
{
public:
	MySteppingAction(MyEventAction* eventAction);
	~MySteppingAction();
	virtual void UserSteppingAction(const G4Step*);
	G4AnalysisManager* man;
private:
	G4GenericMessenger* fMessenger;
	bool saveHistograms;

	G4String volumeName;
};

#endif
