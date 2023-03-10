#include "generator.hh"
#include "Randomize.hh"




MyPrimaryGenerator::MyPrimaryGenerator()
{	
	CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine);
	CLHEP::HepRandom::setTheSeed(time(NULL));
	//CLHEP::HepRandom::setTheSeed((unsigned)clock());

	fMessenger = new G4GenericMessenger(this, "/generator/", "Generator Messenger");

	fMessenger->DeclareProperty("avgE", avgE, "Average energy of the incident electrons");
	//fMessenger->DeclareProperty("sigmaPos", sigmaPos, "Standard deviation to decide whether e- will hit the target");

	fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{

	G4double eps = 0.01 * cm; // offset actual particle start to avoid interaction in "starting material"

	// choice determines type of particles:
	// 0 fast e- from actual target
	// 1 slow e+ from actual moderator
	// 2 fast e- from COMSOL target
	// 3 fast e+ from COMSOL target
	// 4 slow e+ from COMSOL moderator
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
		// todo
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