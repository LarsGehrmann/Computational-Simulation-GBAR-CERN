#ifndef RUNPARAMETERS_HH
#define RUNPARAMETERS_HH

#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4AnalysisManager.hh"

class RunParameters
{
public:
    RunParameters(G4int argNoEvents, G4int argChoiceParticle, G4int argChoiceGeometry, G4double argDistTargetOrigin, G4double argAvgE, G4double argDModeratorTotal, G4double argDistTarMod, 
        G4String argFileName);
	~RunParameters();

    G4int GetNoEvents();
    G4int GetChoiceParticle();
    G4int GetChoiceGeometry();
    G4double GetDistTargetOrigin();
    G4double GetAvgE();
    G4double GetDModeratorTotal();
    G4double GetDistTarMod();
    G4String GetFileName();

    void SetNoEvents(G4int argNoEvents);
    void SetChoiceParticle(G4int argChoiceParticle);
    void SetChoiceGeometry(G4int argChoiceGeometry);
    void SetDModeratorTotal(G4double argDModeratorTotal);
    void SetDistTargetOrigin(G4double argDistTargetOrigin);
    void SetFileName(G4String argFilename);


private:
    G4int noEvents, choiceParticle, choiceGeometry;
    G4double distTargetOrigin, avgE, dModeratorTotal, distTarMod;
    G4String fileName;
};

#endif
