#include <iostream>
#include <chrono>
#include <string.h>
#include <iomanip>
#include <sstream>



#include "G4RunManager.hh"
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
#include "createTuples.hh"

// choiceGeometry determines geometric setup:
// 0 Sampling wall geometry
// 1 COMSOL geometry
/*--------------------------------------------*/
// choiceParticle determines type of particles:
// 0 fast e- from actual target
// 1 fast e+ from sample 24380 particles (originate from 3 * 10^7 e-)
// 2 fast e- from COMSOL target
// 3 fast e+ from COMSOL target
// 4 slow e+ from COMSOL moderator
// 5 slow e+ from actual moderator 
/*--------------------------------------------*/
// choiceStepping determines which data will be stored



int main(int argc, char** argv)
{
    bool showVis = false;

    G4int choiceGeometry = 0;
    G4int choiceParticle = 1;

    G4double distTargetOrigin = 50.5 * cm;
    G4double avgE = 9 * MeV;
    G4double dModeratorTotal = 1.5 * mm;
    G4double dModeratorFront = 0.500 * mm;
    dModeratorTotal = dModeratorFront * 4;
    G4double distTarMod = 2*mm;
    G4double widthModerator = 20 * cm;
    G4double moderatorHeight = 60 * cm;

    G4double scaleBDipole = 0.5;
    G4double scaleBNeon = 1.5;
    G4double scaleBSolenoid = 1.;
    G4double scaleBTarget = 1.5;
    G4double scaleE = 1.;

    G4String moderatorMaterial = "Neon";

    G4int noEvents = 10000;

    G4RunManager* runMan = new G4RunManager;
    ConstructionParameters constructionParameters(choiceGeometry, dModeratorTotal, dModeratorFront,
        widthModerator, distTargetOrigin, moderatorHeight, scaleBDipole, scaleBNeon, scaleBSolenoid,
        scaleBTarget, scaleE, moderatorMaterial);

    runMan->SetUserInitialization(new MyPhysicsList());
    createTuples();

    G4UIExecutive* ui = 0;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }
    G4UImanager *UImanager = G4UImanager::GetUIpointer();   
    G4String fileNames[5] = { "BDipole", "BNeon", "BSolenoid", "BTarget", "E" };
    G4int curRun = 0;
    G4int maxRun = 4;

    G4String fileName;
    G4String fileNameWalls;
    G4String fileNameParameters;

    double TarNeStart = 1.;
    double TarNeStep = 0.5;;
    double DiStart = 0.1;
    double DiStep = 0.2;

    int noTarNe = 4;
    int noDi = 8;
    

    if (!showVis) {
        /*
        for (int TarNeRun = 0; TarNeRun < noTarNe; ++TarNeRun) { // for every fixed target and neon current
            scaleBTarget = TarNeStart + TarNeRun * TarNeStep;
            scaleBNeon = scaleBTarget;
            constructionParameters.SetScaleBTarget(scaleBTarget);
            constructionParameters.SetScaleBNeon(scaleBNeon);
            for (int DiRun = 0; DiRun < noDi; ++DiRun) {
                fileNameWalls = "scoreScalingTarNeRunWalls" + std::to_string(TarNeRun) + "DiRun" + std::to_string(DiRun) + ".csv";
                fileNameParameters = "scoreScalingTarNeRunParameters" + std::to_string(TarNeRun) + "DiRun" + std::to_string(DiRun) + ".csv";
                scaleBDipole = DiStart + DiRun * DiStep;
                constructionParameters.SetScaleBDipole(scaleBDipole);
                constructionParameters.StoreParameters(-1, fileNameParameters);

                runMan->SetUserInitialization(new DetectorConstruction(&constructionParameters));
                runMan->SetUserInitialization(new MyActionInitialization(curRun, choiceParticle, distTargetOrigin, avgE, choiceGeometry, dModeratorTotal,
                    distTarMod, fileNameWalls));
                runMan->InitializeGeometry();
                runMan->GeometryHasBeenModified();
                runMan->Initialize();
                runMan->BeamOn(noEvents);




            }

        }
        exit(2);
        */
        fileName = "Standard.csv";
        runMan->SetUserInitialization(new DetectorConstruction(&constructionParameters));
        runMan->SetUserInitialization(new MyActionInitialization(curRun, choiceParticle, distTargetOrigin, avgE, choiceGeometry, dModeratorTotal,
            distTarMod, fileName));
        runMan->InitializeGeometry();
        runMan->GeometryHasBeenModified();
        runMan->Initialize();
        runMan->BeamOn(noEvents);


       //fileName = "targetSecondWall";
       //fileName = "Standard";
       //fileName = "dipoleSecondWall";
       //fileName = "neonSecondWall";

   
        for (curRun = 0; curRun < maxRun; ++curRun) {   // for every run
            //scaleBNeon = 0.8 + curRun * 0.1;
            //constructionParameters.SetScaleBNeon(scaleBNeon);
            //constructionParameters.StoreParameters(curRun, fileName);
            /*
            runMan->SetUserInitialization(new DetectorConstruction(&constructionParameters));
            runMan->SetUserInitialization(new MyActionInitialization(curRun, choiceParticle, distTargetOrigin, avgE, choiceGeometry, dModeratorTotal,
                distTarMod, fileName));
            runMan->InitializeGeometry();
            runMan->GeometryHasBeenModified();
            runMan->Initialize();
            runMan->BeamOn(noEvents);
            */
        }
        /*
       int ratioCount = -1;
       double ratio = -1;
       int innerNumber = 0;
       for (int i = 0; i < maxRun; ++i) {    // for every fixed current in 
           scaleBDipole = (double)(i + 2.)/2.;
           ratio = 0.5;
           ratioCount = 0;
           while (ratio < 2.2) {
               fileNameWalls = "ratioTarDiWalls"  + std::to_string(ratioCount + i * innerNumber) + ".csv";
               fileNameParameters = "ratioTarDiParameters" + std::to_string(ratioCount + i * innerNumber) + ".csv";
               G4cout << fileName << G4endl;
               scaleBTarget = scaleBDipole * ratio;
               constructionParameters.SetScaleAll(scaleBDipole, scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE);
               constructionParameters.StoreParameters(curRun, fileNameParameters);
               runMan->SetUserInitialization(new DetectorConstruction(&constructionParameters));
               runMan->SetUserInitialization(new MyActionInitialization(curRun, choiceParticle, distTargetOrigin, avgE, choiceGeometry, dModeratorTotal,
                   distTarMod, fileNameWalls));
               runMan->InitializeGeometry();
               runMan->GeometryHasBeenModified();
               runMan->Initialize();
               runMan->BeamOn(noEvents);
               ratio += 0.1;
               ratioCount++;

           }          
           innerNumber = ratioCount;

        }*/
      // exit(1);
       
       
        /*
        for (int i = 0; i < 5; ++i) {       // for every field
            for (curRun = 0; curRun < maxRun; ++curRun) {   // for every run
                G4double scaleBDipole = 1.;
                G4double scaleBNeon = 1.;
                G4double scaleBSolenoid = 1.;
                G4double scaleBTarget = 1.;
                G4double scaleE = 1.;
                switch (i) {
                case 0:
                    scaleBDipole = 0.8 + curRun * 0.1;
                    constructionParameters.SetScaleAll(scaleBDipole, scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE);
                    constructionParameters.StoreParameters(curRun, fileNames[i]);
                    break;
                case 1:
                    scaleBNeon = 0.8 + curRun * 0.1;
                    constructionParameters.SetScaleAll(scaleBDipole, scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE);
                    constructionParameters.StoreParameters(curRun, fileNames[i]);
                    break;
                case 2:
                    scaleBSolenoid = 0.8 + curRun * 0.1;
                    constructionParameters.SetScaleAll(scaleBDipole, scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE);
                    constructionParameters.StoreParameters(curRun, fileNames[i]);
                    break;
                case 3:
                    scaleBTarget = 0.8 + curRun * 0.1;
                    constructionParameters.SetScaleAll(scaleBDipole, scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE);
                    constructionParameters.StoreParameters(curRun, fileNames[i]);
                    break;
                case 4:
                    scaleE = 0.8 + curRun * 0.1;
                    constructionParameters.SetScaleAll(scaleBDipole, scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE);
                    constructionParameters.StoreParameters(curRun, fileNames[i]);
                    break;
                }
                runMan->SetUserInitialization(new DetectorConstruction(&constructionParameters));
                runMan->SetUserInitialization(new MyActionInitialization(curRun, choiceParticle, distTargetOrigin, avgE, choiceGeometry, dModeratorTotal,
                distTarMod, fileNames[i]));
                runMan->InitializeGeometry();
                runMan->GeometryHasBeenModified();
                runMan->Initialize();
                runMan->BeamOn(10000);
            }
        }
        */
        G4cout << "After loop!" << G4endl;
    }
    else {
        G4VisManager* visManager = new G4VisExecutive();
        visManager->Initialize();
        runMan->SetUserInitialization(new DetectorConstruction(&constructionParameters));
        runMan->SetUserInitialization(new MyActionInitialization(curRun, choiceParticle, distTargetOrigin, avgE, choiceGeometry, dModeratorTotal,
            distTarMod, fileName));
        //UImanager->ApplyCommand("/cuts/setMaxCutEnergy 9 MeV");
        runMan->Initialize();
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
    }
    delete runMan;
    return EXIT_SUCCESS;
}

