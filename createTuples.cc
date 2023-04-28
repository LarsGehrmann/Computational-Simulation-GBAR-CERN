#include "createTuples.hh"


void createTuples() {

    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->SetVerboseLevel(0);



    man->CreateNtuple("Parameters", "_");
    man->CreateNtupleDColumn(0, "choiceGeometry");
    man->CreateNtupleDColumn(0, "dModerator");
    man->CreateNtupleDColumn(0, "dModeratorFront");
    man->CreateNtupleDColumn(0, "distTargetOrigin");
    man->CreateNtupleDColumn(0, "moderatorHeight");
    man->CreateNtupleDColumn(0, "scaling of Dipole B-field");
    man->CreateNtupleDColumn(0, "scaling of Neon B-field");
    man->CreateNtupleDColumn(0, "scaling of Solenoid B-field");
    man->CreateNtupleDColumn(0, "scaling of Target B-field");
    man->CreateNtupleDColumn(0, "scaling of E-field");
    man->FinishNtuple(0);


	man->CreateNtuple("modFrontAnnihis", "_");
	man->CreateNtupleDColumn(1, "x");
	man->CreateNtupleDColumn(1, "y");
	man->CreateNtupleDColumn(1, "z");
	man->CreateNtupleDColumn(1, "E");
	man->FinishNtuple(1);

	man->CreateNtuple("Histogram", "_");
	man->CreateNtupleDColumn(2, "Te+Tar");
	man->CreateNtupleDColumn(2, "Te-Tar");
	man->CreateNtupleDColumn(2, "Te+Mod");
	man->CreateNtupleDColumn(2, "Te-Mod");
	man->FinishNtuple(2);
	// Sample positrons
	man->CreateNtuple("Sample Positrons", "_");
	man->CreateNtupleDColumn(3, "x");
	man->CreateNtupleDColumn(3, "y");
	man->CreateNtupleDColumn(3, "z");
	man->CreateNtupleDColumn(3, "px");
	man->CreateNtupleDColumn(3, "py");
	man->CreateNtupleDColumn(3, "pz");
	man->CreateNtupleDColumn(3, "E");
	man->FinishNtuple(3);
	// Annihis
	man->CreateNtuple("Annihis", "_");
	man->CreateNtupleDColumn(4, "Number of volume in which annihilation happened");
	man->FinishNtuple(4);
	// Sample walls
	man->CreateNtuple("SampleWalls", "_");
	man->CreateNtupleDColumn(5, "Wall number");
	man->CreateNtupleDColumn(5, "x");
	man->CreateNtupleDColumn(5, "y");
	man->CreateNtupleDColumn(5, "z");
	man->CreateNtupleDColumn(5, "E");
	man->FinishNtuple(5);

}
