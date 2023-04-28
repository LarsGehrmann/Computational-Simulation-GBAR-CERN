#ifndef CONSTRUCTIONPARAMETERS_HH
#define CONSTRUCTIONPARAMETERS_HH

#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4AnalysisManager.hh"



class ConstructionParameters
{
public:
	ConstructionParameters(G4int choiceGeometry, G4double argDModeratorTotal, G4double argDModeratorFront, G4double argWidthModeratorPart, 
        G4double argDistTargetOrigin, G4double moderatorHeight, G4double scaleBDipole, G4double scaleBNeon, 
        G4double scaleBSolenoid, G4double scaleBTarget, G4double scaleE, G4String moderatorMaterial); // regular constructor
    ConstructionParameters(ConstructionParameters &toCopy); // copy constructor


	~ConstructionParameters();

    void StoreParameters(int runNumber);
    void StoreParameters(int runNumber, G4String argFileName);


    G4int GetChoiceGeometry();
    G4double GetDModeratorTotal();
    G4double GetDModeratorFront();
    G4double GetWidthModerator();
    G4double GetDistTargetOrigin();
    G4double GetModeratorHeight();
    G4double GetScaleBDipole();
    G4double GetScaleBNeon();
    G4double GetScaleBSolenoid();
    G4double GetScaleBTarget();
    G4double GetScaleE();
    G4String GetModeratorMaterial();

    void SetDModeratorTotal(G4double argDModeratorTotal);
    void SetDModeratorFront(G4double argDModeratorFront);
    void SetWidthModerator(G4double argWidthModerator);
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
    G4double dModeratorTotal, dModeratorFront, widthModerator, distTargetOrigin, moderatorHeight, scaleBDipole,
        scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE;
    G4String moderatorMaterial;
};

#endif
