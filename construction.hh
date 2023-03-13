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

extern G4double dModerator;
extern G4double dModeratorEnd;
extern G4double distTarMod;
extern G4double distTargetOrigin;
extern G4int choiceGeometry;

class globalField;


class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
     MyDetectorConstruction();
	//MyDetectorConstruction(G4double distGunTar, G4double distTarMod, G4double dModerator);  // constructor with parameters
	~MyDetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField() override;
private:
    G4AnalysisManager* man;
    G4GenericMessenger* fMessenger;
    void DefineMaterials();
    void SetMaterials();
    G4String moderatorMaterialMessenger = "Tungsten";
    G4String outputNameParameters;
    //parameters to change
    G4double distGunTar; // are global now lol , distTarMod, dModerator;
    // static parameters
    G4double rTargetOut, dTargetOut, rTargetIn, dEffectiveTarget, dTargetIn, lengthModerator, widthModerator, worldVertices,
        heightWorld, lengthWorld, widthWorld;      
    G4Box* solidWorld, * solidModerator, * solidModeratorEnd;
    G4Tubs* solidTargetOut, * solidTargetIn;
    G4SubtractionSolid *solidTarget;
    G4VSolid* coilsSolid, *electrodeSolid, *solenoidSolid, *tarSolid,  *modSolid;

    G4RotationMatrix * RotationTarget, * RotationModerator;
    G4ThreeVector zTrans;
    // materials
    G4Material* worldMat, * targetMaterial, * moderatorMaterial, * moderatorEndMaterial, * coilsMaterial;
    // G4Elements and G4Materials
    G4Element * elNe, * elH, * elW;
    G4Material  * Ne, * H2, * W;
    // logical volumes
    G4LogicalVolume *logicTarget, *logicModerator, *logicModeratorEnd, *logicWorld, *logicCoils, *logicElectrode, *logicSolenoid, *logicTar, *logicMod;
    // physical volumes
    G4VPhysicalVolume *physicalTarget, *physicalModerator, *physicalModeratorEnd, *physicalWorld, *physicalCoils, *physicalElectrode, *physicalSolenoid, *physicalTar, *physicalMod;
    // sensitive detector
    MySensitiveDetector* sensDetModerator;
    MySensitiveDetector* sensDetModeratorEnd;

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