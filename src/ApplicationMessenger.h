#pragma once
#include <G4UImessenger.hh>
#include <QMainWindow>

class ApplicationMessenger : public G4UImessenger
{
  public:
    ApplicationMessenger();
    ~ApplicationMessenger() override;

  private:
    void SetNewValue(G4UIcommand* command, G4String newValue) override;

    static QMainWindow* GetMainWindow();

    G4UIcommand* resizeWindowCmd;
    G4UIcommand* moveWindowCmd;
};
