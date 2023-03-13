#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction* eventAction)
{

	saveHistograms = false;

	fMessenger = new G4GenericMessenger(this, "/SaveData/", "Save Histograms");

	fMessenger->DeclareProperty("saveHistograms", saveHistograms, "Boolean whether histograms of kinetic energy shall be saved");


}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step* aStep) 
{
	// Histogram
	if (saveHistograms) {
		const std::vector<const G4Track*>* secondary = aStep->GetSecondaryInCurrentStep();
		if (aStep->GetPostStepPoint()->GetProcessDefinedStep()) {
			const G4String& procName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
			if (procName == "conv") {
				man = G4AnalysisManager::Instance();
				man->SetVerboseLevel(0);
				for (size_t lp = 0; lp < (*secondary).size(); lp++) {
					auto particle = (*secondary)[lp]->GetDefinition();
					G4String particleName = particle->GetParticleName();
					G4double energy = (*secondary)[lp]->GetKineticEnergy();
					G4String volumeName = (*secondary)[lp]->GetVolume()->GetName();
					if (volumeName == "physicalTarget") {
						if (particleName == "e+") {
							man->FillNtupleDColumn(2, 0, energy);
							man->FillNtupleDColumn(2, 2, -1.);
							man->FillNtupleDColumn(2, 3, -1.);
						}
						else if (particleName == "e-") {
							man->FillNtupleDColumn(2, 1, energy);
						}
						else {
							G4cout << "Particle: " << particleName << G4endl;
						}
					}
					else if (volumeName == "physicalModerator" || volumeName == "physicalModeratorEnd") {
						if (particleName == "e+") {
							man->FillNtupleDColumn(2, 2, energy);
							man->FillNtupleDColumn(2, 0, -1.);
							man->FillNtupleDColumn(2, 1, -1.);
						}
						else if (particleName == "e-") {
							man->FillNtupleDColumn(2, 3, energy);
						}
						else { // if particle neither electron nor positron
							G4cout << "Particle: " << particleName << G4endl;
						}
					}
					else {	  // if process neither in target nor in moderator
						G4cout << "Gamma-conversion in: " << volumeName << G4endl;
					}
				}
				man->AddNtupleRow(2);
			}
		}
	}

	// Pair production and annihlation processes
	if (aStep->GetPostStepPoint()->GetProcessDefinedStep()) {
		const G4String& procName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
		if (procName == "conv") {
			//G4cout << "Conversion in stepping action" << G4endl;
			volumeName = aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName();
			if (volumeName == "physicalModerator" || volumeName == "physicalModeratorEnd") {
				//G4cout << "Process: " << procName << "in: " << volumeName << G4endl;
				noPairProductionMod++;
			}
			if (volumeName == "physicalModeratorEnd") {
				//G4cout << "Process: " << procName << "in: " << volumeName << G4endl;
				noPairProductionModEnd++;
			}
			if (volumeName == "physicalTarget") {
				noPairProductionTar++;
			}
		}
		if (procName == "annihil") {
			volumeName = aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName();
			if (volumeName == "physicalModerator" || volumeName == "physicalModeratorEnd") {
				//G4cout << "Process: " << procName << "in: " << volumeName << G4endl;
				noAnnihilationMod++;
			}
			if (volumeName == "physicalModeratorEnd") {
				//G4cout << "Process: " << procName << "in: " << volumeName << G4endl;
				noAnnihilationModEnd++;
			}
			if (volumeName == "physicalTarget") {
				noAnnihilationTar++;
			}
		}
	}




}