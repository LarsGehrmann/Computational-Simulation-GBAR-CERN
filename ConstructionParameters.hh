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

    void StoreParameters(int runNumber);
    void StoreParameters(int runNumber, G4String argFileName);


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

    void SetDModerator(G4double argDModerator);
    void SetDModeratorFront(G4double argDModeratorFront);
    void SetWidthModeratorPart(G4double argWidthModeratorPart);
    void SetDistTargetOrigin(G4double argDistTargetOrigin);
    void SetModeratorHeight(G4double argModeratorHeight);
    void SetScaleBDipole(G4double argScaleBDipole);
    void SetScaleBNeon(G4double argScaleBNeon);
    void SetScaleBSolenoid(G4double argScaleBSolenoid);
    void SetScaleBTarget(G4double argScaleBTarget);
    void SetScaleE(G4double argScaleE);
    void SetScaleAll(G4double argScaleBDipole, G4double argScaleBNeon, G4double argScaleBSolenoid, G4double argScaleBTarget, G4double argScaleE);
    void SetModeratorMaterial(G4String argModeratorMaterial);


private:
    G4int choiceGeometry;
    G4double dModerator, dModeratorFront, widthModeratorPart, distTargetOrigin, moderatorHeight, scaleBDipole,
        scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE;
    G4String moderatorMaterial;
};

#endif
