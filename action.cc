#include "action.hh"
#include "event.hh"
#include "stepping.hh"


MyActionInitialization::MyActionInitialization(int argRunNo, G4int argChoiceParticle, G4double argDistTargetOrigin, G4double argAvgE,
	G4int argChoiceGeometry, G4double argdModerator, G4double argDistTarMod)
{

	runNo = argRunNo;
	choiceParticle = argChoiceParticle;
	distTargetOrigin = argDistTargetOrigin;
	avgE = argAvgE;
	choiceGeometry = argChoiceGeometry;
	dModerator = argdModerator;
	distTarMod = argDistTarMod;
	fileName = "DefaultFileName";
}

MyActionInitialization::MyActionInitialization(int argRunNo, G4int argChoiceParticle, G4double argDistTargetOrigin, G4double argAvgE, 
	G4int argChoiceGeometry, G4double argdModerator, G4double argDistTarMod, G4String argFileName)
{

	runNo = argRunNo;
	choiceParticle = argChoiceParticle;
	distTargetOrigin = argDistTargetOrigin;
	avgE = argAvgE;
	choiceGeometry = argChoiceGeometry;
	dModerator = argdModerator;
	distTarMod = argDistTarMod;
	fileName = argFileName;
}

MyActionInitialization::~MyActionInitialization()
{
}



void MyActionInitialization::Build()const{

	// determine here which particles to genereate to avoid switch-statement in generate primaries
	FastElectron* fastElectron = new FastElectron(distTargetOrigin, avgE);
	FastPositronSample* fastPositronSample = new FastPositronSample(distTargetOrigin);
	FastElectronCOMSOL* fastElectronCOMSOL = new FastElectronCOMSOL();
	FastPositronCOMSOL* fastPositronCOMSOL = new FastPositronCOMSOL();
	SlowPositronCOMSOL* slowPositronCOMSOL = new SlowPositronCOMSOL();

	switch (choiceParticle) {
	case 0:
		SetUserAction(fastElectron);
		break;
	case 1:
		SetUserAction(fastPositronSample);
		break;
	case 2:
		SetUserAction(fastElectronCOMSOL);
		break;
	case 3:
		SetUserAction(fastPositronCOMSOL);
		break;
	case 4:
		SetUserAction(slowPositronCOMSOL);
		break;
	}

	MyRunAction* runAction = new MyRunAction(runNo, dModerator, avgE, distTargetOrigin, distTarMod, fileName);
	SetUserAction(runAction);

	MyEventAction* eventAction = new MyEventAction(runAction);
	SetUserAction(eventAction);

	MySteppingAction* steppingAction = new MySteppingAction(eventAction, choiceGeometry);
	SetUserAction(steppingAction);
}