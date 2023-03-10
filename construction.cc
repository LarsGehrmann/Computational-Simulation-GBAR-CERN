#include "construction.hh"

#include "Randomize.hh"

#include "G4AutoDelete.hh"
#include "globalField.hh"


MyDetectorConstruction::MyDetectorConstruction()        // default construtor
{

    outputNameParameters = "OutputParameters";
    distGunTar = 10 * mm;
    distTarMod = 2 * mm;
    distTarMod = 200 * mm; //

    dModerator = 0.15 * mm; 
    dModeratorEnd = 0.05 * mm;

    //dModerator = 150 * mm; // 
    //dModeratorEnd = 50 * mm; //

    moderatorMaterialMessenger = "Tungsten";

    placeBehind = true;
    placeBehind = false; //

    angleToAxis = 0 * deg;
    angleToAxis = 20 * deg;  //
    angleOfModerator = 0 * deg;

   fMessenger = new G4GenericMessenger(this, "/detector/", "Detector construction");


    //fMessenger = new G4GenericMessenger(this, "/outputRun/", "Name of output file for RunAction");
    fMessenger->DeclareProperty("outputNameParameters", outputNameParameters, "Name of the output file with parameters");
    fMessenger->DeclareProperty("moderatorMaterialMessenger", moderatorMaterialMessenger, "Material of moderator");
    fMessenger->DeclareProperty("distGunTar", distGunTar, "Distance between electron source and target");
    fMessenger->DeclareProperty("distTarMod", distTarMod, "Distance between target and moderator");
    fMessenger->DeclareProperty("dModerator", dModerator, "Thickness of moderator");
    fMessenger->DeclareProperty("placeBehind", placeBehind, "Place moderator right behind the target as in the naive way");
    fMessenger->DeclareProperty("angleToAxis", angleToAxis, "Angle to the x-axis to the normal of the moderator");
    fMessenger->DeclareProperty("angleOfModerator", angleOfModerator, "Angle of the rotation of the moderator, 0 is naive approach");
    fMessenger->DeclareProperty("dModeratorEnd", dModeratorEnd, "Thickness of end of moderator");

    MyDetectorConstruction::DefineMaterials();

}

void MyDetectorConstruction::DefineMaterials()
{
    G4NistManager* nist = G4NistManager::Instance();

    // Define world material H2
    G4double a = 1.01 * g / mole;
    elH = new G4Element("Hydrogen", "H", 1, a);
    G4double density = 4 * pow(10,-15) * g / cm3;
    H2 = new G4Material("Hydrogen-molecule", density, 1);
    H2->AddElement(elH, 2);

    // Define solid neon
    a = 20.18 * g / mole;
    elNe = new G4Element("Neon", "Ne", 10, a);
    density = 0.9 * g / cm3;
    Ne = new G4Material("Solid neon", density, 1);
    Ne->AddElement(elNe, 1);

    // Define tungsten
    a = 183.84 * g / mole;
    elW = new G4Element("Tungsten", "W", 74, a);
    density = 19.28 * g / cm3;
    W = new G4Material("Tungsten", density, 1);
    W->AddElement(elW, 1);
}


MyDetectorConstruction::~MyDetectorConstruction()   // destructor
{}


void MyDetectorConstruction::SetMaterials()
{


    
    G4NistManager* nist = G4NistManager::Instance();
    // Set target, moderator and world material
    targetMaterial = nist->FindOrBuildMaterial("G4_W");
    worldMat = H2;
    coilsMaterial = nist->FindOrBuildMaterial("G4_Cu");

    if (moderatorMaterialMessenger == "Neon") {
        G4cout << "Neon as material" << G4endl;
        moderatorMaterial = Ne;
        moderatorEndMaterial = Ne;
    }
    else if (moderatorMaterialMessenger == "Tungsten") {
        G4cout << "Tungsten as material" << G4endl;
        moderatorMaterial = W;
        moderatorEndMaterial = W;
    }
    else if (moderatorMaterialMessenger == "Copper") {
        moderatorMaterial = nist->FindOrBuildMaterial("G4_Cu");
        moderatorEndMaterial = nist->FindOrBuildMaterial("G4_Cu");

    }
    else {
        G4cout << "Tungsten as default material" << G4endl;
        moderatorMaterial = W;
        moderatorEndMaterial = W;
    }
}


