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

	man = G4AnalysisManager::Instance();
	man->SetVerboseLevel(3);

	G4String fileName, tupleName;


	fileName = "defaultFileName" + strRunID.str() + ".csv";
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
	man = G4AnalysisManager::Instance();
	man->SetVerboseLevel(0);

	man->Write();
	man->CloseFile();

	G4int runID = run->GetRunID();
}
