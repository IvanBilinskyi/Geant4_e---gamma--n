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
/// \file HistoManager.hh
/// \brief Definition of the HistoManager class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"
#include "G4AnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

struct TrackData
{
    TrackData()
    {
        E = 0;
        pt = 0;
        eta = 0;
        phi = 0;
        x = 0;
        y = 0;
        z = 0;
        px = 0;
        py = 0;
        pz = 0;
        pdg = 0;
        name = "";
        charge = 0;
        mass = 0;
        status = "";
    }

    TrackData(double E_, double pt_, double eta_, double phi_, double x_, double y_, double z_, double px_, double py_,
              double pz_, int pdg_, G4String name_, double charge_, double mass_, G4String status_)
    {
        E = E_;
        pt = pt_;
        eta = eta_;
        phi = phi_;
        x = x_;
        y = y_;
        z = z_;
        px = px_;
        py = py_;
        pz = pz_;
        pdg = pdg_;
        name = name_;
        charge = charge_;
        mass = mass_;
        status = status_;
    }

    G4double E;
    G4double pt;
    G4double eta;
    G4double phi;
    G4double x;
    G4double y;
    G4double z;
    G4double px;
    G4double py;
    G4double pz;
    G4int pdg;
    G4String name;
    G4double charge;
    G4double mass;
    G4String status;
};

class HistoManager
{
public:
    HistoManager();

    ~HistoManager();

    static void FillNtuple(TrackData data);

private:
    static void Book();

    G4String fFileName;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

