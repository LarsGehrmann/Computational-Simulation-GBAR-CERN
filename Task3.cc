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

#include "RunParameters.hh"
#include "ConstructionParameters.hh"
#include "construction.hh"
#include "createTuples.hh"

#include "testRatioTarDi.hh"
#include "testRatioTarNe.hh"
#include "testRatioDiNe.hh"
#include "testRatioTarEqNeAndDi.hh"
#include "testDistancesTargetOrigin.hh"
#include "testFields.hh"
#include "testRatio.hh"

/*--------------------------------------------*/
// choiceGeometry determines geometric setup:
// 0 Sampling wall geometry
// 1 COMSOL geometry
/*--------------------------------------------*/
// choiceParticle determines type of particles:
// 0 fast e- from actual target
// 1 fast e+ from sample 16514 particles (originate from 2*10^7 simulated e-)
// 2 fast e- from COMSOL target 
// 3 fast e+ from COMSOL target
// 4 slow e+ from COMSOL moderator
/*--------------------------------------------*/

int main(int argc, char** argv)
{
    bool showVis = true;

    G4int choiceGeometry = 1;
    G4int choiceParticle = 1;

    G4double distTargetOrigin = 50.5 * cm;
    G4double avgE = 9 * MeV;
    G4double dModeratorTotal = 1.5 * mm;
    G4double dModeratorFront = 0.500 * mm;
    dModeratorTotal = dModeratorFront * 4;
    G4double distTarMod = 2*mm;
    G4double widthModerator = 20 * cm;
    G4double moderatorHeight = 60 * cm;

    G4double scaleBDipole = 1.0;
    G4double scaleBNeon = 1.0;
    G4double scaleBSolenoid = 1.;
    G4double scaleBTarget = 1.0;
    G4double scaleE = 1.;

    G4String moderatorMaterial = "Neon";

    G4int noEvents = 10000;

    G4String fileName = "Standard.csv";

    G4RunManager* runMan = new G4RunManager;
    ConstructionParameters constructionParameters(choiceGeometry, dModeratorTotal, dModeratorFront,
        widthModerator, distTargetOrigin, moderatorHeight, scaleBDipole, scaleBNeon, scaleBSolenoid,
        scaleBTarget, scaleE, moderatorMaterial);
    RunParameters runParameters(noEvents, choiceParticle, choiceGeometry, distTargetOrigin, avgE, dModeratorTotal, distTarMod, 
        fileName);


    runMan->SetUserInitialization(new MyPhysicsList());
    createTuples();

    G4UIExecutive* ui = 0;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }
    G4UImanager *UImanager = G4UImanager::GetUIpointer();   

    G4int curRun = 0;

//    G4String fileNameWalls;
 //   G4String fileNameParameters;




    if (!showVis) {
        
        runMan->SetUserInitialization(new DetectorConstruction(&constructionParameters));
        runMan->SetUserInitialization(new MyActionInitialization(curRun, choiceParticle, distTargetOrigin, avgE, choiceGeometry, dModeratorTotal,
            distTarMod, fileName));
        runMan->InitializeGeometry();
        runMan->GeometryHasBeenModified();
        runMan->Initialize();
        runMan->BeamOn(noEvents);
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




/*    double TarNeStart = 1.;
    double TarNeStep = 0.5;;
    double ratioStart = 0.0;
    double ratioStep = 0.05;

    int noTarNe = 4;
    int noDi = 16;

    //testRatio(&constructionParameters, &runParameters, runMan, TarNeStart, TarNeStep, ratioStart, ratioStep, noTarNe, noDi);
    //exit(2);
*/

/*
    G4double minScale = 0.7;
    G4double maxScale = 2.0;
    G4double stepScale = 0.1;
    testFields(&constructionParameters, &runParameters, runMan, minScale, maxScale, stepScale);
    exit(2);
*/

/*
    G4double minDist = 35 * cm;
    G4double maxDist = 70 * cm;
    G4double stepDist = 2.5 * cm;
    G4int noDist = 15;
    testDistancesTargetOrigin(&constructionParameters, &runParameters, runMan,
        minDist, maxDist, stepDist, noDist);
    exit(2);
*/

/*
    double TarStart = 1.;
    double TarStep = 0.5;;
    double ratioStart = 0.2;
    double ratioStep = 0.1;

    int noTar = 4;
    int noDi = 15;

    testRatioTarDi(&constructionParameters, &runParameters, runMan, TarStart, TarStep, ratioStart, ratioStep, noTar, noDi);
    exit(2);
*/


/*
double DiStart = 1.;
double DiStep = 0.5;
double ratioStart = 0.4;
double ratioStep = 0.2;

int noDi = 4;
int noNe = 15;

testRatioDiNe(&constructionParameters, &runParameters, runMan, DiStart, DiStep, ratioStart, ratioStep, noDi, noNe);
exit(2);
*/

/*
double TarStart = 1.;
double TarStep = 0.5;;
double ratioStart = 0.5;
double ratioStep = 0.1;

int noTar = 4;
int noNe = 15;

testRatioTarNe(&constructionParameters, &runParameters, runMan, TarStart, TarStep, ratioStart, ratioStep, noTar, noNe);
exit(2);
*/

/*
    double TarStart = 1.;
    double TarStep = 0.5;;
    double ratioStart = 0.2;
    double ratioStep = 0.1;

    int noTar = 4;
    int noDi = 15;

    testRatioTarEqNeAndDi(&constructionParameters, &runParameters, runMan, TarStart, TarStep, ratioStart, ratioStep, noTar, noDi);
    exit(2);
    */