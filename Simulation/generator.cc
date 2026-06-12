#include "generator.hh"

PrimaryGenerator::PrimaryGenerator() {
	fParticleGun = new G4ParticleGun(1);
	fParticleEnergy = 100 * MeV;
	fParticleGun->SetParticleEnergy(fParticleEnergy);

}

PrimaryGenerator::~PrimaryGenerator() {
	delete fParticleGun;
}

void PrimaryGenerator::SetParticleEnergy(G4double energy)
{
	fParticleEnergy = energy;
}

void PrimaryGenerator::GeneratePrimaries(G4Event* anEvent) {
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* particle1 = particleTable->FindParticle("proton");
	G4ParticleDefinition* particle2 = particleTable->FindParticle("neutron");
	G4ParticleDefinition* particle3 = particleTable->FindParticle("alpha");

	G4ThreeVector pos(((G4UniformRand() * 2.0 - 1.0) * 4 * cm), ((G4UniformRand() * 2.0 - 1.0) * 4 * cm), -400);
	G4ThreeVector mom(0., 0., 1);

	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleEnergy(fParticleEnergy);
	fParticleGun->SetParticleDefinition(particle1);

	fParticleGun->GeneratePrimaryVertex(anEvent);
}