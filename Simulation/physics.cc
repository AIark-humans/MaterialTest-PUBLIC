#include "physics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4NeutronTrackingCut.hh"

PhysicsList::PhysicsList() {
	RegisterPhysics(new G4EmStandardPhysics());
	RegisterPhysics(new G4HadronElasticPhysics());
	RegisterPhysics(new G4HadronPhysicsFTFP_BERT_HP());
}

PhysicsList::~PhysicsList(){}