#ifndef CONSTRUCTIONPARAMETERS_HH
#define CONSTRUCTIONPARAMETERS_HH

#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4AnalysisManager.hh"



class ConstructionParameters
{
public:
	ConstructionParameters(G4int choiceGeometry, G4double argDModerator, G4double argDModeratorFront, G4double argWidthModeratorPart, 
        G4double argDistTargetOrigin, G4double moderatorHeight, G4double scaleBDipole, G4double scaleBNeon, 
        G4double scaleBSolenoid, G4double scaleBTarget, G4double scaleE); // regular constructor
    ConstructionParameters(ConstructionParameters &toCopy); // copy constructor


	~ConstructionParameters();

    void StoreParameters(G4int runNumber);

    G4int GetChoiceGeometry();

    G4double GetDModerator();
    G4double GetDModeratorFront();
    G4double GetWidthModeratorPart();
    G4double GetDistTargetOrigin();
    G4double GetModeratorHeight();
    G4double GetScaleBDipole();
    G4double GetScaleBNeon();
    G4double GetScaleBSolenoid();
    G4double GetScaleBTarget();
    G4double GetScaleE();
    G4String GetModeratorMaterial();

private:
    G4int choiceGeometry, dModerator, dModeratorFront, widthModeratorPart, distTargetOrigin, moderatorHeight, scaleBDipole,
        scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE;
    G4String moderatorMaterial;
};

#endif
