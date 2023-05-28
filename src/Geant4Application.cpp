#include "Geant4Application.h"

#include "ActionInitialization.h"
#include "DetectorConstruction.h"
#include "PhysicsList.h"

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
    runManager->SetUserInitialization(new DetectorConstruction);
    runManager->SetUserInitialization(new PhysicsList);
    runManager->SetUserInitialization(new ActionInitialization);
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
