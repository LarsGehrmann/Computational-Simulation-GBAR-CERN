#include "generator.hh"
#include "Randomize.hh"




MyPrimaryGenerator::MyPrimaryGenerator(G4int argChoiceParticle, G4double argDistTargetOrigin, G4double argAvgE)
{	
	choiceParticle = argChoiceParticle;
	distTargetOrigin = argDistTargetOrigin;
	avgE = argAvgE;

	CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine);
	CLHEP::HepRandom::setTheSeed(time(NULL));
	//CLHEP::HepRandom::setTheSeed((unsigned)clock());
	fMessenger = new G4GenericMessenger(this, "/generator/", "Generator Messenger");
	fMessenger->DeclareProperty("avgE", avgE, "Average energy of the incident electrons");

	std::string fileName = "posTable.txt";
	std::fstream file(fileName);
	posTable = new double * [posNumber];
	for (int i = 0; i < posNumber; i++) {
		posTable[i] = new double[7];
	}

	double input;
	int modCount = 0;
	posCounter = 0;
	
	if (choiceParticle == 1) {
	while (file >> input)
	{	
		/*
		G4cout << "input: " << input << G4endl;
		G4cout << "modCount: " << modCount << G4endl;
		G4cout << "posCounter: " << posCounter << G4endl;
		*/
		posTable[posCounter][modCount] = input;

		modCount++;
		modCount = modCount % 7;
		if (modCount == 0) {
			posCounter++;
		}
	}
	file.close();
	/*
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 7; ++j) {
			G4cout << posTable[i][j] << ", ";
		}
		G4cout << G4endl;
	}
	*/
	posCounter = 0;
	}
	fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{

	G4double eps = 0.01 * cm; // offset actual particle start to avoid interaction in "starting material"
	G4double energy = 0;
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4double x, y, z, r, theta;
	G4ParticleDefinition* particle;
	G4ThreeVector pos;
	G4ThreeVector mom;
	switch (choiceParticle) {
	case 0:
		energy = CLHEP::RandGaussQ::shoot(avgE, 0.2 * MeV);
		particle = particleTable->FindParticle("e-");
		pos.setX(distTargetOrigin + 1 * cm + 1 * cm);
		pos.setY(0.);
		pos.setZ(0.);
		mom.setX(-1.);
		mom.setY(0.);
		mom.setZ(0.);
		break;
		
	case 1:
		energy = posTable[posCounter][6] * MeV;
		particle = particleTable->FindParticle("e+");
		pos.setX(posTable[posCounter][0]);
		pos.setY(posTable[posCounter][1]);
		pos.setZ(posTable[posCounter][2]);
		mom.setX(posTable[posCounter][3]);
		mom.setY(posTable[posCounter][4]);
		mom.setZ(posTable[posCounter][5]);
		posCounter++;
		break;
	case 2:
		energy = 9.0 * MeV;
		r = 1. * cm * sqrt(G4UniformRand());
		theta = 2. * 3.1415 * G4UniformRand();
		y = -5. * cm + r * sin(theta);
		z = 3. * cm + r * cos(theta);
		particle = particleTable->FindParticle("e-");
		pos.setX(50 * cm - eps);
		pos.setY(y);
		pos.setZ(z);
		mom.setX(-1.);
		mom.setY(0.);
		mom.setZ(0.);
		break;
	case 3:
		energy = 1.0 * MeV;
		r = 1. * cm * sqrt(G4UniformRand());
		theta = 2. * 3.1415 * G4UniformRand();
		y = -5. * cm + r * sin(theta);
		z = 3. * cm + r * cos(theta);
		particle = particleTable->FindParticle("e+");
		pos.setX(50 * cm - eps);
		pos.setY(y);
		pos.setZ(z);
		mom.setX(-1.);
		mom.setY(0.);
		mom.setZ(0.);
		break;
	case 4:
		energy = 3.0 * eV;
		x = -4.5 * cm + 5 * cm * G4UniformRand();
		y = 57.5 * cm - eps;
		z = -4.5 * cm + 5 * cm * G4UniformRand();
		particle = particleTable->FindParticle("e+");
		pos.setX(x);
		pos.setY(y);
		pos.setZ(z);
		mom.setX(0.);
		mom.setY(-1.);
		mom.setZ(0.);
		break;
	case 5:
		break;
	default:
		G4cerr << "No correct choice of particles chosen!" << G4endl;
		exit(1);
		break;
	}
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticleEnergy(energy);
	fParticleGun->GeneratePrimaryVertex(anEvent);
}