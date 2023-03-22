#include "construction.hh"
#include "Randomize.hh"
#include "G4AutoDelete.hh"
#include "globalField.hh"


MyDetectorConstruction::MyDetectorConstruction(G4double argdModerator, G4double argdModeratorFront, G4double argDistTarMod, 
    G4double argDistTargetOrigin, G4int argChoiceGeometry, G4double argWidthModeratorPart, G4double argModeratorHeight, G4double argScaleBDipole,
    G4double argScaleBNeon, G4double argScaleBSolenoid, G4double argScaleBTarget, G4double argScaleE)        // default construtor
{
    dModerator = argdModerator;
    dModeratorFront = argdModeratorFront;
    distTarMod = argDistTarMod;
    distTargetOrigin = argDistTargetOrigin;
    choiceGeometry = argChoiceGeometry;
    widthModeratorPart = argWidthModeratorPart;
    moderatorHeight = argModeratorHeight;

    scaleBDipole = argScaleBDipole;
    scaleBNeon = argScaleBNeon;
    scaleBSolenoid = argScaleBSolenoid;
    scaleBTarget = argScaleBTarget;
    scaleE = argScaleE;

    outputNameParameters = "OutputParameters";

   // moderatorMaterialMessenger = "Tungsten";

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
    MyDetectorConstruction::SetMaterials();

    worldVertices = 1000 * mm; // world length
    heightWorld = worldVertices;
    lengthWorld = worldVertices;
    widthWorld = worldVertices;
    solidWorld = new G4Box("soldidWorld", lengthWorld, heightWorld, widthWorld);
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicVWorld");
    physicalWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physicalWorld", 0, false, 0, true);

    G4double widthSampleWall = 50 * cm;
    G4double thicknessSampleWall = 0.001 * mm;

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
    case 0: {
        widthModerator = 19 * mm;
        widthModerator = 200 * mm;//
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
        solidTargetOut = new G4Tubs("solidTargetOut", 0., rTargetOut, dTargetOut / 2, 0, 360);
        solidTargetIn = new G4Tubs("solidTargetIn", 0., rTargetIn, dTargetIn / 2, 0, 360);
        solidTarget = new G4SubtractionSolid("solidTarget", solidTargetOut, solidTargetIn, 0, zTrans);
        logicTarget = new G4LogicalVolume(solidTarget, targetMaterial, "logicVTarget");
        physicalTarget = new G4PVPlacement(RotationTarget, G4ThreeVector(distTargetOrigin + dTargetOut / 2, 0., 0.), logicTarget, "physicalTarget", logicWorld, false, 1, true);

        solidModerator = new G4Box("solidModerator", widthModerator / 2, dModerator / 2, widthModerator / 2);
        solidModeratorEnd = new G4Box("solidModeratorEnd", widthModerator / 2, dModeratorEnd / 2, widthModerator / 2);
        //solidModerator = new G4Box("solidModerator", dModerator / 2, widthModerator / 2, widthModerator / 2);
        //solidModeratorEnd = new G4Box("solidModeratorEnd", dModeratorEnd / 2, widthModerator / 2, widthModerator / 2);

        logicModerator = new G4LogicalVolume(solidModerator, moderatorMaterial, "logicVModerator");
        logicModeratorEnd = new G4LogicalVolume(solidModeratorEnd, moderatorEndMaterial, "logicVModeratorEnd");

        G4cout << "Distance between target and origin: " << distTargetOrigin << G4endl;
        physicalModerator = new G4PVPlacement(0, G4ThreeVector(0, 60 * cm + dModerator / 2, 0), logicModerator, "physicalModerator", logicWorld, false, 2, true);
        physicalModeratorEnd = new G4PVPlacement(0, G4ThreeVector(0, 60 * cm + dModerator + dModeratorEnd / 2, 0), logicModeratorEnd, "physicalModeratorEnd", logicWorld, false, 3, true);
        //physicalModerator = new G4PVPlacement(0, G4ThreeVector(distTargetOrigin - dTargetOut - 2*mm - dModerator/2, 0., 0.), logicModerator, "physicalModerator", logicWorld, false, 2, true);
        //physicalModeratorEnd = new G4PVPlacement(0, G4ThreeVector(distTargetOrigin - dTargetOut - 2 * mm - dModerator - dModeratorEnd / 2, 0., 0.), logicModeratorEnd, "physicalModeratorEnd", logicWorld, false, 3, true);

        break;
    }
    case 1: {
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
    case 2: {
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
        solidTargetOut = new G4Tubs("solidTargetOut", 0., rTargetOut, dTargetOut / 2, 0, 360);
        solidTargetIn = new G4Tubs("solidTargetIn", 0., rTargetIn, dTargetIn / 2, 0, 360);
        solidTarget = new G4SubtractionSolid("solidTarget", solidTargetOut, solidTargetIn, 0, zTrans);
        logicTarget = new G4LogicalVolume(solidTarget, targetMaterial, "logicVTarget");
        physicalTarget = new G4PVPlacement(RotationTarget, G4ThreeVector(distTargetOrigin + dTargetOut / 2, 0., 0.), logicTarget, "physicalTarget", logicWorld, false, 1, true);

        solidModeratorFront = new G4Box("solidModerator", widthModeratorPart / 2, dModeratorFront / 2, widthModeratorPart / 2);
        solidModerator = new G4Box("solidModeratorEnd", widthModeratorPart / 2, dModerator / 2, widthModeratorPart / 2);
        logicModeratorFront = new G4LogicalVolume(solidModeratorFront, moderatorMaterial, "logicVModeratorFront");
        logicModerator = new G4LogicalVolume(solidModerator, moderatorMaterial, "logicVModerator");

        G4double x, z, dx, dz;
        G4double xStart = -10 * cm;
        G4double zStart = -10 * cm;
        dx = 1 * cm;
        dz = 1 * cm;
        x = xStart;
        z = zStart;

        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 20; ++j) {
                physicalModeratorFront = new G4PVPlacement(0, G4ThreeVector(x, moderatorHeight + dModeratorFront / 2, z), logicModeratorFront, "physicalModeratorFront", logicWorld, false, 1000 + i * 20 + j, true);
                physicalModerator = new G4PVPlacement(0, G4ThreeVector(x, moderatorHeight + dModeratorFront + dModerator/2, z), logicModerator, "physicalModerator", logicWorld, false, 2000 + i * 20 + j, true);
                z += dz;
            }
            z = zStart;
            x += dx;
        }

        break;
    }
    }
    sampleWallSolid = new G4Box("solidSampleWall", thicknessSampleWall / 2, widthSampleWall / 2, widthSampleWall / 2);
    logicSampleWall = new G4LogicalVolume(sampleWallSolid, worldMat, "logicVSampleWall");
    physicalSampleWall = new G4PVPlacement(0, G4ThreeVector(distTargetOrigin - 2 * cm, 0, 0), logicSampleWall, "physicalSampleWall", logicWorld, false, 10, true);

    sampleWallSolid4 = new G4Box("solidSampleWall4", thicknessSampleWall / 2, 20 / 2 * cm, 20 / 2 * cm);


    logicSampleWall1 = new G4LogicalVolume(sampleWallSolid, worldMat, "logicVSampleWall1");
    logicSampleWall2 = new G4LogicalVolume(sampleWallSolid, worldMat, "logicVSampleWall2");
    logicSampleWall3 = new G4LogicalVolume(sampleWallSolid, worldMat, "logicVSampleWall3");
    logicSampleWall4 = new G4LogicalVolume(sampleWallSolid4, worldMat, "logicVSampleWall4");

    RotationSampleWall2 = new G4RotationMatrix();
    RotationSampleWall2->rotateX(0 * deg);
    RotationSampleWall2->rotateY(0 * deg);
    RotationSampleWall2->rotateZ(45 * deg);

    RotationSampleWall3 = new G4RotationMatrix();
    RotationSampleWall3->rotateX(0 * deg);
    RotationSampleWall3->rotateY(0 * deg);
    RotationSampleWall3->rotateZ(90 * deg);

    physicalSampleWall1 = new G4PVPlacement(0, G4ThreeVector(25 * cm, 0, 0), logicSampleWall1, "physicalSampleWall1", logicWorld, false, 11, true);
    //physicalSampleWall1 = new G4PVPlacement(0, G4ThreeVector(distTargetOrigin - 2.01 * cm, 0, 0), logicSampleWall1, "physicalSampleWall1", logicWorld, false, 11, true);

    physicalSampleWall2 = new G4PVPlacement(RotationSampleWall2, G4ThreeVector(0, 0, 0), logicSampleWall2, "physicalSampleWall2", logicWorld, false, 12, true);
    physicalSampleWall3 = new G4PVPlacement(RotationSampleWall3, G4ThreeVector(0, 30 * cm, 0), logicSampleWall3, "physicalSampleWall3", logicWorld, false, 13, true);
    physicalSampleWall4 = new G4PVPlacement(RotationSampleWall3, G4ThreeVector(0, moderatorHeight - 0.00001 * cm, 0), logicSampleWall4, "physicalSampleWall4", logicWorld, false, 14, true);

    //ConstructSDandField();
	return physicalWorld;
}

