//
// Created by ivan on 08.02.23.
//
#ifndef ParticleInfo_h
#define ParticleInfo_h 1

#include "globals.hh"
#include "G4ThreeVector.hh"

class ParticleInfo
{
public:
    static G4bool isElectron;
    static G4bool isGamma;
    static G4bool processed;
    static G4int neutronCount;
    ParticleInfo() = default;
    ~ParticleInfo() = default;

    static void SetMomentum(G4ThreeVector momentum);
    static G4ThreeVector GetMomentum();
    static G4String GetMomentumStr();

    static void SetEnergy(G4double);
    static G4double GetEnergy();
    static G4String GetEnergyStr();

    static G4ThreeVector GetPosition();
    static void SetPosition(G4ThreeVector pos);
    static G4String GetPositionStr();

    static void SetAll(G4double newEn, G4ThreeVector newPos, G4ThreeVector newMom);

private:
    static G4double energy;
    static G4ThreeVector momentum;
    static G4ThreeVector position;
};

#endif
