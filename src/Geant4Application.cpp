#include <G4ParticleHPManager.hh>
#include "Geant4Application.h"

#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"

Geant4Application::Geant4Application(int argc, char** argv, bool runGUI)
    : runManager(new G4MTRunManager),
      ui(nullptr),
      visManager(nullptr)
{
    Init();
    applicationMessenger = new ApplicationMessenger;
    if(runGUI)
    {
        ui         = new G4UIExecutive(argc, argv, "qt");
        visManager = new G4VisExecutive;
        InitGUI();
    }
}

Geant4Application::~Geant4Application()
{
    delete applicationMessenger;
    delete visManager;
    delete runManager;
}

void Geant4Application::Init()
{
    // set mandatory initialization classes
    auto detectorConstruction = new DetectorConstruction;
    runManager->SetUserInitialization(detectorConstruction);
    runManager->SetUserInitialization(new PhysicsList);
    runManager->SetUserInitialization(new ActionInitialization(detectorConstruction));

    G4ParticleHPManager::GetInstance()->SetSkipMissingIsotopes( false );
    G4ParticleHPManager::GetInstance()->SetDoNotAdjustFinalState( true );
    G4ParticleHPManager::GetInstance()->SetUseOnlyPhotoEvaporation( true );
    G4ParticleHPManager::GetInstance()->SetNeglectDoppler( false );
    G4ParticleHPManager::GetInstance()->SetProduceFissionFragments( false );
    G4ParticleHPManager::GetInstance()->SetUseWendtFissionModel( false );
    G4ParticleHPManager::GetInstance()->SetUseNRESP71Model( false );
}

void Geant4Application::InitGUI()
{
    visManager->Initialize();
}

void Geant4Application::Execute(const std::string& command)
{
    G4UImanager::GetUIpointer()->ApplyCommand(command);
}

void Geant4Application::Run()
{
    if(ui)
        ui->SessionStart();
    delete ui;
}
