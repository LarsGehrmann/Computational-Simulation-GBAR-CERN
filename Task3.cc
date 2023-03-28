#include <iostream>
#include <chrono>

#include "G4RunManager.hh"
//#include "G4MTG4RunManagerager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BERT.hh"
#include "G4ScoringManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

#include "physics.hh"
#include "action.hh"

#include "ConstructionParameters.hh"
#include "construction.hh"

//#include "detector.hh"
//
#include "runMan.hh"
#include "createTuples.hh"

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

///  Built on G4RunManagerager and change: initilize! buildAtLeastOnce hast to get false;

int main(int argc, char** argv)
{
    G4int choiceGeometry = 2;
    G4int choiceParticle = 1;

    G4double distTargetOrigin = 50.5 * cm;
    G4double avgE = 9 * MeV;
    G4double dModerator = 0.15 * mm;
    G4double dModeratorEnd = 0.05 * mm;
    G4double dModeratorFront = 0.05 * mm;
    G4double distTarMod = 2*mm;
    G4double widthModeratorPart = 1 * cm;
    G4double moderatorHeight = 60 * cm;

    G4double scaleBDipole = 1.;
    G4double scaleBNeon = 1.;
    G4double scaleBSolenoid = 1.;
    G4double scaleBTarget = 1.;
    G4double scaleE = 1.;


    G4RunManager* runMan = new G4RunManager;
   

    ConstructionParameters constructionParameters(choiceGeometry, dModerator, dModeratorFront,
        widthModeratorPart, distTargetOrigin, moderatorHeight, scaleBDipole, scaleBNeon, scaleBSolenoid,
        scaleBTarget, scaleE);
    
   // G4RunManagerager->SetUserInitialization(new DetectorConstruction(&constructionParameters));
    runMan->SetUserInitialization(new MyPhysicsList());
    //G4RunManagerager->SetUserInitialization(new MyActionInitialization(choiceParticle, distTargetOrigin, avgE, choiceGeometry, dModerator, 
     //   distTarMod, scaleE));

    G4UIExecutive* ui = 0;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }
    
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    
    G4UImanager *UImanager = G4UImanager::GetUIpointer();   
    UImanager->ApplyCommand("/mcVerbose/geometryManager 0");
    G4int curRun = 0;
    G4int maxRun = 10;

    G4String fileNames[5] = {"BDipole", "BNeon", "BSolenoid", "BTarget", "E"};
    createTuples();

    for (int i = 0; i < 5; ++i) {
        G4double scaleBDipole = 1.;
        G4double scaleBNeon = 1.;
        G4double scaleBSolenoid = 1.;
        G4double scaleBTarget = 1.;
        G4double scaleE = 1.;
        for (curRun = 0; curRun < maxRun; ++curRun) {
            switch (i) {
            case 0:
                scaleBDipole = 0.8 + curRun * 0.1;
                constructionParameters.SetScaleBDipole(scaleBDipole);
                constructionParameters.StoreParameters(curRun, fileNames[i]);
                break;
            case 1:
                scaleBNeon = 0.8 + curRun * 0.1;
                constructionParameters.SetScaleBNeon(scaleBNeon);
                constructionParameters.StoreParameters(curRun, fileNames[i]);
                break;
            case 2:
                scaleBSolenoid = 0.8 + curRun * 0.1;
                constructionParameters.SetScaleBSolenoid(scaleBSolenoid);
                constructionParameters.StoreParameters(curRun, fileNames[i]);
                break;
            case 3:
                scaleBTarget = 0.8 + curRun * 0.1;
                constructionParameters.SetScaleBTarget(scaleBTarget);
                constructionParameters.StoreParameters(curRun, fileNames[i]);
                break;
            case 4:
                scaleE = 0.8 + curRun * 0.1;
                constructionParameters.SetScaleE(scaleE);
                constructionParameters.StoreParameters(curRun, fileNames[i]);
                break;
            }
            //distTargetOrigin = 32.5 * cm + curRun * 2.5 * cm;
            //moderatorHeight = 40 * cm + 5 * cm * curRun;
            //constructionParameters.SetDistTargetOrigin(distTargetOrigin);
            runMan->SetUserInitialization(new DetectorConstruction(&constructionParameters));
            runMan->SetUserInitialization(new MyActionInitialization(curRun, choiceParticle, distTargetOrigin, avgE, choiceGeometry, dModerator,
            distTarMod, fileNames[i]));
            //UImanager->ApplyCommand("/run/reinitilizeGeometry true");
            G4cout << "Before initialize geometry" << G4endl;
            runMan->InitializeGeometry();
            runMan->GeometryHasBeenModified();
            //UImanager->ApplyCommand("/run/reinitilizeGeometry");
            runMan->Initialize();
            runMan->BeamOn(10000);
        // UImanager->ApplyCommand("/run/initialize");
        }
    }

    G4cout << "After loop!" << G4endl;

     //UImanager->ApplyCommand("/cuts/setMaxCutEnergy 9 MeV");
    /*
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
     */
    delete runMan;
    return EXIT_SUCCESS;
}

