#include "ConstructionParameters.hh"


ConstructionParameters::ConstructionParameters(G4int argChoiceGeometry, G4double argDModerator, G4double argDModeratorFront,
    G4double argWidthModeratorPart, G4double argDistTargetOrigin,

    G4double argModeratorHeight, G4double argScaleBDipole,
    G4double argScaleBNeon, G4double argScaleBSolenoid, G4double argScaleBTarget, G4double argScaleE)
    :
    choiceGeometry(argChoiceGeometry), dModerator(argDModerator), dModeratorFront(argDModeratorFront),
    widthModeratorPart(argWidthModeratorPart), distTargetOrigin(argDistTargetOrigin), moderatorHeight(argModeratorHeight),
    scaleBDipole(argScaleBDipole), scaleBNeon(argScaleBNeon), scaleBSolenoid(argScaleBSolenoid),
    scaleBTarget(argScaleBTarget),
    scaleE(argScaleE)
{
    G4cout << "ConstructionParameters constructor called" << G4endl;
}

ConstructionParameters::~ConstructionParameters() {


}

ConstructionParameters::ConstructionParameters(ConstructionParameters &toCopy) {
    choiceGeometry = toCopy.GetChoiceGeometry();

}

G4int ConstructionParameters::GetChoiceGeometry() {
    return choiceGeometry;
}
G4double ConstructionParameters::GetDModerator() {
    return dModerator;
}

G4double ConstructionParameters::GetDModeratorFront() {
    return dModeratorFront;
}
G4double ConstructionParameters::GetWidthModeratorPart() {
    return widthModeratorPart;
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

void ConstructionParameters::SetDModerator(G4double argDModerator) {
    dModerator = argDModerator;
}
void ConstructionParameters::SetDModeratorFront(G4double argDModeratorFront) {
    dModeratorFront = argDModeratorFront;
}


void ConstructionParameters::SetWidthModeratorPart(G4double argWidthModeratorPart) {
    widthModeratorPart = argWidthModeratorPart;
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
void ConstructionParameters::SetModeratorMaterial(G4String argModeratorMaterial) {
    moderatorMaterial = argModeratorMaterial;
}


void ConstructionParameters::StoreParameters(int runNumber) {

    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->SetVerboseLevel(0);

    std::stringstream strRunID;
    strRunID << runNumber;

    G4String fileName = "ConstructionParameters" + strRunID.str() + ".csv";
    G4String tupleName = "Construction Parameters";
    //tupleName = "";
    


    if (runNumber == 0) {
    // Create tuples
    man->CreateNtuple(tupleName,tupleName);
    man->CreateNtupleDColumn(0,"choiceGeometry");
    man->CreateNtupleDColumn(0, "dModerator");
    man->CreateNtupleDColumn(0, "dModeratorFront");
    man->CreateNtupleDColumn(0, "distTargetOrigin");
    man->CreateNtupleDColumn(0, "moderatorHeight");
    man->CreateNtupleDColumn(0, "scaling of Dipole B-field");
    man->CreateNtupleDColumn(0, "scaling of Neon B-field");
    man->CreateNtupleDColumn(0, "scaling of Solenoid B-field");
    man->CreateNtupleDColumn(0, "scaling of Target B-field");
    man->CreateNtupleDColumn(0, "scaling of E-field");
    man->FinishNtuple(0);   
    }

    man->OpenFile(fileName);


    man->FillNtupleDColumn(0, 0, choiceGeometry);
    man->FillNtupleDColumn(0, 1, dModerator);
    man->FillNtupleDColumn(0, 2, dModeratorFront);
    man->FillNtupleDColumn(0, 3, distTargetOrigin);
    man->FillNtupleDColumn(0, 4, scaleBDipole);
    man->FillNtupleDColumn(0, 5, scaleBNeon);
    man->FillNtupleDColumn(0, 6, scaleBSolenoid);
    man->FillNtupleDColumn(0, 7, scaleBTarget);
    man->FillNtupleDColumn(0, 8, scaleE);
    man->AddNtupleRow(0);

    man->Write();
    man->CloseFile();

}