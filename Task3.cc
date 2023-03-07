#include <iostream>

#include "G4RunManager.hh"
//#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BERT.hh"
#include "G4ScoringManager.hh"
#include "G4LogicalVolume.hh"
#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "detector.hh"


G4double dModerator;
G4double dModeratorEnd;
G4double distTarMod;
G4double sigmaPos;
G4double avgE;

G4double eDepMod;
G4double eDepModGamma;
G4double eDepModElectron;
G4double eDepModPositron;
G4int noAnnihilationTar;
G4int noPairProductionTar;
G4int noAnnihilationMod;
G4int noPairProductionMod;
G4int noAnnihilationModEnd;
G4int noPairProductionModEnd;

int main(int argc, char** argv)
{


    G4UIExecutive* ui = 0;

    G4RunManager* runManager = new G4RunManager;

    /*
    #ifdef G4MULTITHREADED
     G4MTRunManager *runManager = new G4MTRunManager;
    #else
     
    #endif
    */

      G4ScoringManager* scoringManager = G4ScoringManager::GetScoringManager();
      runManager->SetUserInitialization(new MyDetectorConstruction());
      runManager->SetUserInitialization(new MyPhysicsList());
      runManager->SetUserInitialization(new MyActionInitialization());

     runManager->Initialize();

      if (argc == 1) {
          ui = new G4UIExecutive(argc, argv);
      }


    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();   
    //UImanager->ApplyCommand("/cuts/setMaxCutEnergy 9 MeV");

    if (ui) {
        UImanager->ApplyCommand("/control/execute vis.mac");
        UImanager->ApplyCommand("/control/execute gui.mac");
        ui->SessionStart();
    }
    else
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }
    delete runManager;
    return EXIT_SUCCESS;
}

/*
G4double distGunTar = 1 * cm;
G4double distTarMod = 2. * mm;
G4double dModerator = 0.2 * mm;
*/


/*
UImanager->ApplyCommand("/vis/open OGL 1920x1080 -0+0");

UImanager->ApplyCommand("/vis/view/set/viewpointVector 1 1 1");
UImanager->ApplyCommand("/vis/drawVolume");
UImanager->ApplyCommand("/vis/scene/add/axes");
UImanager->ApplyCommand("/vis/scene/add/eventID"); // how good is that ?
UImanager->ApplyCommand("/vis/scene/add/date");
UImanager->ApplyCommand("/vis/geometry/set/visibility World 0 false");
UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByCharge");
UImanager->ApplyCommand("/vis/modeling/trajectories/drawByCharge-0/default/setDrawStepPts true");
UImanager->ApplyCommand("/vis/modeling/trajectories/drawByCharge-0/default/setStepPtsSize 2");
UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
*/


//    runManager->SetUserInitialization(new MyDetectorConstruction());
 //   runManager->SetUserInitialization(new MyPhysicsList());
//    runManager->SetUserInitialization(new MyActionInitialization());

//    G4VModularPhysicsList* physics = new QGSP_BERT();
 //   physics->RegisterPhysics(new G4DecayPhysics());
 //   runManager->SetUserInitialization(physics);
// 




/*


    UImanager->ApplyCommand("/vis/open OGL 1920x1080 -0+0");

    UImanager->ApplyCommand("/vis/view/set/viewpointVector 1 1 1");
    UImanager->ApplyCommand("/vis/drawVolume");
   // UImanager->ApplyCommand("/vis/scene/add/scale");
    UImanager->ApplyCommand("/vis/scene/add/axes");
    UImanager->ApplyCommand("/vis/scene/add/eventID"); // how good is that ?
    UImanager->ApplyCommand("/vis/scene/add/date");
    UImanager->ApplyCommand("/vis/geometry/set/visibility World 0 false");
    UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByCharge");
    UImanager->ApplyCommand("/vis/modeling/trajectories/drawByCharge-0/default/setDrawStepPts true");
    UImanager->ApplyCommand("/vis/modeling/trajectories/drawByCharge-0/default/setStepPtsSize 2");
    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");


    // UImanager->ApplyCommand("/vis/scene/add/logo2D");
   // UImanager->ApplyCommand("/vis/scene/add/logo");

    UImanager->ApplyCommand("/vis/view/autoRefresh false"); // true (?)
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");


    UImanager->ApplyCommand("/score/create/boxMesh moderatorEnergyMesh");
    UImanager->ApplyCommand("/score/mesh/boxSize 110 50. 20. mm");          // mesh has to be moved, so it contains the moderator
    UImanager->ApplyCommand("/score/mesh/nBin 100 50 50");
    UImanager->ApplyCommand("/score/mesh/translate/xyz 13. 0. 0. cm");
    UImanager->ApplyCommand("/score/quantity/energyDeposit energyScorer MeV");
    UImanager->ApplyCommand("/run/beamOn 10000");
    UImanager->ApplyCommand("/score/drawProjection moderatorEnergyMesh energyScorer");
    UImanager->ApplyCommand("/score/dumpQuantityToFile moderatorEnergyMesh energyScorer energyDeposit.txt");

        // UImanager->ApplyCommand("/vis/scene/add/scale");

*/