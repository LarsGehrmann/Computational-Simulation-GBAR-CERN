#include "action.hh"
#include "event.hh"
#include "stepping.hh"

MyActionInitialization::MyActionInitialization(G4int argChoiceParticle, G4double argDistTargetOrigin, G4double argAvgE, 
	G4int argChoiceGeometry, G4double argdModerator, G4double argDistTarMod, G4double argScaleB)
{
	choiceParticle = argChoiceParticle;
	distTargetOrigin = argDistTargetOrigin;
	avgE = argAvgE;
	choiceGeometry = argChoiceGeometry;
	dModerator = argdModerator;
	distTarMod = argDistTarMod;
	scaleB = argScaleB;
}

MyActionInitialization::~MyActionInitialization()
{
}



void MyActionInitialization::Build()const{
	MyPrimaryGenerator* generator = new MyPrimaryGenerator(choiceParticle, distTargetOrigin, avgE);
	SetUserAction(generator);

	MyRunAction* runAction = new MyRunAction(dModerator, avgE, distTargetOrigin, distTarMod, scaleB);
	SetUserAction(runAction);

	MyEventAction* eventAction = new MyEventAction(runAction);
	SetUserAction(eventAction);

	MySteppingAction* steppingAction = new MySteppingAction(eventAction, choiceGeometry);
	SetUserAction(steppingAction);
}

/*
void MyActionInitialization::customBuild()
{
	MyPrimaryGenerator* generator = new MyPrimaryGenerator(choiceParticle, distTargetOrigin, avgE);
	SetUserAction(generator);

	MyRunAction* runAction = new MyRunAction(dModerator, avgE, distTargetOrigin, distTarMod, scaleB, &eDepModTotal, &eDepModGammaTotal,
		&eDepModElectronTotal, &eDepModPositronTotal, &noAnnihilationTar, &noPairProductionTar,
		&noAnnihilationMod, &noPairProductionMod, &noAnnihilationModEnd, &noPairProductionModEnd,
		annihiMod, eDepModGamma, eDepModElectron, eDepModPositron);
	SetUserAction(runAction);

	MyEventAction* eventAction = new MyEventAction(runAction);
	SetUserAction(eventAction);

	MySteppingAction* steppingAction = new MySteppingAction(eventAction, choiceGeometry, &eDepModTotal, &eDepModGammaTotal,
		&eDepModElectronTotal, &eDepModPositronTotal, &noAnnihilationTar, &noPairProductionTar,
		&noAnnihilationMod, &noPairProductionMod, &noAnnihilationModEnd, &noPairProductionModEnd,
		annihiMod, eDepModGamma, eDepModElectron, eDepModPositron);
	SetUserAction(steppingAction);
}
*/


/*
, &eDepModTotal, &eDepModGammaTotal,
		&eDepModElectronTotal, &eDepModPositronTotal, &noAnnihilationTar, &noPairProductionTar,
		&noAnnihilationMod, &noPairProductionMod, &noAnnihilationModEnd, &noPairProductionModEnd,
		annihiMod, eDepModGamma, eDepModElectron, eDepModPositron
*/