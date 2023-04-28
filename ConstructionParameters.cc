#include "ConstructionParameters.hh"


ConstructionParameters::ConstructionParameters(G4int argChoiceGeometry, G4double argDModeratorTotal, G4double argDModeratorFront,
    G4double argWidthModerator, G4double argDistTargetOrigin, G4double argModeratorHeight, G4double argScaleBDipole,
    G4double argScaleBNeon, G4double argScaleBSolenoid, G4double argScaleBTarget, G4double argScaleE, G4String argModeratorMaterial)
    :
    choiceGeometry(argChoiceGeometry), dModeratorTotal(argDModeratorTotal), dModeratorFront(argDModeratorFront),
    widthModerator(argWidthModerator), distTargetOrigin(argDistTargetOrigin), moderatorHeight(argModeratorHeight),
    scaleBDipole(argScaleBDipole), scaleBNeon(argScaleBNeon), scaleBSolenoid(argScaleBSolenoid),
    scaleBTarget(argScaleBTarget),
    scaleE(argScaleE), moderatorMaterial(argModeratorMaterial)
{
}

ConstructionParameters::~ConstructionParameters() {


}

ConstructionParameters::ConstructionParameters(ConstructionParameters &toCopy) {
    choiceGeometry = toCopy.GetChoiceGeometry();

}

G4int ConstructionParameters::GetChoiceGeometry() {
    return choiceGeometry;
}
G4double ConstructionParameters::GetDModeratorTotal() {
    return dModeratorTotal;
}

G4double ConstructionParameters::GetDModeratorFront() {
    return dModeratorFront;
}
G4double ConstructionParameters::GetWidthModerator() {
    return widthModerator;
}
G4double ConstructionParameters::GetDistTargetOrigin() {
    return distTargetOrigin;
}
G4double ConstructionParameters::GetModeratorHeight() {
    return moderatorHeight;
}
G4double ConstructionParameters::GetScaleBDipole() {
    return scaleBDipole;
}
G4double ConstructionParameters::GetScaleBNeon() {
    return scaleBNeon;
}
G4double ConstructionParameters::GetScaleBSolenoid() {
    return scaleBSolenoid;
}
G4double ConstructionParameters::GetScaleBTarget() {
    return scaleBTarget;
}
G4double ConstructionParameters::GetScaleE() {
    return scaleE;
}
G4String ConstructionParameters::GetModeratorMaterial() {
    return moderatorMaterial;
}

void ConstructionParameters::SetDModeratorTotal(G4double argDModeratorTotal) {
    dModeratorTotal = argDModeratorTotal;
}
void ConstructionParameters::SetDModeratorFront(G4double argDModeratorFront) {
    dModeratorFront = argDModeratorFront;
}


void ConstructionParameters::SetWidthModerator(G4double argWidthModerator) {
    widthModerator = argWidthModerator;
}
void ConstructionParameters::SetDistTargetOrigin(G4double argDistTargetOrigin) {
    distTargetOrigin = argDistTargetOrigin;
}
void ConstructionParameters::SetModeratorHeight(G4double argModeratorHeight) {
    moderatorHeight = argModeratorHeight;
}
void ConstructionParameters::SetScaleBDipole(G4double argScaleBDipole) {
    scaleBDipole = argScaleBDipole;
}
void ConstructionParameters::SetScaleBNeon(G4double argScaleBNeon) {
    scaleBNeon = argScaleBNeon;
}
void ConstructionParameters::SetScaleBSolenoid(G4double argScaleBSolenoid) {
    scaleBSolenoid = argScaleBSolenoid;
}
void ConstructionParameters::SetScaleBTarget(G4double argScaleBTarget) {
    scaleBTarget = argScaleBTarget;
}
void ConstructionParameters::SetScaleE(G4double argScaleE) {
    scaleE = argScaleE;
}
void ConstructionParameters::SetScaleAll(G4double argScaleBDipole, G4double argScaleBNeon, G4double argScaleBSolenoid,
    G4double argScaleBTarget, G4double argScaleE) {
    scaleBDipole = argScaleBDipole;
    scaleBNeon = argScaleBNeon;
    scaleBSolenoid = argScaleBSolenoid;
    scaleBTarget = argScaleBTarget;
    scaleE = argScaleE;
}
void ConstructionParameters::SetModeratorMaterial(G4String argModeratorMaterial) {
    moderatorMaterial = argModeratorMaterial;
}


void ConstructionParameters::StoreParameters(int runNumber) {

    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->SetVerboseLevel(0);

    std::stringstream strRunID;
    strRunID << runNumber;

    G4String fileName =  "Parameters" + strRunID.str() + ".csv";
    G4String tupleName = "Construction Parameters";
   
    man->OpenFile(fileName);

    man->FillNtupleDColumn(0, 0, choiceGeometry);
    man->FillNtupleDColumn(0, 1, dModeratorTotal);
    man->FillNtupleDColumn(0, 2, dModeratorFront);
    man->FillNtupleDColumn(0, 3, distTargetOrigin);
    man->FillNtupleDColumn(0, 4, moderatorHeight);
    man->FillNtupleDColumn(0, 5, scaleBDipole);
    man->FillNtupleDColumn(0, 6, scaleBNeon);
    man->FillNtupleDColumn(0, 7, scaleBSolenoid);
    man->FillNtupleDColumn(0, 8, scaleBTarget);
    man->FillNtupleDColumn(0, 9, scaleE);
    man->AddNtupleRow(0);

    man->Write();
    man->CloseFile();

}


void ConstructionParameters::StoreParameters(int runNumber, G4String argFileName) {

    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->SetVerboseLevel(0);

    std::stringstream strRunID;
    strRunID << runNumber;

    G4String fileName = argFileName;
    man->OpenFile(fileName);


    man->FillNtupleDColumn(0, 0, choiceGeometry);
    man->FillNtupleDColumn(0, 1, dModeratorTotal);
    man->FillNtupleDColumn(0, 2, dModeratorFront);
    man->FillNtupleDColumn(0, 3, distTargetOrigin);
    man->FillNtupleDColumn(0, 4, moderatorHeight);
    man->FillNtupleDColumn(0, 5, scaleBDipole);
    man->FillNtupleDColumn(0, 6, scaleBNeon);
    man->FillNtupleDColumn(0, 7, scaleBSolenoid);
    man->FillNtupleDColumn(0, 8, scaleBTarget);
    man->FillNtupleDColumn(0, 9, scaleE);
    man->AddNtupleRow(0);

    man->Write();
    man->CloseFile();

}