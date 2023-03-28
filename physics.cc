#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
	G4EmParameters* param = G4EmParameters::Instance();
    param->SetDefaults();
    param->SetVerbose(0);
    param->SetMinEnergy(10*eV);
    param->SetMaxEnergy(10*TeV);
    //RegisterPhysics(new G4EmStandardPhysics_option4(1));
	//RegisterPhysics (new G4EmStandardPhysics());
    RegisterPhysics(new G4EmPenelopePhysics());


    //SetPhysicsType(bElectromagnetic);
}

MyPhysicsList::~MyPhysicsList()
{
}


void MyPhysicsList::ConstructProcess()
{

    AddTransportation();

    
    G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

    auto particleIterator = GetParticleIterator();
    particleIterator->reset();
    while ((*particleIterator)()) {
        G4ParticleDefinition* particle = particleIterator->value();
        G4String particleName = particle->GetParticleName();
        //G4cout << "In while-loop!" << G4endl;
        if (particleName == "gamma") {

            ph->RegisterProcess(new G4RayleighScattering, particle);
            ph->RegisterProcess(new G4PhotoElectricEffect, particle);
            G4ComptonScattering* cs = new G4ComptonScattering;
            cs->SetEmModel(new G4KleinNishinaModel());
            ph->RegisterProcess(cs, particle);
            ph->RegisterProcess(new G4GammaConversion, particle);

        }
        else if (particleName == "e-") {

            ph->RegisterProcess(new G4eMultipleScattering(), particle);
            ph->RegisterProcess(new G4eIonisation(), particle);
            ph->RegisterProcess(new G4eBremsstrahlung(), particle);

        }
        else if (particleName == "e+") {

            ph->RegisterProcess(new G4eMultipleScattering(), particle);
            ph->RegisterProcess(new G4eIonisation(), particle);
            ph->RegisterProcess(new G4eBremsstrahlung(), particle);
            ph->RegisterProcess(new G4eplusAnnihilation(), particle);

        }
        else if (particleName == "mu+" ||
            particleName == "mu-") {

            ph->RegisterProcess(new G4MuMultipleScattering(), particle);
            ph->RegisterProcess(new G4MuIonisation(), particle);
            ph->RegisterProcess(new G4MuBremsstrahlung(), particle);
            ph->RegisterProcess(new G4MuPairProduction(), particle);

        }
        else if (particleName == "proton" ||
            particleName == "pi-" ||
            particleName == "pi+") {

            ph->RegisterProcess(new G4hMultipleScattering(), particle);
            ph->RegisterProcess(new G4hIonisation(), particle);
            ph->RegisterProcess(new G4hBremsstrahlung(), particle);
            ph->RegisterProcess(new G4hPairProduction(), particle);

        }
        else if (particleName == "alpha" ||
            particleName == "He3") {

            ph->RegisterProcess(new G4hMultipleScattering(), particle);
            ph->RegisterProcess(new G4ionIonisation(), particle);
            ph->RegisterProcess(new G4NuclearStopping(), particle);

        }
        else if (particleName == "GenericIon") {

            ph->RegisterProcess(new G4hMultipleScattering(), particle);
            G4ionIonisation* ionIoni = new G4ionIonisation();
            ionIoni->SetEmModel(new G4IonParametrisedLossModel());
            ph->RegisterProcess(ionIoni, particle);
            ph->RegisterProcess(new G4NuclearStopping(), particle);

        }
        else if ((!particle->IsShortLived()) &&
            (particle->GetPDGCharge() != 0.0) &&
            (particle->GetParticleName() != "chargedgeantino")) {

            //all others charged particles except geantino
            ph->RegisterProcess(new G4hMultipleScattering(), particle);
            ph->RegisterProcess(new G4hIonisation(), particle);
        }
    }


    
}


/*








void MyPhysicsList::ConstructProcess()
{
    G4cout << "In ConstructProcess()" << G4endl;
    G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

    // Add standard EM Processes
    //
    auto particleIterator = GetParticleIterator();
    particleIterator->reset();
    while ((*particleIterator)()) {
        G4ParticleDefinition* particle = particleIterator->value();
        G4String particleName = particle->GetParticleName();

        if (particleName == "gamma") {

            ph->RegisterProcess(new G4RayleighScattering, particle);
            ph->RegisterProcess(new G4PhotoElectricEffect, particle);
            G4ComptonScattering* cs = new G4ComptonScattering;
            cs->SetEmModel(new G4KleinNishinaModel());
            ph->RegisterProcess(cs, particle);
            ph->RegisterProcess(new G4GammaConversion, particle);

        }
        else if (particleName == "e-") {

            ph->RegisterProcess(new G4eMultipleScattering(), particle);
            ph->RegisterProcess(new G4eIonisation(), particle);
            ph->RegisterProcess(new G4eBremsstrahlung(), particle);

        }
        else if (particleName == "e+") {

            ph->RegisterProcess(new G4eMultipleScattering(), particle);
            ph->RegisterProcess(new G4eIonisation(), particle);
            ph->RegisterProcess(new G4eBremsstrahlung(), particle);
            ph->RegisterProcess(new G4eplusAnnihilation(), particle);

        }
        else if (particleName == "mu+" ||
            particleName == "mu-") {

            ph->RegisterProcess(new G4MuMultipleScattering(), particle);
            ph->RegisterProcess(new G4MuIonisation(), particle);
            ph->RegisterProcess(new G4MuBremsstrahlung(), particle);
            ph->RegisterProcess(new G4MuPairProduction(), particle);

        }
        else if (particleName == "proton" ||
            particleName == "pi-" ||
            particleName == "pi+") {

            ph->RegisterProcess(new G4hMultipleScattering(), particle);
            ph->RegisterProcess(new G4hIonisation(), particle);
            ph->RegisterProcess(new G4hBremsstrahlung(), particle);
            ph->RegisterProcess(new G4hPairProduction(), particle);

        }
        else if (particleName == "alpha" ||
            particleName == "He3") {

            ph->RegisterProcess(new G4hMultipleScattering(), particle);
            ph->RegisterProcess(new G4ionIonisation(), particle);
            ph->RegisterProcess(new G4NuclearStopping(), particle);

        }
        else if (particleName == "GenericIon") {

            ph->RegisterProcess(new G4hMultipleScattering(), particle);
            G4ionIonisation* ionIoni = new G4ionIonisation();
            ionIoni->SetEmModel(new G4IonParametrisedLossModel());
            ph->RegisterProcess(ionIoni, particle);
            ph->RegisterProcess(new G4NuclearStopping(), particle);

        }
        else if ((!particle->IsShortLived()) &&
            (particle->GetPDGCharge() != 0.0) &&
            (particle->GetParticleName() != "chargedgeantino")) {

            //all others charged particles except geantino
            ph->RegisterProcess(new G4hMultipleScattering(), particle);
            ph->RegisterProcess(new G4hIonisation(), particle);
        }
    }

    // Deexcitation
    //
    G4VAtomDeexcitation* de = new G4UAtomicDeexcitation();
    G4LossTableManager::Instance()->SetAtomDeexcitation(de);
}



*/

