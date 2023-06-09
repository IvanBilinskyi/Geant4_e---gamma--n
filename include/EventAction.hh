//
// Created by tolkiens_fan on 08.06.23.
//

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///

class RunAction;

class EventAction : public G4UserEventAction
{
public:
    EventAction(RunAction* runAction);
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

    void AddGammaEdep(G4double edep) { fGammaEdep += edep; fGCount++;}
    void AddElEdep(G4double edep) { fElEdep += edep; fECount++;}
    void AddN() {fNCount += 1;};

private:
    RunAction* fRunAction = nullptr;
    G4double   fGammaEdep = 0.;
    G4double   fElEdep = 0.;
    G4int      fNCount = 0;
    G4int      fGCount = 0;
    G4int      fECount = 0;
};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif