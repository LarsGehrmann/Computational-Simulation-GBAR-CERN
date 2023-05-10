#include "RunParameters.hh"


RunParameters::RunParameters(G4int argNoEvents, G4int argChoiceParticle, G4int argChoiceGeometry, G4double argDistTargetOrigin, G4double argAvgE, G4double argDModeratorTotal, 
    G4double argDistTarMod, G4String argFileName)
    :
    noEvents(argNoEvents), choiceParticle(argChoiceParticle), choiceGeometry(argChoiceGeometry), distTargetOrigin(argDistTargetOrigin), avgE(argAvgE), 
    dModeratorTotal(argDModeratorTotal), distTarMod(argDistTarMod), fileName(argFileName)
{
}

RunParameters::~RunParameters() {
}

G4int RunParameters::GetNoEvents() {
    return noEvents;
}
G4int RunParameters::GetChoiceParticle() {
    return choiceParticle;
}
G4int RunParameters::GetChoiceGeometry() {
    return choiceGeometry;
}
G4double RunParameters::GetDistTargetOrigin() {
    return distTargetOrigin;
}
G4double RunParameters::GetAvgE() {
    return avgE;
}
G4double RunParameters::GetDModeratorTotal() {
    return dModeratorTotal;
}
G4double RunParameters::GetDistTarMod() {
    return distTarMod;
}
G4String RunParameters::GetFileName() {
    return fileName;
}

void RunParameters::SetNoEvents(int argNoEvents) {
    noEvents = argNoEvents;
}
void RunParameters::SetChoiceParticle(int argChoiceParticle) {
    choiceParticle = argChoiceParticle;
}
void RunParameters::SetChoiceGeometry(int argChoiceGeometry) {
    choiceGeometry = argChoiceGeometry;
}
void RunParameters::SetDModeratorTotal(G4double argDModeratorTotal) {
    dModeratorTotal = argDModeratorTotal;
}
void RunParameters::SetFileName(G4String argFileName) {
    fileName = argFileName;
}