G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    // choiceGeometry determines geometric setup:
    // 0 custom geometry
    // 1 COMSOL geometry
    G4int choice = 0;
    MyDetectorConstruction::SetMaterials();


    worldVertices = 1000 * mm; // world length
    heightWorld = worldVertices;
    lengthWorld = worldVertices;
    widthWorld = worldVertices;
    solidWorld = new G4Box("soldidWorld", lengthWorld, heightWorld, widthWorld);
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicVWorld");
    physicalWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physicalWorld", 0, false, 0, true);




    auto meshCoils = CADMesh::TessellatedMesh::FromSTL("coils.stl");
    meshCoils->SetScale(1000.0);
    coilsSolid = meshCoils->GetSolid();
    logicCoils = new G4LogicalVolume(coilsSolid, coilsMaterial, "logicCoils");
    physicalCoils = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicCoils, "physicalCoils", logicWorld, false, 5, true);

    auto meshElectrode = CADMesh::TessellatedMesh::FromSTL("electrode.stl");
    meshElectrode->SetScale(1000.0);
    electrodeSolid = meshElectrode->GetSolid();
    logicElectrode = new G4LogicalVolume(electrodeSolid, coilsMaterial, "logicElectrode");
    physicalElectrode = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicElectrode, "physicalElectrode", logicWorld, false, 6, true);

    auto meshSolenoid = CADMesh::TessellatedMesh::FromSTL("solenoid.stl");
    meshSolenoid->SetScale(1000.0);
    solenoidSolid = meshSolenoid->GetSolid();
    logicSolenoid = new G4LogicalVolume(solenoidSolid, coilsMaterial, "logicSolenoid");
    physicalSolenoid = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicSolenoid, "physicalSolenoid", logicWorld, false, 7, true);


    switch (choiceGeometry) {
    case 0:        lengthModerator = 19 * mm;
        widthModerator = 19 * mm;
        // define two cylinders outer and inner and take boolean geometry, subtraction solid
        rTargetOut = 95 * mm; // radius of target (outer)
        dTargetOut = 10 * mm;
        dTargetIn = dTargetOut - dEffectiveTarget;

        rTargetIn = 2.5 * mm; // radius of target (inner)
        dEffectiveTarget = 1 * mm; // thickness of leftover target after cutting
        // Create a RotationTarget, matrix that rotates the Target
        RotationTarget = new G4RotationMatrix();
        RotationTarget->rotateX(0 * deg);
        RotationTarget->rotateY(90 * deg);
        RotationTarget->rotateZ(0 * deg);

        // translate inner cylinder of target
        zTrans.setX(0.);
        zTrans.setY(0.);
        zTrans.setZ(dEffectiveTarget / 2);
        G4cout << "HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << G4endl;
        solidTargetOut = new G4Tubs("solidTargetOut", 0., rTargetOut, dTargetOut / 2, 0, 360);
        G4cout << "HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << G4endl;

        solidTargetIn = new G4Tubs("solidTargetIn", 0., rTargetIn, dTargetIn / 2, 0, 360);
        G4cout << "HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << G4endl;

        solidTarget = new G4SubtractionSolid("solidTarget", solidTargetOut, solidTargetIn, 0, zTrans);

        logicTarget = new G4LogicalVolume(solidTarget, targetMaterial, "logicVTarget");
        physicalTarget = new G4PVPlacement(RotationTarget, G4ThreeVector(distTargetOrigin + dTargetOut / 2, 0., 0.), logicTarget, "physicalTarget", logicWorld, false, 1, true);

        solidModerator = new G4Box("solidModerator", dModerator / 2, lengthModerator / 2, widthModerator / 2);
        solidModeratorEnd = new G4Box("solidModeratorEnd", dModeratorEnd / 2, lengthModerator / 2, widthModerator / 2);
        logicModerator = new G4LogicalVolume(solidModerator, moderatorMaterial, "logicVModerator");
        logicModeratorEnd = new G4LogicalVolume(solidModeratorEnd, moderatorEndMaterial, "logicVModeratorEnd");
        physicalModerator = new G4PVPlacement(0, G4ThreeVector(0, 60 * cm + dModerator / 2, 0), logicModerator, "physicalModerator", logicWorld, false, 2, true);
        physicalModeratorEnd = new G4PVPlacement(0, G4ThreeVector(0, 60 * cm + dModerator + dModeratorEnd/2, 0), logicModeratorEnd, "physicalModeratorEnd", logicWorld, false, 3, true);

        break;
    case 1:
        auto meshMod = CADMesh::TessellatedMesh::FromSTL("mod.stl");
        meshMod->SetScale(1000.0);
        modSolid = meshMod->GetSolid();
        logicMod = new G4LogicalVolume(modSolid, coilsMaterial, "logicMod");
        physicalMod = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicMod, "physicalMod", logicWorld, false, 9, true);

        auto meshTar = CADMesh::TessellatedMesh::FromSTL("Target.stl");
        meshTar->SetScale(1000.0);
        tarSolid = meshTar->GetSolid();
        logicTar = new G4LogicalVolume(tarSolid, coilsMaterial, "logicTar");
        physicalSolenoid = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicTar, "physicalTar", logicWorld, false, 8, true);

        break;
    }
	return physicalWorld;
}

