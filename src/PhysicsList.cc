
#include "G4PhysicsListHelper.hh"

#include "PhysicsList.hh" 
#include "G4hMultipleScattering.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysListFactory.hh"
#include "G4VPhysicsConstructor.hh"

// Physic lists (contained inside the Geant4 distribution)
#include "G4EmStandardPhysics_option4.hh" /// use for "standard EM". Designed for any applications required higher accuracy of electrons, hadrons and ion tracking without magnetic field. 

// For units of measurements
#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

PhysicsList::PhysicsList(): G4VModularPhysicsList()
					
{
  defaultCutValue = 0.1* mm;

  SetVerboseLevel(0);

  // EM physics
      emPhysicsList = new G4EmStandardPhysics_option4(0);
   //   emPhysicsList = new G4EmLivermorePhysics(0);
   //   emPhysicsList = new G4EmPenelopePhysics(0);
}


PhysicsList::~PhysicsList()
{
	delete emPhysicsList;
}

/////////////////////////////////////////////////////////////////////////////
void PhysicsList::ConstructParticle()
{
	emPhysicsList->ConstructParticle();
  /*decPhysicsList->ConstructParticle();
    // ions
  G4IonConstructor iConstructor;
  iConstructor.ConstructParticle();*/
}

void PhysicsList::ConstructProcess()
{
	emPhysicsList->ConstructProcess();
	
  // transportation
  //
  AddTransportation();
/*
  // electromagnetic physics list
  //
  emPhysicsList->ConstructProcess();
  em_config.AddModels();*/
}

void PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCutsWithDefault();
  DumpCutValuesTable();
}
