#include "generator.hh"
#include "Randomize.hh"


extern G4double sigmaPos;
extern G4double avgE;

MyPrimaryGenerator::MyPrimaryGenerator()
{	
	CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine);
	CLHEP::HepRandom::setTheSeed(time(NULL));
	//CLHEP::HepRandom::setTheSeed((unsigned)clock());
	avgE = 9 * MeV;

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

	G4double radiusCircle = 2.5 * mm;
	G4double sigmaEnergy = 0.2 * MeV;
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "e-";
	G4ParticleDefinition* particle = particleTable->FindParticle("e-");


	
	G4ThreeVector pos(55 * cm, 0., 0.);
	G4ThreeVector mom(-1., 0., 0);
	G4double randPos;	// to test whether beam hits the thin target
	G4double energy;
	energy = CLHEP::RandGaussQ::shoot(avgE, sigmaEnergy);


	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticleEnergy(energy);

	fParticleGun->GeneratePrimaryVertex(anEvent);
}


/*
randPos = CLHEP::RandGaussQ::shoot(0 * mm, sigmaPos);
if (randPos > -radiusCircle && randPos < radiusCircle)		// electron hits target properly
{
	energy = CLHEP::RandGaussQ::shoot(avgE, sigmaEnergy);
}
else
{
	energy = 0;
}
*/
//G4double test = CLHEP::RandMultiGauss::shoot();