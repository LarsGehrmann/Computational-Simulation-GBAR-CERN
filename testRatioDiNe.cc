#include "testRatioDiNe.hh"


void testRatioDiNe(ConstructionParameters *constructionParameters,  RunParameters * runParameters, G4RunManager* runMan, double DiStart, 
	double DiStep, double ratioStart, double ratioStep, int noDi, int noNe) {

    int curRun = -1;
    G4double scaleBDipole, scaleBNeon;
    G4int choiceParticle = -1;
    double ratio = -1;
    G4String fileNameWalls, fileNameParameters;
    for (int DiRun = 0; DiRun < noDi; ++DiRun) { // for every fixed target scaling
        scaleBDipole = DiStart + DiRun * DiStep;
        constructionParameters->SetScaleBDipole(scaleBDipole);
        for (int NeRun = 0; NeRun < noNe; ++NeRun) {
            curRun = DiRun * noNe + NeRun;
            fileNameWalls = "hitsScalingDiNeRunWalls" + std::to_string(DiRun) + "NeRun" + std::to_string(NeRun) + ".csv";
            fileNameParameters = "hitsScalingDiNeRunParameters" + std::to_string(DiRun) + "DiRun" + std::to_string(NeRun) + ".csv";
            ratio = ratioStart + NeRun * ratioStep;
            scaleBNeon = scaleBDipole * ratio;
            G4cout << "scaleBDipole: " << scaleBDipole << G4endl;
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
