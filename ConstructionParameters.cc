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

void ConstructionParameters::StoreParameters(G4int runNumber) {

    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->SetVerboseLevel(0);

    // Parameters
    man->CreateNtuple("Title3", "Title4");
    man->CreateNtupleDColumn("distTarMod ");
    man->CreateNtupleDColumn("dModerator");
    man->CreateNtupleDColumn("empty");
    man->CreateNtupleDColumn("avgEnergy");

    man->CreateNtupleDColumn("distTargetOrigin (real geometry)");
    man->CreateNtupleDColumn("moderator height");

    man->CreateNtupleDColumn("scaling of Dipole B-field");
    man->CreateNtupleDColumn("scaling of Neon B-field");
    man->CreateNtupleDColumn("scaling of Solenoid B-field");
    man->CreateNtupleDColumn("scaling of Target B-field");
    man->CreateNtupleDColumn("scaling of E-field");

    man->FinishNtuple(1);


    std::stringstream strRunID;
    strRunID << runNumber;

    G4String fileName = "ConstructionParameters" + strRunID.str() + ".csv";
    man->OpenFile(fileNameParameters);

    man->AddNtupleRow(1);
    man->Write();
    man->CloseFile();

}