#include "ApplicationMessenger.h"

#include <G4Tokenizer.hh>
#include <G4UIQt.hh>
#include <G4UImanager.hh>
#include <G4UIsession.hh>
#include <G4VBasicShell.hh>

ApplicationMessenger::ApplicationMessenger()
{
    resizeWindowCmd = new G4UIcommand("/application/resizeWindow", this);
    resizeWindowCmd->SetGuidance("Resize the application window");
    resizeWindowCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
    resizeWindowCmd->SetParameter(new G4UIparameter("width", 'i', false));
    resizeWindowCmd->SetParameter(new G4UIparameter("height", 'i', false));

    moveWindowCmd = new G4UIcommand("/application/moveWindow", this);
    moveWindowCmd->SetGuidance("Move the application window");
    moveWindowCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
    moveWindowCmd->SetParameter(new G4UIparameter("x", 'i', false));
    moveWindowCmd->SetParameter(new G4UIparameter("y", 'i', false));
}

ApplicationMessenger::~ApplicationMessenger()
{
    delete resizeWindowCmd;
    delete moveWindowCmd;
}

void ApplicationMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if(command == resizeWindowCmd)
    {
        G4Tokenizer next(newValue);
        G4int width  = StoI(next());
        G4int height = StoI(next());
        G4cout << "Resizing window to " << width << "x" << height << G4endl;
        GetMainWindow()->resize(width, height);
    }
    if(command == moveWindowCmd)
    {
        G4Tokenizer next(newValue);
        G4int x = StoI(next());
        G4int y = StoI(next());
        G4cout << "Moving window to " << x << "," << y << G4endl;
        GetMainWindow()->move(x, y);
    }
}

QMainWindow* ApplicationMessenger::GetMainWindow()
{
    auto uiManager = G4UImanager::GetUIpointer();
    if(!uiManager)
        return nullptr;

    G4VBasicShell* shell = dynamic_cast<G4VBasicShell*>(uiManager->GetG4UIWindow());
    G4UIQt* qt           = dynamic_cast<G4UIQt*>(shell);
    return qt->GetMainWindow();
}
