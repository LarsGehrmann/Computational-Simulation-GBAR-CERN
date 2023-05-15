#include "testRatioTarNe.hh"


void testRatioTarNe(ConstructionParameters* constructionParameters, RunParameters* runParameters, G4RunManager* runMan, double TarStart,
    double TarStep, double ratioStart, double ratioStep, int noTar, int noNe) {

    int curRun = -1;
    G4double scaleBTarget, scaleBNeon;
    G4int choiceParticle = -1;
    double ratio = -1;
    G4String fileNameWalls, fileNameParameters;
    for (int TarRun = 0; TarRun < noTar; ++TarRun) { // for every fixed target scaling
        scaleBTarget = TarStart + TarRun * TarStep;
        constructionParameters->SetScaleBTarget(scaleBTarget);
        for (int NeRun = 0; NeRun < noNe; ++NeRun) {
            curRun = TarRun * noNe + NeRun;
            fileNameWalls = "hitsScalingTarNeRunWalls" + std::to_string(TarRun) + "NeRun" + std::to_string(NeRun) + ".csv";
            fileNameParameters = "hitsScalingTarNeRunParameters" + std::to_string(TarRun) + "NeRun" + std::to_string(NeRun) + ".csv";
            ratio = ratioStart + NeRun * ratioStep;
            scaleBNeon = scaleBTarget * ratio;
            G4cout << "scaleBNeon: " << scaleBNeon << G4endl;
            constructionParameters->SetScaleBNeon(scaleBNeon);
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
