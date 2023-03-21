#include <iostream>
#include <chrono>

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

//#include "detector.hh"
//
//#include "runManager.hh"



// choiceGeometry determines geometric setup:
// 0 real geometry
// 1 COMSOL geometry
// 2 sample e+ geometry
/*--------------------------------------------*/
// choiceParticle determines type of particles:
// 0 fast e- from actual target
// 1 fast e+ from sample 24380 particles (originate from 3 * 10^7 e-)
// 2 fast e- from COMSOL target
// 3 fast e+ from COMSOL target
// 4 slow e+ from COMSOL moderator
// 5 slow e+ from actual moderator 


/// Comment of sensitive detecor

int main(int argc, char** argv)
{
    G4int choiceParticle = 1;
    G4int choiceGeometry = 2;

    G4double distTargetOrigin = 50.5 * cm;
    G4double avgE = 9 * MeV;
    G4double dModerator = 0.15 * mm;
    G4double dModeratorEnd = 0.05 * mm;
    G4double dModeratorFront = 0.05 * mm;
    G4double distTarMod = 2*mm;
    G4double widthModeratorPart = 1 * cm;
    G4double moderatorHeight = 60 * cm;

    G4double scaleBDipole = 1;
    G4double scaleBNeon = 1;
    G4double scaleBSolenoid = 1;
    G4double scaleBTarget = 1;
    G4double scaleE = 1;




    G4UIExecutive* ui = 0;
    G4RunManager* runManager = new G4RunManager;
    G4ScoringManager* scoringManager = G4ScoringManager::GetScoringManager();
   runManager->SetUserInitialization(new MyDetectorConstruction(dModerator, dModeratorFront, distTarMod, distTargetOrigin, 
        choiceGeometry, widthModeratorPart, moderatorHeight, scaleBDipole, scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE));

    runManager->SetUserInitialization(new MyPhysicsList());

    runManager->SetUserInitialization(new MyActionInitialization(choiceParticle, distTargetOrigin, avgE, choiceGeometry, dModerator, 
        distTarMod, scaleE));

    runManager->Initialize();
   
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    G4UImanager *UImanager = G4UImanager::GetUIpointer();   

    UImanager->ApplyCommand("/run/initialize");
    UImanager->ApplyCommand("/run/reinitializeGeometry");
    UImanager->ApplyCommand("/run/beamOn 1000");
    //UImanager->ApplyCommand("/run/beamOn 24380");

    /*
    int curRun = 0;
    int maxRun = 1;
    UImanager->ApplyCommand("/run/initialize");
    for (int curRun = 0; curRun < maxRun; curRun++) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        G4cout << "Run number: " << curRun+1 << "/" << maxRun << G4endl;
        UImanager->ApplyCommand("/run/beamOn 10000");
      //  UImanager->ApplyCommand("/run/beamOn 10000000");
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::minutes>(end - begin).count() << "[min]" << std::endl;
    }
    */
     /*
     UImanager->ApplyCommand("/output/outputNameValues distTargetOriginValues");
     UImanager->ApplyCommand("/output/outputNameParameters distTargetOriginParameters");
     */

     /*
     for (int i = 0; i < 10; i++) {
        // scaleB = 0.5 + 0.1 * i;
         distTargetOrigin = 25 * cm + i * 5 * cm;
         UImanager->ApplyCommand("/run/initialize");
         UImanager->ApplyCommand("/run/reinitializeGeometry");
         UImanager->ApplyCommand("/run/beamOn 1000000");
        // UImanager->ApplyCommand("/run/beamOn 100");
     }
     */


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

*/

//////////////////////////////////////////////////////////////////////////////////

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