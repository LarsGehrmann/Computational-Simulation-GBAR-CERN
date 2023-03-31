#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"
#include "generator.hh"
#include "run.hh"

class MyActionInitialization : public G4VUserActionInitialization
{
	public:
		MyActionInitialization(int argRunNo, G4int argChoiceParticle, G4double argDistTargetOrigin, G4double argAvgE, G4int argChoiceGeometry,
			G4double argdModerator, G4double argDistTarMod);
		MyActionInitialization(int argRunNo, G4int argChoiceParticle, G4double argDistTargetOrigin, G4double argAvgE, G4int argChoiceGeometry, 
			G4double argdModerator, G4double argDistTarMod, G4String argFileName);
		~MyActionInitialization();

//		using G4VUserActionInitialization::Build();
		void customBuild();
		virtual void Build() const;
		//virtual void BuildForMaster() const;
private:
	int runNo;
	G4int choiceParticle;
	G4double distTargetOrigin, avgE;
	G4int choiceGeometry;
	G4double dModerator, distTarMod, scaleB;
	G4String fileName;

};

#endif
