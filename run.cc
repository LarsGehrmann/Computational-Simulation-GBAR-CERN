#include "run.hh"


#include <filesystem>
#include <iostream>
#include <string>

MyRunAction::MyRunAction(int argRunNo, G4double argdModerator, G4double argAvgE, G4double argDistTargetOrigin, G4double argDistTarMod, G4double argScaleB)
{
	runNo = argRunNo;
	dModerator = argdModerator;
	avgE = argAvgE;
	distTargetOrigin = argDistTargetOrigin;
	distTarMod = argDistTarMod;
	scaleB = argScaleB;


	std::stringstream strRunID;
	strRunID << runNo;

	G4cout << "Run ID: " << runNo << G4endl;
	man = G4AnalysisManager::Instance();
	man->SetVerboseLevel(0);

	G4String fileName, tupleName;

	if (runNo == 0) {
		// dead0
		/*
		tupleName = "0th" + strRunID.str();
		man->CreateNtuple("test", "test");
		man->CreateNtupleDColumn(0, "dead0");
		man->FinishNtuple(0);
		*/
		// dead1
		tupleName = "1st";
		man->CreateNtuple(tupleName, tupleName);
		man->CreateNtupleDColumn(1, "dead");
		man->FinishNtuple(1);
		// histo 
		tupleName = "Histogram" + strRunID.str();
		man->CreateNtuple(tupleName, tupleName);
		man->CreateNtupleDColumn(2, "Te+Tar");
		man->CreateNtupleDColumn(2, "Te-Tar");
		man->CreateNtupleDColumn(2, "Te+Mod");
		man->CreateNtupleDColumn(2, "Te-Mod");
		man->FinishNtuple(2);
		// Sample positrons
		tupleName = "Sample Positrons";
		man->CreateNtuple(tupleName, tupleName);
		man->CreateNtupleDColumn(3, "x");
		man->CreateNtupleDColumn(3, "y");
		man->CreateNtupleDColumn(3, "z");
		man->CreateNtupleDColumn(3, "px");
		man->CreateNtupleDColumn(3, "py");
		man->CreateNtupleDColumn(3, "pz");
		man->CreateNtupleDColumn(3, "E");
		man->FinishNtuple(3);
		// Annihis
		tupleName = "Annihis";
		man->CreateNtuple(tupleName, tupleName);
		man->CreateNtupleDColumn(4, "Number of volume in which annihilation happened");
		man->FinishNtuple(4);
		// Sample walls
		tupleName = "SampleWalls";
		man->CreateNtuple(tupleName, tupleName);
		man->CreateNtupleDColumn(5, "Wall number");
		man->CreateNtupleDColumn(5, "x");
		man->CreateNtupleDColumn(5, "y");
		man->CreateNtupleDColumn(5, "z");
		man->FinishNtuple(5);
	}

	fileName = "SampleWalls" + strRunID.str() + ".csv";
	man->OpenFile(fileName);
	//G4String fileNameHisto = outputNameHisto + strRunID.str() + ".csv";
	//man->OpenFile(fileNameHisto);

	//G4String fileNameSample = outputNameSample + strRunID.str() + ".csv";
	//man->OpenFile(fileNameSample);

	//G4String fileNameAnnihis = outputNameAnnihis + strRunID.str() + ".csv";
	//man->OpenFile(fileNameAnnihis);






	/*
	eDepModTotal = argEDepModTotal;
	eDepModGammaTotal = argEDepModGammaTotal;
	eDepModElectronTotal = argEDepModElectronTotal;
	eDepModPositronTotal = argEDepModPositronTotal;
	noAnnihilationTar = argNoAnnihilationTar;
	noPairProductionTar = argNoPairProductionTar;
	noAnnihilationMod = argNoAnnihilationMod;
	noPairProductionMod = argNoPairProductionMod;
	noAnnihilationModEnd = argNoAnnihilationModEnd;
	noPairProductionModEnd = argNoPairProductionModEnd;
	annihiMod = argAnnihiMod;
	eDepModGamma = argEDepModGamma;
	eDepModElectron = argEDepModElectron;
	eDepModPositron = argEDepModPositron;
	*/

	

}

MyRunAction::~MyRunAction()
{
	delete G4AnalysisManager::Instance();
}

void MyRunAction::BeginOfRunAction(const G4Run* run) 
{

}


void MyRunAction::EndOfRunAction(const G4Run* run) 
{

	G4cout << "In end of Run action" << G4endl;
	man = G4AnalysisManager::Instance();
	man->SetVerboseLevel(0);

	man->Write();
	man->CloseFile();

	G4int runID = run->GetRunID();
	G4cout << "Finished run number: " << runID << G4endl;

	//delete G4AnalysisManager::Instance();


}



/*
try {
	std::filesystem::remove(fileNameP1);
	G4cout << "File deleted !!!!!!!!!!!!!!!!" << G4endl;
}
catch (const std::filesystem::filesystem_error& err) {
	G4cout << "File NOT deleted !!!!!!!!!!!!!1" << G4endl;
}
*/