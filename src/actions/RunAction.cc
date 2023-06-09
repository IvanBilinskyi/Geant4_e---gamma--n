//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file RunAction.cc
/// \brief Implementation of the RunAction class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "RunAction.hh"
#include "Run.hh"
#include "RunMessenger.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "HistoManager.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(DetectorConstruction *det, PrimaryGeneratorAction *prim)
        : G4UserRunAction(),
          fDetector(det), fPrimary(prim), fRun(0), fHistoManager(0),
          fRunMessenger(0), fPrint(true)
{
    fHistoManager = new HistoManager();
    fRunMessenger = new RunMessenger(this);
    const G4double milligray = 1.e-3 * gray;
    const G4double microgray = 1.e-6 * gray;
    const G4double nanogray = 1.e-9 * gray;
    const G4double picogray = 1.e-12 * gray;

    new G4UnitDefinition("milligray", "milliGy", "Dose", milligray);
    new G4UnitDefinition("microgray", "microGy", "Dose", microgray);
    new G4UnitDefinition("nanogray", "nanoGy", "Dose", nanogray);
    new G4UnitDefinition("picogray", "picoGy", "Dose", picogray);

    // Register accumulable to the accumulable manager
    G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->RegisterAccumulable(fGammaEnDep);
    accumulableManager->RegisterAccumulable(fElEnDep);
    accumulableManager->RegisterAccumulable(fNCount);
    accumulableManager->RegisterAccumulable(fECount);
    accumulableManager->RegisterAccumulable(fGCount);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
    delete fHistoManager;
    delete fRunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run *RunAction::GenerateRun()
{
    fRun = new Run(fDetector);
    return fRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run *)
{
    // show Rndm status
    if (isMaster) G4Random::showEngineStatus();

    // keep run condition
    if (fPrimary) {
        G4ParticleDefinition *particle
                = fPrimary->GetParticleGun()->GetParticleDefinition();
        G4double energy = fPrimary->GetParticleGun()->GetParticleEnergy();
        fRun->SetPrimary(particle, energy);
    }

    fScoringVolume = fDetector->GetLQuartz();
    //histograms
    //
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run *run)
{
    G4int nofEvents = run->GetNumberOfEvent();
    if (nofEvents == 0) return;

    G4double edep = fGammaEnDep.GetValue() + fElEnDep.GetValue();
    G4double rms = edep / nofEvents;
    if (rms > 0.) rms = std::sqrt(rms); else rms = 0.;

    const auto detConstruction = static_cast<const DetectorConstruction *>(
            G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    G4double mass = detConstruction->GetLQuartz()->GetMass();
    G4double dose = edep / mass;
    G4double rmsDose = rms / mass;

    // Print
    //
    if (!isMaster) {
        G4cout
                << G4endl
                << "--------------------End of Local Run------------------------";
        G4cout
                << G4endl
                << " Number of events : "
                << nofEvents
                << G4endl
                << " Cumulated dose per run, in scoring volume : "
                << G4BestUnit(dose, "Dose") << " rms = " << G4BestUnit(rmsDose, "Dose")
                << G4endl
                << "------------------------------------------------------------"
                << G4endl
                << G4endl;
    }

    if (isMaster) fRun->EndOfRun(fPrint);

    //save histograms
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();

    // show Rndm status
    if (isMaster) G4Random::showEngineStatus();
}

void RunAction::AddEdep(G4double Edep, G4int eCount, G4double Gdep, G4int gCount)
{
    fGammaEnDep += Gdep;
    fGCount += gCount;
    fECount += eCount;
    fElEnDep += Edep;
    fRun->AddEdep(Edep, eCount, Gdep, gCount);
}

void RunAction::AddNCount(G4int n)
{
    fNCount += n;
    fRun->AddNCount(n);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::SetPrintFlag(G4bool flag)
{
    fPrint = flag;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
