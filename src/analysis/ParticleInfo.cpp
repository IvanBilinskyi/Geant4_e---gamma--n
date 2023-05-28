//
// Created by ivan on 08.02.23.
//
#include "ParticleInfo.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

G4bool ParticleInfo::processed = false;
G4bool ParticleInfo::isElectron = false;
G4bool ParticleInfo::isGamma = false;
G4int ParticleInfo::neutronCount = 0;

G4ThreeVector ParticleInfo::position = G4ThreeVector();
G4ThreeVector ParticleInfo::momentum = G4ThreeVector(1,0,0);
G4double ParticleInfo::energy = 40*MeV;

G4double ParticleInfo::GetEnergy()
{
    return ParticleInfo::energy;
}

void ParticleInfo::SetEnergy(G4double newEn)
{
    ParticleInfo::energy = newEn;
}

G4String ParticleInfo::GetEnergyStr()
{
    return std::to_string(energy) + " MeV";
}

G4ThreeVector ParticleInfo::GetMomentum()
{
    return ParticleInfo::momentum;
}

G4String ParticleInfo::GetMomentumStr()
{
    return std::to_string(momentum.getX() / momentum.mag()) + " " +
           std::to_string(momentum.getY() / momentum.mag()) + " " +
           std::to_string(momentum.getZ() / momentum.mag());
}

void ParticleInfo::SetMomentum(G4ThreeVector newMom)
{
    ParticleInfo::momentum = newMom;
}

G4ThreeVector ParticleInfo::GetPosition()
{
    return ParticleInfo::position;
}

void ParticleInfo::SetPosition(G4ThreeVector pos)
{
    ParticleInfo::position = pos;
}

G4String ParticleInfo::GetPositionStr()
{
    return std::to_string(position.getX()) + " " +
           std::to_string(position.getY()) + " " +
           std::to_string(position.getZ());
}

void ParticleInfo::SetAll(G4double newEn, G4ThreeVector newPos, G4ThreeVector newMom)
{
    SetEnergy(newEn);
    SetPosition(newPos);
    SetMomentum(newMom);
}
