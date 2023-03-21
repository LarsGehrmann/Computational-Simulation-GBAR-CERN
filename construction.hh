#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH



#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4SubtractionSolid.hh"

#include "globals.hh"


#include "G4Cache.hh"


#include "G4MagneticField.hh"
#include "G4ElectricField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

//#include "magneticField.hh"
//#include "electricField.hh"
#include "globalField.hh"

#include "G4AnalysisManager.hh"


#include "G4Run.hh"
#include "detector.hh"

#include "CADMesh-master/CADMesh.hh"



class globalField;


class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
     MyDetectorConstruction(G4double argdModerator, G4double argdModeratorFront, G4double argDistTarMod, G4double argDistTargetOrigin, 
         G4int argChoiceGeometry, G4double argWidthModeratorPart, G4double argModeratorHeight, G4double argScaleBDipole, G4double argScaleBNeon, 
         G4double argScaleBSolenoid, G4double argScaleBTarget, G4double argScaleE);
	//MyDetectorConstruction(G4double distGunTar, G4double distTarMod, G4double dModerator);  // constructor with parameters
	~MyDetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField() override;
private:
    G4int choiceGeometry;
    G4double dModerator, dModeratorEnd, dModeratorFront, distTarMod, distTargetOrigin, moderatorHeight;
    G4double scaleBDipole, scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE;

    G4AnalysisManager* man;
    G4GenericMessenger* fMessenger;
    void DefineMaterials();
    void SetMaterials();
    G4String moderatorMaterialMessenger = "Tungsten";
    G4String outputNameParameters;
    //parameters to change
    G4double distGunTar; // are global now lol , distTarMod, dModerator;
    // static parameters
    G4double rTargetOut, dTargetOut, rTargetIn, dEffectiveTarget, dTargetIn, lengthModerator, widthModerator, widthModeratorPart, worldVertices,
        heightWorld, lengthWorld, widthWorld;      
    G4Box* solidWorld, * solidModerator, * solidModeratorEnd, *solidModeratorFront;
    G4Tubs* solidTargetOut, * solidTargetIn;
    G4SubtractionSolid *solidTarget;
    G4VSolid *coilsSolid, *electrodeSolid, *solenoidSolid, *tarSolid,  *modSolid, *sampleWallSolid;

    G4RotationMatrix * RotationTarget, * RotationModerator;
    G4ThreeVector zTrans;
    // materials
    G4Material* worldMat, * targetMaterial, * moderatorMaterial, * moderatorEndMaterial, * coilsMaterial;
    // G4Elements and G4Materials
    G4Element * elNe, * elH, * elW;
    G4Material  * Ne, * H2, * W;
    // logical volumes
    G4LogicalVolume *logicTarget, *logicModerator, *logicModeratorEnd, *logicModeratorFront, *logicWorld, *logicCoils, *logicElectrode, *logicSolenoid, *logicTar, 
        *logicMod, *logicSampleWall;
    // physical volumes
    G4VPhysicalVolume *physicalTarget, *physicalModerator, *physicalModeratorEnd, *physicalModeratorFront, *physicalWorld, *physicalCoils, *physicalElectrode, 
        *physicalSolenoid, *physicalTar, *physicalMod, *physicalSampleWall;
    // sensitive detector
    //MySensitiveDetector *sensDetModerator, *sensDetModeratorEnd, *sensDetSampleWall;

    G4MagneticField* magField;
    G4FieldManager* magFieldMgr;

    G4ElectricField* elField;
    G4FieldManager* elFieldMgr;

    G4Cache<globalField*> fFieldSetUp;

    G4bool placeBehind;
    G4double angleToAxis;
    G4double angleOfModerator;


};
#endif