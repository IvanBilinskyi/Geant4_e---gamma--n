//
// Created by tolkiens_fan on 08.06.23.
//
#include "EventAction.hh"
#include "RunAction.hh"

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///

class RunAction;

EventAction::EventAction(RunAction* runAction)
        : fRunAction(runAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
    fGammaEdep = 0.;
    fElEdep = 0.;
    fNCount = 0;
    fGCount = 0;
    fECount = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{
    // accumulate statistics in run action
    fRunAction->AddEdep(fElEdep, fECount, fGammaEdep, fGCount);
    fRunAction->AddNCount(fNCount);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
