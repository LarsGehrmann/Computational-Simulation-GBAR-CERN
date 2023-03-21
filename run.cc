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

	outputNameValues = "OutputValues";
	outputNameParameters = "OutputParameters";
	outputNameHisto = "OutputHistogram";
	outputNameSample = "OutputSample";
	outputNameAnnihis = "OutputAnnihis";
	fMessenger = new G4GenericMessenger(this, "/output/", "Name of output file");

	fMessenger->DeclareProperty("outputNameValues", outputNameValues, "Name of the output of the file with values");
	fMessenger->DeclareProperty("outputNameParameters", outputNameParameters, "Name of the output of the file with paramters");
	fMessenger->DeclareProperty("outputNameHisto", outputNameHisto, "Name of the histogram file");


	G4AnalysisManager* man = G4AnalysisManager::Instance();
	man->SetVerboseLevel(0);

	// Values
	man->CreateNtuple("Title1", "Title2");
	man->CreateNtupleDColumn("depositedEnergyModerator");
	man->CreateNtupleDColumn("depositedEnergyGamma");
	man->CreateNtupleDColumn("depositedEnergyElectron");
	man->CreateNtupleDColumn("depositedEnergyPositron");
	man->CreateNtupleDColumn("noAnnihilationTar");
	man->CreateNtupleDColumn("noPairProductionTar");
	man->CreateNtupleDColumn("noAnnihilationMod");
	man->CreateNtupleDColumn("noPairProductionMod");
	man->CreateNtupleDColumn("noAnnihilationModEnd");
	man->CreateNtupleDColumn("noPairProductionModEnd");
	man->FinishNtuple(0);

	// Parameters
	man->CreateNtuple("Title3", "Title4");
	man->CreateNtupleDColumn("distTarMod ");
	man->CreateNtupleDColumn("dModerator");
	man->CreateNtupleDColumn("empty");
	man->CreateNtupleDColumn("avgEnergy");
	man->CreateNtupleDColumn("scaling of B-field");
	man->CreateNtupleDColumn("distTargetOrigin (real geometry)");

	man->FinishNtuple(1);

	// Histogram
	man->CreateNtuple("Title5", "Title6");
	man->CreateNtupleDColumn("Te+Tar");
	man->CreateNtupleDColumn("Te-Tar");
	man->CreateNtupleDColumn("Te+Mod");
	man->CreateNtupleDColumn("Te-Mod");
	man->FinishNtuple(2);

	// Sample positrons
	man->CreateNtuple("Title7", "Title8");
	man->CreateNtupleDColumn("x");
	man->CreateNtupleDColumn("y");
	man->CreateNtupleDColumn("z");
	man->CreateNtupleDColumn("px");
	man->CreateNtupleDColumn("py");
	man->CreateNtupleDColumn("pz");
	man->CreateNtupleDColumn("E");
	man->FinishNtuple(3);

	// Annihis
	man->CreateNtuple("Title9", "Title10");
	man->CreateNtupleDColumn("Number of volume in which annihilation happened");
	man->FinishNtuple(4);


}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run) 
{

	man = G4AnalysisManager::Instance();
	man->SetVerboseLevel(0);

	G4int runID = run->GetRunID();
	std::stringstream strRunID;
	strRunID << runID;


	//G4String fileNameHisto = outputNameHisto + strRunID.str() + ".csv";
	//man->OpenFile(fileNameHisto);

	//G4String fileNameSample = outputNameSample + strRunID.str() + ".csv";
	//man->OpenFile(fileNameSample);

	G4String fileNameAnnihis = outputNameAnnihis + strRunID.str() + ".csv";
	man->OpenFile(fileNameAnnihis);

	/*
	annihiMod = new double* [20];
	eDepModGamma = new double* [20];
	eDepModElectron = new double* [20];
	eDepModPositron = new double* [20];

	for (int i = 0; i < 20; ++i) {
		annihiMod[i] = new double[20];
		eDepModGamma[i] = new double[20];
		eDepModElectron[i] = new double[20];
		eDepModoPositron[i] = new double[20];

	}
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			annihiMod[i][j] = 0;
			eDepModGamma[i][j] = 0;
			eDepModElectron[i][j] = 0;
			eDepModPositron[i][j] = 0;
		}
	}
	
	eDepMod = 0;
	eDepModGamma = 0;
	eDepModElectron = 0;
	eDepModPositron = 0;
	noAnnihilationTar = 0;
	noPairProductionTar = 0;
	noAnnihilationMod = 0;
	noPairProductionMod = 0;
	noAnnihilationModEnd = 0;
	noPairProductionModEnd = 0;
	*/

}


