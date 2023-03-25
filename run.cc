#include "run.hh"


#include <filesystem>
#include <iostream>
#include <string>

MyRunAction::MyRunAction(G4double argdModerator, G4double argAvgE, G4double argDistTargetOrigin, G4double argDistTarMod, G4double argScaleB)
{
	dModerator = argdModerator;
	avgE = argAvgE;
	distTargetOrigin = argDistTargetOrigin;
	distTarMod = argDistTarMod;
	scaleB = argScaleB;

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
{}

void MyRunAction::BeginOfRunAction(const G4Run* run) 
{
	G4cout << "BEGIN OF RUN ACTION `!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << G4endl;
	G4String fileName, tupleName;

	std::stringstream strRunID;
	strRunID << run->GetRunID();;
	G4cout << "before!" << G4endl;

	G4AnalysisManager* man = G4AnalysisManager::Instance();
	man->SetVerboseLevel(3);
	
	G4cout << "after!" << G4endl;

	// Dead
	fileName = "Dead0" + strRunID.str() + ".csv";
	tupleName = "Dead0" + strRunID.str();
	G4cout << "after!" << G4endl;

	man->CreateNtuple("test", "test");
	man->CreateNtupleDColumn(0, "dead0");
	man->FinishNtuple(0);
	
	G4cout << "after!" << G4endl;

	// Dead
	fileName = "Dead" + strRunID.str() + ".csv";
	tupleName = "Dead" + strRunID.str();
	man->CreateNtuple(tupleName, tupleName);
	man->CreateNtupleDColumn(1, "dead");
	man->FinishNtuple(1);
	G4cout << "after!" << G4endl;


	// Histogram
	fileName = "Histogram" + strRunID.str() + ".csv";
	tupleName = "Histogram" + strRunID.str();
	man->CreateNtuple(tupleName, tupleName);
	man->CreateNtupleDColumn(2,"Te+Tar");
	man->CreateNtupleDColumn(2, "Te-Tar");
	man->CreateNtupleDColumn(2, "Te+Mod");
	man->CreateNtupleDColumn(2, "Te-Mod");
	man->FinishNtuple(2);
	G4cout << "after!" << G4endl;



	// Sample positrons
	fileName = "Sample Positrons" + strRunID.str() + ".csv";
	tupleName = "Sample Positrons" + strRunID.str();
	man->CreateNtuple(tupleName, tupleName);
	man->CreateNtupleDColumn(3,"x");
	man->CreateNtupleDColumn(3, "y");
	man->CreateNtupleDColumn(3, "z");
	man->CreateNtupleDColumn(3, "px");
	man->CreateNtupleDColumn(3, "py");
	man->CreateNtupleDColumn(3, "pz");
	man->CreateNtupleDColumn(3, "E");
	man->FinishNtuple(3);

	// Annihis
	fileName = "Annihis" + strRunID.str() + ".csv";
	tupleName = "Annihis" + strRunID.str();
	man->CreateNtuple(tupleName, tupleName);
	man->CreateNtupleDColumn(4, "Number of volume in which annihilation happened");
	man->FinishNtuple(4);


	// Sample walls
	fileName = "SampleWalls" + strRunID.str() + ".csv";
	tupleName = "SampleWalls" + strRunID.str();
	man->CreateNtuple(tupleName, tupleName);
	man->CreateNtupleDColumn(5,"Wall number");
	man->CreateNtupleDColumn(5, "x");
	man->CreateNtupleDColumn(5, "y");
	man->CreateNtupleDColumn(5, "z");
	man->FinishNtuple(5);
	G4cout << "after!" << G4endl;

	man->OpenFile(fileName);
	G4cout << "End of begin of run action" << G4endl;

	//G4String fileNameHisto = outputNameHisto + strRunID.str() + ".csv";
	//man->OpenFile(fileNameHisto);

	//G4String fileNameSample = outputNameSample + strRunID.str() + ".csv";
	//man->OpenFile(fileNameSample);

	//G4String fileNameAnnihis = outputNameAnnihis + strRunID.str() + ".csv";
	//man->OpenFile(fileNameAnnihis);
	G4cout << "after!" << G4endl;

}


void MyRunAction::EndOfRunAction(const G4Run* run) 
{
	G4cout << "In end of Run action" << G4endl;
	G4AnalysisManager* man = G4AnalysisManager::Instance();
	man->SetVerboseLevel(3);

	man->Write();
	man->CloseFile();

	G4int runID = run->GetRunID();
	G4cout << "Finished run number: " << runID << G4endl;
	delete man;
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