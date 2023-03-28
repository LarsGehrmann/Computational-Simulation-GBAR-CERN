#include "runMan.hh"

/*
void RunMan::Initialize() {
	G4StateManager * stateManager = G4StateManager::GetStateManager();
	G4ApplicationState currentState = stateManager->GetCurrentState();
	if (currentState != G4State_PreInit && currentState != G4State_Idle) {
		G4cerr << "Illegal application state - " << "G4RunManager::Initialize() ignored." << G4endl;
		return;
	}
	if (!geometryInitialized) InitializeGeometry();
	if (!physicsInitialized) {
		InitializePhysics();
	}
		initializedAtLeastOnce = true;

}*/





void RunMan::Initialize()
{
	G4StateManager* stateManager = G4StateManager::GetStateManager();
	G4ApplicationState currentState = stateManager->GetCurrentState();
	if (currentState != G4State_PreInit && currentState != G4State_Idle)
	{
		G4cerr << "Illegal application state - "
			<< "G4RunManager::Initialize() ignored." << G4endl;
		return;
	}

	if (!geometryInitialized) {
		InitializeGeometry();
		G4cerr << "Geometry not initialized" << G4endl;
	}
	if (!physicsInitialized) {
		InitializePhysics();
		InitializeGeometry();
		G4cerr << "Physics not initialized" << G4endl;
	}
	initializedAtLeastOnce = true;
}