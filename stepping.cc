#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction* eventAction, G4int argChoiceGeometry)
{
	saveHistograms = false;
	fMessenger = new G4GenericMessenger(this, "/SaveData/", "Save Histograms");
	fMessenger->DeclareProperty("saveHistograms", saveHistograms, "Boolean whether histograms of kinetic energy shall be saved");
	choiceGeometry = argChoiceGeometry;

	lastEventID = new G4int[noSampleWalls];
	for (int i = 0; i < noSampleWalls; ++i) {
		lastEventID[i] = -1;
	}
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step* aStep) 
{
	/*
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
	*/






	/*
	if (aStep->GetPreStepPoint()->GetProcessDefinedStep()) {
		const G4String& procName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
		if (procName == "annihil") {
			int x = 5;
			//G4cout << "Annihi" << G4endl;
			man = G4AnalysisManager::Instance();
			man->SetVerboseLevel(0);
			man->FillNtupleDColumn(4, 0, aStep->GetPostStepPoint()->GetPhysicalVolume()->GetCopyNo());
			//man->FillNtupleDColumn(4, 0, x);
			man->AddNtupleRow(4);

		}
	}
	*/

	/*
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
	*/
	/*
	if (choiceGeometry == 2) {
		G4double x, y, z, px, py, pz, E;
		if (aStep->GetPreStepPoint()->GetProcessDefinedStep()) {
			const G4String& procName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
			const G4String& particleName = aStep->GetTrack()->GetDefinition()->GetParticleName();
			G4String volumeName = aStep->GetTrack()->GetVolume()->GetName();
			if (particleName == "e+" && volumeName == "physicalSampleWall") {

				G4AnalysisManager* man = G4AnalysisManager::Instance();
				man->SetVerboseLevel(0);
				x = aStep->GetPreStepPoint()->GetPosition().getX();
				y = aStep->GetPreStepPoint()->GetPosition().getY();
				z = aStep->GetPreStepPoint()->GetPosition().getZ();
				//G4cout << "x,y,z: " << x << ", " << y << ", " << z << G4endl;
				px = aStep->GetPreStepPoint()->GetMomentumDirection().getX();
				py = aStep->GetPreStepPoint()->GetMomentumDirection().getY();
				pz = aStep->GetPreStepPoint()->GetMomentumDirection().getZ();
				//G4cout << "px,py,pz: " << px << ", " << py << ", " << pz << G4endl;
				E = aStep->GetPreStepPoint()->GetKineticEnergy();
				//G4cout << "E: " << E << G4endl;
				man->FillNtupleDColumn(3, 0, x);
				man->FillNtupleDColumn(3, 1, y);
				man->FillNtupleDColumn(3, 2, z);
				man->FillNtupleDColumn(3, 3, px);
				man->FillNtupleDColumn(3, 4, py);
				man->FillNtupleDColumn(3, 5, pz);
				man->FillNtupleDColumn(3, 6, E);

				man->AddNtupleRow(3);
				aStep->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);

			}
		}

	}
	*/

	// if e+ annihilate in front of moderator
if (aStep->GetPreStepPoint()->GetProcessDefinedStep()) {
	const G4String& procName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
	const G4String& volumeName = aStep->GetTrack()->GetVolume()->GetName();
	if (procName == "annihil" && volumeName == "physicalModeratorFront") {
		G4AnalysisManager* man = G4AnalysisManager::Instance();
		man->SetVerboseLevel(0);
		man->FillNtupleDColumn(1, 0, aStep->GetPreStepPoint()->GetPosition().getX());
		man->FillNtupleDColumn(1, 1, aStep->GetPreStepPoint()->GetPosition().getY());
		man->FillNtupleDColumn(1, 2, aStep->GetPreStepPoint()->GetPosition().getZ());
		man->FillNtupleDColumn(1, 3, aStep->GetPreStepPoint()->GetKineticEnergy());
		man->AddNtupleRow(1);

	}
}
	// if e+ hit sampling wall
	if (aStep->GetPreStepPoint()->GetProcessDefinedStep()) {
		//const G4String& procName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
		const G4String& particleName = aStep->GetTrack()->GetDefinition()->GetParticleName();
		if (particleName == "e+") {
			G4double x, y, z, E;
			G4String volumeName = aStep->GetTrack()->GetVolume()->GetName();
			if (volumeName == "physicalSampleWall0" && lastEventID[0] != G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()) {
				lastEventID[0] = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
				const G4String& procName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
				G4AnalysisManager* man = G4AnalysisManager::Instance();
				man->SetVerboseLevel(0);
				man->FillNtupleDColumn(5, 0, 0);
				man->FillNtupleDColumn(5, 1, aStep->GetPreStepPoint()->GetPosition().getX());
				man->FillNtupleDColumn(5, 2, aStep->GetPreStepPoint()->GetPosition().getY());
				man->FillNtupleDColumn(5, 3, aStep->GetPreStepPoint()->GetPosition().getZ());
				man->FillNtupleDColumn(5, 4, aStep->GetPreStepPoint()->GetKineticEnergy());
				man->AddNtupleRow(5);
			}
			else if (volumeName == "physicalSampleWall1"  && lastEventID[1] != G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()) {
				lastEventID[1] = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
				const G4String& procName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
				G4AnalysisManager* man = G4AnalysisManager::Instance();
				man->SetVerboseLevel(0);
				man->FillNtupleDColumn(5, 0, 1.);
				man->FillNtupleDColumn(5, 1, aStep->GetPreStepPoint()->GetPosition().getX());
				man->FillNtupleDColumn(5, 2, aStep->GetPreStepPoint()->GetPosition().getY());
				man->FillNtupleDColumn(5, 3, aStep->GetPreStepPoint()->GetPosition().getZ());
				man->FillNtupleDColumn(5, 4, aStep->GetPreStepPoint()->GetKineticEnergy());
				man->AddNtupleRow(5);
			}
			else if (volumeName == "physicalSampleWall2" && lastEventID[2] != G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()) {
				lastEventID[2] = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
				const G4String& procName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
				G4AnalysisManager* man = G4AnalysisManager::Instance();
				man->SetVerboseLevel(0);
				man->FillNtupleDColumn(5, 0, 2.);
				man->FillNtupleDColumn(5, 1, aStep->GetPreStepPoint()->GetPosition().getX());
				man->FillNtupleDColumn(5, 2, aStep->GetPreStepPoint()->GetPosition().getY());
				man->FillNtupleDColumn(5, 3, aStep->GetPreStepPoint()->GetPosition().getZ());
				man->FillNtupleDColumn(5, 4, aStep->GetPreStepPoint()->GetKineticEnergy());
				man->AddNtupleRow(5);
			}
			else if (volumeName == "physicalSampleWall3" && lastEventID[3] != G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()) {
				lastEventID[3] = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
				const G4String& procName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
				G4AnalysisManager* man = G4AnalysisManager::Instance();
				man->SetVerboseLevel(0);
				man->FillNtupleDColumn(5, 0, 3.);
				man->FillNtupleDColumn(5, 1, aStep->GetPreStepPoint()->GetPosition().getX());
				man->FillNtupleDColumn(5, 2, aStep->GetPreStepPoint()->GetPosition().getY());
				man->FillNtupleDColumn(5, 3, aStep->GetPreStepPoint()->GetPosition().getZ());
				man->FillNtupleDColumn(5, 4, aStep->GetPreStepPoint()->GetKineticEnergy());
				man->AddNtupleRow(5);
			}
			else if (volumeName == "physicalSampleWall4" && lastEventID[4] != G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()) {
				lastEventID[4] = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
				const G4String& procName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
				G4AnalysisManager* man = G4AnalysisManager::Instance();
				man->SetVerboseLevel(0);
				man->FillNtupleDColumn(5, 0, 4.);
				man->FillNtupleDColumn(5, 1, aStep->GetPreStepPoint()->GetPosition().getX());
				man->FillNtupleDColumn(5, 2, aStep->GetPreStepPoint()->GetPosition().getY());
				man->FillNtupleDColumn(5, 3, aStep->GetPreStepPoint()->GetPosition().getZ());
				man->FillNtupleDColumn(5, 4, aStep->GetPreStepPoint()->GetKineticEnergy());
				man->AddNtupleRow(5);
			}
		}
	}
	
	
}