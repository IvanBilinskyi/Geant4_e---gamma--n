//
// Created by ivan on 03.02.23.
//

#include "ElectronPhysics.hh"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"

#include "G4eBremsstrahlung.hh"

#include "G4SystemOfUnits.hh"

ElectronPhysics::ElectronPhysics(const G4String &name)
: G4VPhysicsConstructor(name)
{ }

ElectronPhysics::~ElectronPhysics()
{ }

void ElectronPhysics::ConstructProcess()
{
    G4eBremsstrahlung* process = new G4eBremsstrahlung("Bremsstrahlung");
    RegisterProcess(process, G4Electron::Definition());

    G4ProcessManager* processManager = G4Electron::Electron()->GetProcessManager();
    processManager->AddContinuousProcess(process);
}