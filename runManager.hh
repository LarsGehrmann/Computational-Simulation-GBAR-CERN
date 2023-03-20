#ifndef RUNMANAGER_HH
#define RUNMANAGER_HH

#include <sstream>

#include "G4Timer.hh"

#include "G4MTRunManagerKernel.hh"
#include "G4RunManager.hh"
#include "G4RunManagerKernel.hh"
#include "G4WorkerRunManagerKernel.hh"

#include "G4ApplicationState.hh"
#include "G4Material.hh"
#include "G4ParallelWorldProcessStore.hh"
#include "G4ParticleTable.hh"
#include "G4ProcessTable.hh"
#include "G4ProductionCutsTable.hh"
#include "G4Run.hh"
#include "G4RunMessenger.hh"
#include "G4SDManager.hh"
#include "G4StateManager.hh"
#include "G4TiMemory.hh"
#include "G4UImanager.hh"
#include "G4UnitsTable.hh"
#include "G4UserRunAction.hh"
#include "G4UserWorkerInitialization.hh"
#include "G4UserWorkerThreadInitialization.hh"
#include "G4VPersistencyManager.hh"
#include "G4VScoreNtupleWriter.hh"
#include "G4VUserActionInitialization.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VUserPhysicsList.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "Randomize.hh"
#include "G4TiMemory.hh"
#include "G4Profiler.hh"

#include "G4HCofThisEvent.hh"
#include "G4ParallelWorldProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4ProcessManager.hh"
#include "G4ScoringManager.hh"
#include "G4TransportationManager.hh"
#include "G4VHitsCollection.hh"
#include "G4VScoringMesh.hh"

#include "G4ScoringBox.hh"
#include "G4ScoringCylinder.hh"
#include "G4LogicalVolume.hh"
#include "G4SmartVoxelHeader.hh"
#include "G4SmartVoxelStat.hh"
#include "G4VPhysicalVolume.hh"

#include "G4AssemblyStore.hh"
#include "G4GeometryManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4RegionStore.hh"
#include "G4SolidStore.hh"

#include "action.hh"
#include "construction.hh"
#include "physics.hh"

using namespace CLHEP;


class MyRunManager : public G4RunManager
{
	public:
		MyRunManager();
		~MyRunManager();

		void SetUserInitialization(MyActionInitialization* userInit);
		void SetUserInitialization(MyDetectorConstruction* userInit);
		void SetUserInitialization(MyPhysicsList* userInit);

private:



};
#endif
