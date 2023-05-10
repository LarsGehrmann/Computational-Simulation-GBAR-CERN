#include "testRatio.hh"


void testRatio(ConstructionParameters *constructionParameters,  RunParameters *runParameters, G4RunManager* runMan, 
    double TarNeStart, double TarNeStep, double ratioStart, double ratioStep, int noTarNe, int noDi) {

    int curRun = -1;
    G4double scaleBTarget, scaleBNeon, scaleBDipole;
    G4int choiceParticle = -1;
    double ratio = -1;
    G4String fileNameWalls, fileNameParameters;
    for (int TarNeRun = 0; TarNeRun < noTarNe; ++TarNeRun) { // for every fixed target and neon current
        scaleBTarget = TarNeStart + TarNeRun * TarNeStep;
        scaleBNeon = scaleBTarget;
        constructionParameters->SetScaleBTarget(scaleBTarget);
        constructionParameters->SetScaleBNeon(scaleBNeon);
        for (int DiRun = 0; DiRun < noDi; ++DiRun) {
            curRun = TarNeRun * noDi + DiRun;
            fileNameWalls = "scoreScalingTarNeRunWalls" + std::to_string(TarNeRun) + "DiRun" + std::to_string(DiRun) + ".csv";
            fileNameParameters = "scoreScalingTarNeRunParameters" + std::to_string(TarNeRun) + "DiRun" + std::to_string(DiRun) + ".csv";
            ratio = ratioStart + DiRun * ratioStep;
            scaleBDipole = scaleBTarget * ratio;
            G4cout << "scaleBDipole: " << scaleBDipole << G4endl;
            constructionParameters->SetScaleBDipole(scaleBDipole);
            constructionParameters->StoreParameters(-1, fileNameParameters);

            runMan->SetUserInitialization(new DetectorConstruction(constructionParameters));

            runMan->SetUserInitialization(new MyActionInitialization(curRun, runParameters->GetChoiceParticle(), runParameters->GetDistTargetOrigin(),
                runParameters->GetAvgE(), runParameters->GetChoiceGeometry(), runParameters->GetDModeratorTotal(),
                runParameters->GetDistTarMod(), fileNameWalls));
            runMan->InitializeGeometry();
            runMan->GeometryHasBeenModified();
            runMan->Initialize();
            runMan->BeamOn(runParameters->GetNoEvents());




        }

    }
}