void MyDetectorConstruction::ConstructSDandField() {

    if (choiceGeometry == 0) {
        sensDetModerator = new MySensitiveDetector("dModeratorSensDet");
        sensDetModeratorEnd = new MySensitiveDetector("dModeratorEndSensDet");
        logicModerator->SetSensitiveDetector(sensDetModerator);
        logicModeratorEnd->SetSensitiveDetector(sensDetModeratorEnd);
    }
    globalField* globField = new globalField();
    G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
    fieldMgr->SetDetectorField(globField);
    G4ChordFinder* chordFinder = globField->getChordFinder();
    fieldMgr->SetChordFinder(chordFinder);
}

/*

if (!placeBehind) {  // approach, where moderator is rotated and magnetic field is used to separate e+ and e-
    physicalModerator = new G4PVPlacement(RotationModerator,
        G4ThreeVector( distGunTar + dTargetOut + (distTarMod + dModerator / 2)  * cos(angleToAxis),
        0., (distTarMod + dModerator / 2) * sin(angleToAxis) ), logicModerator,
        "physicalModerator", logicWorld, false, 2, true);
    physicalModeratorEnd = new G4PVPlacement(RotationModerator,
        G4ThreeVector(distGunTar + dTargetOut + (distTarMod + dModerator + dModeratorEnd / 2) * cos(angleToAxis),
        0., (distTarMod + dModerator + dModeratorEnd / 2) * sin(angleToAxis)), logicModeratorEnd,
        "physicalModeratorEnd", logicWorld, false, 3, true);

}
else {  // naive approach, placing moderator right behind the target as it is in the current setup
    physicalModerator = new G4PVPlacement(0, G4ThreeVector(distGunTar + dTargetOut + distTarMod + dModerator / 2, 0., 0.), logicModerator, "physicalModerator", logicWorld, false, 2, true);
    physicalModeratorEnd = new G4PVPlacement(0, G4ThreeVector(distGunTar + dTargetOut + distTarMod + dModerator + dModeratorEnd / 2, 0., 0.), logicModeratorEnd, "physicalModeratorEnd", logicWorld, false, 3, true);
}
*/

/*
if (!fFieldSetUp.Get()) {
    globalField* field = globalField::GetObject(this);
    G4AutoDelete::Register(field);  // Kernel will delete the F04GlobalField
    fFieldSetUp.Put(field);
}
*/

/*
elField = new MyElectricField();
elFieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
elFieldMgr->SetDetectorField(elField);
//elFieldMgr->CreateChordFinder(elField);

magField = new MyMagneticField();
magFieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
magFieldMgr->SetDetectorField(magField);
magFieldMgr->CreateChordFinder(magField);

*/
/*
G4double point[4];
G4double field[6];
point[0] = 50 * cm;
point[1] = 0;
point[2] = 0;
point[3] = 0;
globField->GetFieldValue(point, field);
G4cout << "HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << G4endl;
G4cout << "Point: " << point[0] << ", " << point[1] << ", " << point[2] << "; Magnetic Field: " << field[0] << ", " << field[1] << ", " << field[2] << G4endl;
G4cout << "Point: " << point[0] << ", " << point[1] << ", " << point[2] << "; Electric Field: " << field[3] << ", " << field[4] << ", " << field[5] << G4endl;
*/