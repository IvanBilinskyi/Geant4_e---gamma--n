//
// Created by ivan on 03.02.23.
//

#ifndef ElectronPhysics_h
#define ElectronPhysics_h 1

#include "globals.hh"
#include "G4VPhysicsConstructor.hh"

class ElectronPhysics : public G4VPhysicsConstructor
{
public:
    ElectronPhysics(const G4String& name="e-");
    ~ElectronPhysics() override;

public:
    void ConstructParticle() override { };
    void ConstructProcess() override;
};


#endif