void MyDetectorConstruction::ConstructSDandField() {

    /*
    if (choiceGeometry == 0) {
        sensDetModerator = new MySensitiveDetector("dModeratorSensDet");
        sensDetModeratorEnd = new MySensitiveDetector("dModeratorEndSensDet");
        logicModerator->SetSensitiveDetector(sensDetModerator);
        logicModeratorEnd->SetSensitiveDetector(sensDetModeratorEnd);
    }
    */
    /*
    if (choiceGeometry == 2) {
        sensDetSampleWall = new MySensitiveDetector("sampleWallSensDet");
        logicSampleWall->SetSensitiveDetector(sensDetSampleWall);
    }
    */
    globalField* globField = new globalField(scaleBDipole, scaleBNeon, scaleBSolenoid, scaleBTarget, scaleE);
    G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
    fieldMgr->SetDetectorField(globField);
    G4ChordFinder* chordFinder = globField->getChordFinder();
    fieldMgr->SetChordFinder(chordFinder);

    /*
    G4double x = -2 * cm;
    G4double y = -34 * cm;
    G4double z = -70 * cm;
    */
    G4double x = -22. * cm;
    G4double y = -76. * cm;
    G4double z = -64. * cm;
    G4double point[4] = { x,y,z,0 };
    G4double field[6] = { -1, -1, -1, -1, -1, -1 };
    globField->GetFieldValue(point, field);
    G4cout << "----------------------------------------------------------------------------------------------------------" << G4endl;
    G4cout << "----------------------------------------------------------------------------------------------------------" << G4endl;

    G4cout << "x,y,z: " << x << ", " << y << ", " << z << ";  Bx,By,Bz: " << field[0] << ", " << field[1] << ", " << field[2] << ";   Ex,Ey,Ez: "
        << field[3] << ", " << field[4] << ", " << field[5] << G4endl;
    G4cout << "----------------------------------------------------------------------------------------------------------" << G4endl;
    G4cout << "----------------------------------------------------------------------------------------------------------" << G4endl;

}