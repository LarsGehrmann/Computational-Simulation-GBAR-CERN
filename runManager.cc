#include "runManager.hh"


void MyRunManager::SetUserInitialization(MyActionInitialization* userInit)
{
	userActionInitialization = userInit;
	userActionInitialization->customBuild();
}
void MyRunManager::SetUserInitialization(MyDetectorConstruction* userInit)
{
	userDetector = userInit;
}
void MyRunManager::SetUserInitialization(MyPhysicsList* userInit)
{
	physicsList = userInit;
	kernel->SetPhysics(userInit);
}

MyRunManager::MyRunManager()
{
	if (fRunManager)
	{
		G4Exception("G4RunManager::G4RunManager()", "Run0031", FatalException,
			"G4RunManager constructed twice.");
	}
	fRunManager = this;

	kernel = new G4RunManagerKernel();
	eventManager = kernel->GetEventManager();

	timer = new G4Timer();
	runMessenger = new G4RunMessenger(this);
	previousEvents = new std::list<G4Event*>;
	G4ParticleTable::GetParticleTable()->CreateMessenger();
	G4ProcessTable::GetProcessTable();
	std::ostringstream oss;
	G4Random::saveFullState(oss);
	randomNumberStatusForThisRun = oss.str();
	randomNumberStatusForThisEvent = oss.str();
	runManagerType = sequentialRM;
}

MyRunManager::~MyRunManager()
{
	// finalise profiler before shutting down the threads
	G4Profiler::Finalize();
	G4StateManager* pStateManager = G4StateManager::GetStateManager();
	// set the application state to the quite state
	if (pStateManager->GetCurrentState() != G4State_Quit)
	{
		if (verboseLevel > 0)
			G4cout << "G4 kernel has come to Quit state." << G4endl;
		pStateManager->SetNewState(G4State_Quit);
	}

	CleanUpPreviousEvents();
	delete currentRun;
	delete timer;
	delete runMessenger;
	delete previousEvents;

	// The following will work for all RunManager types
	// if derived class does the correct thing in the derived
	// destructor that is: set to zero pointers of
	// user initialization objects for which have no
	// ownership
	DeleteUserInitializations();
	delete userRunAction;
	userRunAction = nullptr;
	if (verboseLevel > 1)
		G4cout << "UserRunAction deleted." << G4endl;

	delete userPrimaryGeneratorAction;
	userPrimaryGeneratorAction = nullptr;
	if (verboseLevel > 1)
		G4cout << "UserPrimaryGenerator deleted." << G4endl;

	if (verboseLevel > 1)
		G4cout << "RunManager is deleting RunManagerKernel." << G4endl;

	delete kernel;

	fRunManager = nullptr;

	if (verboseLevel > 1)
		G4cout << "RunManager is deleted." << G4endl;
}


