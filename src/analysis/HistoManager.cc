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
/// \file HistoManager.cc
/// \brief Implementation of the HistoManager class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HistoManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
        : fFileName("Hadr03")
{
    Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
    // Create or get analysis manager
    // The choice of analysis technology is done via selection of a namespace
    // in HistoManager.hh
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetNtupleMerging(true, 1);
    analysisManager->SetDefaultFileType("root");
    analysisManager->SetFileName("Hadr03");
    analysisManager->SetVerboseLevel(1);
//  analysisManager->SetActivation(true);     //enable inactivation of histograms

    // Define histograms start values
    const G4int kMaxHisto = 14;
    const G4String id[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                           "10", "11", "12", "13"};
    const G4String title[] =
            {"dummy",                                          //0
             "kinetic energy of scattered primary particle",   //1
             "kinetic energy of gamma",                        //2
             "kinetic energy of electrons",                    //3
             "kinetic energy of neutrons",                     //4
             "kinetic energy of protons",                      //5
             "kinetic energy of deuterons",                    //6
             "kinetic energy of alphas",                       //7
             "kinetic energy of nuclei",                       //8
             "kinetic energy of mesons",                       //9
             "kinetic energy of baryons",                      //10
             "Q = Ekin out - Ekin in",                         //11
             "Pbalance = mag(P_out - P_in)",                   //12
             "atomic mass of nuclei"                           //13
            };

    // Default values (to be reset via /analysis/h1/set command)
    G4int nbins = 100;
    G4double vmin = 0.;
    G4double vmax = 100.;

    // Create all histograms as inactivated
    // as we have not yet set nbins, vmin, vmax
//    for (G4int k = 0; k < kMaxHisto; k++) {
//        G4int ih = analysisManager->CreateH1(id[k], title[k], nbins, vmin, vmax);
//        analysisManager->SetH1Activation(ih, false);
//    }

    // book ntuple
    //
    analysisManager->CreateNtuple("Tracks", "Track parameters");
    analysisManager->CreateNtupleDColumn(0, "E");
    analysisManager->CreateNtupleDColumn(0, "pt");
    analysisManager->CreateNtupleDColumn(0, "eta");
    analysisManager->CreateNtupleDColumn(0, "phi");
    analysisManager->CreateNtupleDColumn(0, "x");
    analysisManager->CreateNtupleDColumn(0, "y");
    analysisManager->CreateNtupleDColumn(0, "z");
    analysisManager->CreateNtupleDColumn(0, "px");
    analysisManager->CreateNtupleDColumn(0, "py");
    analysisManager->CreateNtupleDColumn(0, "pz");
    analysisManager->CreateNtupleDColumn(0, "pdg");
    analysisManager->CreateNtupleSColumn(0, "name");
    analysisManager->CreateNtupleDColumn(0, "charge");
    analysisManager->CreateNtupleDColumn(0, "mass");
    analysisManager->CreateNtupleSColumn(0, "status");
    analysisManager->FinishNtuple(0);

}

void HistoManager::FillNtuple(TrackData data)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(0, 0, data.E);
    analysisManager->FillNtupleDColumn(0, 1, data.pt);
    analysisManager->FillNtupleDColumn(0, 2, data.eta);
    analysisManager->FillNtupleDColumn(0, 3, data.phi);
    analysisManager->FillNtupleDColumn(0, 4, data.x);
    analysisManager->FillNtupleDColumn(0, 5, data.y);
    analysisManager->FillNtupleDColumn(0, 6, data.z);
    analysisManager->FillNtupleDColumn(0, 7, data.px);
    analysisManager->FillNtupleDColumn(0, 8, data.py);
    analysisManager->FillNtupleDColumn(0, 9, data.pz);
    analysisManager->FillNtupleDColumn(0, 10, data.pdg);
    analysisManager->FillNtupleSColumn(0, 11, data.name);
    analysisManager->FillNtupleDColumn(0, 12, data.charge);
    analysisManager->FillNtupleDColumn(0, 13, data.mass);
    analysisManager->FillNtupleSColumn(0, 14, data.status);
    analysisManager->AddNtupleRow();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
