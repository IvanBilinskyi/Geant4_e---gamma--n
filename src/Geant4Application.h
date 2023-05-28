#pragma once
#include <G4MTRunManager.hh>
#include <G4RunManagerFactory.hh>
#include <G4UIExecutive.hh>
#include <G4UImanager.hh>
#include <G4VisExecutive.hh>

#include "ApplicationMessenger.h"

class Geant4Application
{
  public:
    Geant4Application(int argc, char** argv, bool runGUI = true);
    ~Geant4Application();
    void Execute(const std::string& command);
    void Run();

  private:
    void Init();
    void InitGUI();

    G4MTRunManager* runManager;
    G4UIExecutive* ui;
    G4VisManager* visManager;

    ApplicationMessenger* applicationMessenger;
};
