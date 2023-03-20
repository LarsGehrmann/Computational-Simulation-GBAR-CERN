#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
//	fMessenger = new G4GenericMessenger(this, "/posCounter/", "Sensitive detector construction");
//	fMessenger->GetCurrentValue()
}

MySensitiveDetector::~MySensitiveDetector()
{}
/*
G4int MySensitiveDetector::getPositronCount()
{ 
	return positronCount;
}

G4double MySensitiveDetector::getDepositedEnergy()
{
	return depositedEnergy;
}
*/
G4bool MySensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{
	/*
	eDepMod += aStep->GetTotalEnergyDeposit();



	if (aStep->GetPostStepPoint()->GetProcessDefinedStep()) {
		const G4String& particleName = aStep->GetTrack()->GetDefinition()->GetParticleName();
		if (particleName == "gamma") {
			eDepModGamma += aStep->GetTotalEnergyDeposit();
		}
		else if (particleName == "e-") {
			eDepModElectron += aStep->GetTotalEnergyDeposit();
		}
		else if (particleName == "e+") {
			eDepModPositron += aStep->GetTotalEnergyDeposit();
		}
		else {
			G4cout << "Energy deposited by particle: " << particleName << G4endl;
		}
	}
	else {
		G4cout << "Pointer can not be dereferenced!" << G4endl;
	}
	*/


	/*
	if (aStep->GetPostStepPoint()->GetProcessDefinedStep()) {
		const G4String& procName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
		if (procName == "annihil") {
			noAnnihilationMod++;
		}
		if (procName == "conv") {
			noPairProductionMod++;
		}
	}
	*/



	/*
	//G4int evtNo = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	if (aStep->GetPostStepPoint()->GetProcessDefinedStep()) {
		const G4String& procName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
		if (procName == "conv") {
			noPairProductionSensDet++;
		}
		if (procName == "annihil") {
			noAnnihilationsSensDet++;
		}
	}
	*/
	/*


	if (aStep->GetPreStepPoint()->GetProcessDefinedStep()) {
		const G4String& particleName = aStep->GetTrack()->GetDefinition()->GetParticleName();
		if (particleName == "gamma") {
			if (aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName()) {
				const G4String& procName = aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName();
				if (procName != "compt" && procName != "Rayl") {
					if (procName != "CoupledTransportation") {
						G4cout << procName << G4endl;
					}
				}


			}
			//	G4cout << aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName() << G4endl;
		}
	}


	

	/*
	if (aStep->GetPreStepPoint()->GetProcessDefinedStep()) {
		const G4String& procName = aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName();
		if (procName != "annihil") {
			G4cout << aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName() << G4endl;
			noAnnihilations++;
			//G4cout << ""
		}
	}
	*/
	/*
	if (aStep->GetPreStepPoint()->GetProcessDefinedStep()) {
		const G4String& procName = aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName();
		if (procName == "annihil") {
			G4cout << "Annihilation in moderator detected!" << G4endl;
			noAnnihilations++;
			//G4cout << ""
		}
	}
	*/
	/*
	if (aStep->GetPreStepPoint()->GetProcessDefinedStep()) {
		const G4String& procName = aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName();
		if (procName == "conv") {
				//G4cout << "Pair production detected!" << G4endl;
				G4cout << aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName() << G4endl;
				noPairProduction++;
		}
	}
	if (aStep->GetPreStepPoint()->GetProcessDefinedStep()) {
		const G4String& procName = aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName();
		if (procName == "eIoni") {
			//G4cout << "Pair production detected!" << G4endl;
			G4cout << aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName() << G4endl;
			noPairProduction++;
		}
	}
	*/
	//G4cout << "ProcName: " << aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName() << G4endl;
	//	G4cout << "BREMSSTRAHLUNG DETECTED!!!!" << G4endl;

	/*
	
	G4AnalysisManager* man = G4AnalysisManager::Instance();
	man->SetVerboseLevel(3);

	man->FillNtupleIColumn(0, 0, evtNo);
	man->FillNtupleIColumn(0, 1, positronCount);
	man->FillNtupleDColumn(0, 2, depositedEnergy);
	man->AddNtupleRow(0);
	//G4cout << "HERE" << G4endl;
	*/

	/*

	man = G4AnalysisManager::Instance();
	man->OpenFile("output.root");

	man->CreateNtuple("Hits", "Hits");



	man->CreateNtupleIColumn("positronNumber");

	man->CreateNtupleDColumn("depositedEnergy");
	man->FinishNtuple(0);
	*/

	//G4cout << "Positron in moderator! Number so far: " << positronCount << G4endl;
	//G4cout << "Accumulated deposited energy: " << depositedEnergy << G4endl;
	return true;
}