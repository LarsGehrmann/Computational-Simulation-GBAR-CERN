#include "testFields.hh"


void testDistancesTargetOrigin(ConstructionParameters* constructionParameters, RunParameters* runParameters, G4RunManager* runMan,
    G4double minDist, G4double maxDist, G4double stepDist, G4int noDist) {

   // G4int noDist = (maxDist - minDist) / stepDist;
    G4cout << "Number of distances: " << noDist << G4endl;
    int curRun = -1;
    G4int choiceParticle = -1;
    G4String fileNameWalls, fileNameParameters;
    G4double distTargetOrigin = -1 * cm;
    for (curRun = 0; curRun < noDist; ++curRun) {   // for every distance
        fileNameWalls = "testDistances" + std::to_string(curRun) + ".csv";
        fileNameParameters = "testDistancesParameters" + std::to_string(curRun) + ".csv";
        distTargetOrigin = minDist + curRun * stepDist;
        constructionParameters->SetDistTargetOrigin(distTargetOrigin);
        runParameters->SetDistTargetOrigin(distTargetOrigin);
        constructionParameters->StoreParameters(curRun, fileNameParameters);
        G4cout << "Current distance: " << distTargetOrigin << G4endl;
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