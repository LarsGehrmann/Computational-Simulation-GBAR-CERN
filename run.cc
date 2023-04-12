#include "run.hh"


#include <filesystem>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

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


	fileName = "SampleWalls" + strRunID.str() + ".csv";
	man->OpenFile(fileName);
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

	fileName = argFileName;
	man->OpenFile(fileName);

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