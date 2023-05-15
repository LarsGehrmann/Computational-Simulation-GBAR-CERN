#include "testRatioTarEqNeAndDi.hh"


void testRatioTarEqNeAndDi(ConstructionParameters* constructionParameters, RunParameters* runParameters, G4RunManager* runMan, double TarStart,
    double TarStep, double ratioStart, double ratioStep, int noTar, int noDi) {

    int curRun = -1;
    G4double scaleBTarget, scaleBDipole;
    G4double scaleBNeon;
    G4int choiceParticle = -1;
    double ratio = -1;
    G4String fileNameWalls, fileNameParameters;
    for (int TarRun = 0; TarRun < noTar; ++TarRun) { // for every fixed target scaling
        scaleBTarget = TarStart + TarRun * TarStep;
        scaleBNeon = scaleBTarget;
        constructionParameters->SetScaleBTarget(scaleBTarget);
        constructionParameters->SetScaleBNeon(scaleBNeon);
        for (int DiRun = 0; DiRun < noDi; ++DiRun) {
            curRun = TarRun * noDi + DiRun;
            fileNameWalls = "hitsScalingTarEqNeAndDiRunWalls" + std::to_string(TarRun) + "DiRun" + std::to_string(DiRun) + ".csv";
            fileNameParameters = "hitsScalingTarEqNeAndDiRunParameters" + std::to_string(TarRun) + "DiRun" + std::to_string(DiRun) + ".csv";
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
