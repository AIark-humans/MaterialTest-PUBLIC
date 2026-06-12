#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

class PrimaryGenerator : public G4VUserPrimaryGeneratorAction {
public:
	PrimaryGenerator();
	~PrimaryGenerator();

	virtual void GeneratePrimaries(G4Event*);

	void SetParticleEnergy(G4double energy);

private:
	G4ParticleGun* fParticleGun;
	G4double fParticleEnergy;
};

#endif