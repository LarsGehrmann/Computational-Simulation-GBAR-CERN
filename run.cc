#include "run.hh"


#include <filesystem>
#include <iostream>
#include <string>

MyRunAction::MyRunAction(int argRunNo, G4double argdModerator, G4double argAvgE, G4double argDistTargetOrigin, G4double argDistTarMod)
{
	runNo = argRunNo;
	dModerator = argdModerator;
	avgE = argAvgE;
	distTargetOrigin = argDistTargetOrigin;
	distTarMod = argDistTarMod;

	std::stringstream strRunID;
	strRunID << runNo;

	G4cout << "Run ID: " << runNo << G4endl;
	man = G4AnalysisManager::Instance();
	man->SetVerboseLevel(3);

	G4String fileName, tupleName;

	if (runNo == 0) {
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
}
MyRunAction::MyRunAction(int argRunNo, G4double argdModerator, G4double argAvgE, G4double argDistTargetOrigin, G4double argDistTarMod, G4String argFileName)
{
	runNo = argRunNo;
	dModerator = argdModerator;
	avgE = argAvgE;
	distTargetOrigin = argDistTargetOrigin;
	distTarMod = argDistTarMod;


	std::stringstream strRunID;
	strRunID << runNo;

	G4cout << "Run ID: " << runNo << G4endl;
	man = G4AnalysisManager::Instance();
	man->SetVerboseLevel(3);

	G4String fileName, tupleName;

	fileName = argFileName + strRunID.str() + ".csv";
	man->OpenFile(fileName);
	//G4String fileNameHisto = outputNameHisto + strRunID.str() + ".csv";
	//man->OpenFile(fileNameHisto);

	//G4String fileNameSample = outputNameSample + strRunID.str() + ".csv";
	//man->OpenFile(fileNameSample);

	//G4String fileNameAnnihis = outputNameAnnihis + strRunID.str() + ".csv";
	//man->OpenFile(fileNameAnnihis);
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
	man->SetVerboseLevel(3);

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