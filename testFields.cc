#include "testFields.hh"


void testFields(ConstructionParameters* constructionParameters, RunParameters* runParameters, G4RunManager* runMan,
    G4double minScale, G4double maxScale, G4double stepScale) {

    G4int noScales = (maxScale - minScale) / stepScale;
    G4cout << "Number of scales per field type: " << noScales << G4endl;
    int curRun = -1;
    G4int choiceParticle = -1;
    double ratio = -1;
    G4String fileNames[5] = { "BDipole", "BNeon", "BSolenoid", "BTarget", "E" };
    G4String fileNameWalls, fileNameParameters;


    G4double scaleBDipole = -1.;
    G4double scaleBNeon = -1.;
    G4double scaleBSolenoid = -1.;
    G4double scaleBTarget = -1.;
    G4double scaleE = -1.;

    for (int i = 0; i < 5; ++i) {       // for every field
        for (curRun = 0; curRun < noScales; ++curRun) {   // for every scale
            scaleBDipole = 1.;
            scaleBNeon = 1.;
            scaleBSolenoid = 1.;
            scaleBTarget = 1.;
            scaleE = 1.;

            fileNameWalls = "testField" + fileNames[i] + "scaleRun" + std::to_string(curRun) + ".csv";
            fileNameParameters = "testFieldParameters" + fileNames[i] + "scaleRun" + std::to_string(curRun) + ".csv";

            G4cout << "Current field type: " << fileNames[i] << G4endl;
            G4cout << "Current scaling: " << minScale + curRun * stepScale << G4endl;
            switch (i) {
            case 0:
                scaleBDipole = minScale + curRun * stepScale;
                constructionParameters->SetScaleAll(scaleBDipole, scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE);
                constructionParameters->StoreParameters(curRun, fileNameParameters);
                break;
            case 1:
                scaleBNeon = minScale + curRun * stepScale;
                constructionParameters->SetScaleAll(scaleBDipole, scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE);
                constructionParameters->StoreParameters(curRun, fileNameParameters);
                break;
            case 2:
                scaleBSolenoid = minScale + curRun * stepScale;
                constructionParameters->SetScaleAll(scaleBDipole, scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE);
                constructionParameters->StoreParameters(curRun, fileNameParameters);
                break;
            case 3:
                scaleBTarget = minScale + curRun * stepScale;
                constructionParameters->SetScaleAll(scaleBDipole, scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE);
                constructionParameters->StoreParameters(curRun, fileNameParameters);
                break;
            case 4:
                scaleE = minScale + curRun * stepScale;
                constructionParameters->SetScaleAll(scaleBDipole, scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE);
                constructionParameters->StoreParameters(curRun, fileNameParameters);
                break;
            }
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