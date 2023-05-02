#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4GenericMessenger.hh"
#include <fstream>
#include <iostream>
#include <random>
#include <string>

/* -------------------------------------------------------------------- */
class FastElectron : public G4VUserPrimaryGeneratorAction
{
public:
	FastElectron(G4double argDistTargetOrigin, G4double argAvgE);
	~FastElectron();

	virtual void GeneratePrimaries(G4Event*);

private:
	G4double distTargetOrigin;
	G4double avgE;

	G4ParticleGun* fParticleGun;
	G4GenericMessenger* fMessenger;

};
/* -------------------------------------------------------------------- */
class FastPositronSample : public G4VUserPrimaryGeneratorAction
{
public:
	FastPositronSample(G4double argDistTargetOrigin);
	~FastPositronSample();

	virtual void GeneratePrimaries(G4Event*);

private:
	G4double distTargetOrigin;

	G4ParticleGun* fParticleGun;
	G4GenericMessenger* fMessenger;
	int posCounter;
	int posNumber = 16514;
	double** posTable;  // x y z, px, py, pz, E

};
/* -------------------------------------------------------------------- */
class FastElectronCOMSOL : public G4VUserPrimaryGeneratorAction
{
public:
	FastElectronCOMSOL();
	~FastElectronCOMSOL();
	virtual void GeneratePrimaries(G4Event*);
private:
	G4ParticleGun* fParticleGun;
};
/* -------------------------------------------------------------------- */
class FastPositronCOMSOL : public G4VUserPrimaryGeneratorAction
{
public:
	FastPositronCOMSOL();
	~FastPositronCOMSOL();
	virtual void GeneratePrimaries(G4Event*);
private:
	G4ParticleGun* fParticleGun;
};
/* -------------------------------------------------------------------- */
class SlowPositronCOMSOL : public G4VUserPrimaryGeneratorAction
{
public:
	SlowPositronCOMSOL();
	~SlowPositronCOMSOL();
	virtual void GeneratePrimaries(G4Event*);

private:
	G4ParticleGun* fParticleGun;
};
/* -------------------------------------------------------------------- */
#endif