void MyRunAction::EndOfRunAction(const G4Run* run) 
{
	man = G4AnalysisManager::Instance();
	man->SetVerboseLevel(0);

	man->Write();
	man->CloseFile();


	G4int runID = run->GetRunID();
	std::stringstream strRunID;
	strRunID << runID;


	G4String fileNameValues = outputNameValues + strRunID.str() + ".csv";
	man->OpenFile(fileNameValues);
	/*
	man->FillNtupleDColumn(0, 0, eDepMod);
	man->FillNtupleDColumn(0, 1, eDepModGamma);
	man->FillNtupleDColumn(0, 2, eDepModElectron);
	man->FillNtupleDColumn(0, 3, eDepModPositron);
	man->FillNtupleDColumn(0, 4, noAnnihilationTar);
	man->FillNtupleDColumn(0, 5, noPairProductionTar);
	man->FillNtupleDColumn(0, 6, noAnnihilationMod);
	man->FillNtupleDColumn(0, 7, noPairProductionMod);
	man->FillNtupleDColumn(0, 8, noAnnihilationModEnd);
	man->FillNtupleDColumn(0, 9, noPairProductionModEnd);
	man->AddNtupleRow(0);
	man->Write();
	*/
	man->CloseFile();

	G4String fileNameParameters = outputNameParameters + strRunID.str() + ".csv";
	man->OpenFile(fileNameParameters);
	
	man->FillNtupleDColumn(1, 0, distTarMod);
	man->FillNtupleDColumn(1, 1, dModerator);
	man->FillNtupleDColumn(1, 2, 0.);
	man->FillNtupleDColumn(1, 3, avgE);
	man->FillNtupleDColumn(1, 4, scaleB);
	man->FillNtupleDColumn(1, 5, distTargetOrigin);
	
	man->AddNtupleRow(1);
	man->Write();
	man->CloseFile();

	G4cout << "------------------------------------------------------------------------" << G4endl;
	/*
	//G4cout << "Total e+ production : " << noPairProductionStep << G4endl;
	//G4cout << "e+ production in moderator: " << noPairProductionMod << G4endl;
	G4cout << "Target: " << G4endl;
	G4cout << "Number of pair-prod: " << noPairProductionTar << ", number of annihilations: " << noAnnihilationTar << G4endl;
	G4cout << "----------------" << G4endl;

	G4cout << "Moderator: " << G4endl;
	G4cout << "Number of pair-prod: " << noPairProductionMod << ", number of annihilations: " << noAnnihilationMod << G4endl;
	G4cout << "----------------" << G4endl;


	G4cout << "Moderator end: " << G4endl;
	G4cout << "Number of pair-prod: " << noPairProductionModEnd << ", number of annihilations: " << noAnnihilationModEnd << G4endl;
	G4cout << "----------------" << G4endl;
	G4cout << "Total energy deposited in moderator: " << eDepMod << "MeV" << G4endl;
	G4cout << "Energy deposited by gammas: " << eDepModGamma << "MeV" << G4endl;
	G4cout << "Energy deposited by electrons: " << eDepModElectron << "MeV" << G4endl;
	G4cout << "Energy deposited by positrons: " << eDepModPositron << "MeV" << G4endl;
	G4cout << "--------------------------------------------------------------------------------" << G4endl;
	G4cout << "--------------------------------------------------------------------------------" << G4endl;
	*/

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