
#ifndef CONSTRUCTIONTEST_HH
#define CONSTRUCTIONTEST_HH



#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
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

#include "globalField.hh"

#include "G4AnalysisManager.hh"


#include "G4Run.hh"
#include "detector.hh"

#include "CADMesh-master/CADMesh.hh"

#include "ConstructionParameters.hh"



class globalField;
class ConstructionParameters;


class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
     DetectorConstruction(ConstructionParameters *argConstructionParameters);
	~DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField() override;
private:
    ConstructionParameters* constructionParameters;
    //G4AnalysisManager* man;
    void DefineMaterials();
    void SetMaterials();
    //parameters to change
    // static parameters
    /*
    G4double rTargetOut, dTargetOut, rTargetIn, dEffectiveTarget, dTargetIn, lengthModerator, widthModerator, widthModeratorPart, worldVertices,
        heightWorld, lengthWorld, widthWorld;      
        */
    G4Box* solidWorld, * solidModerator, * solidModeratorEnd, *solidModeratorFront;
    G4Tubs* solidTargetOut, * solidTargetIn;
    G4SubtractionSolid *solidTarget;
    G4VSolid *coilsSolid, *electrodeSolid, *solenoidSolid, *tarSolid,  *modSolid, *sampleWallSolid, * sampleWallSolid4;

    G4RotationMatrix * RotationTarget, * RotationModerator, * RotationSampleWall2, * RotationSampleWall3, * RotationSampleWall4;
    G4ThreeVector zTrans;
    // materials
    G4Material* worldMat, * targetMaterial, * moderatorMaterial, * moderatorEndMaterial, * coilsMaterial;
    // G4Elements and G4Materials
    G4Element * elNe, * elH, * elW;
    G4Material  * Ne, * H2, * W;
    // logical volumes
    G4LogicalVolume *logicTarget, *logicModerator, *logicModeratorEnd, *logicModeratorFront, *logicWorld, *logicCoils, *logicElectrode, *logicSolenoid, *logicTar, 
        *logicMod, *logicSampleWall, * logicSampleWall0, * logicSampleWall1, * logicSampleWall2, * logicSampleWall3, * logicSampleWall4;
    // physical volumes
    G4VPhysicalVolume *physicalTarget, *physicalModerator, *physicalModeratorEnd, *physicalModeratorFront, *physicalWorld, *physicalCoils, *physicalElectrode, 
        *physicalSolenoid, *physicalTar, *physicalMod, *physicalSampleWall, * physicalSampleWall0, * physicalSampleWall1, * physicalSampleWall2, * physicalSampleWall3, * physicalSampleWall4;
    // sensitive detector
    //MySensitiveDetector *sensDetModerator, *sensDetModeratorEnd, *sensDetSampleWall;

    G4MagneticField* magField;
    G4FieldManager* magFieldMgr;

    G4ElectricField* elField;
    G4FieldManager* elFieldMgr;

    G4Cache<globalField*> fFieldSetUp;


};
#endif
