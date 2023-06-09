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
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Torus.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(),
 fPBox(0), fLBox(0), fMaterial(0), fDetectorMessenger(0)
{
  fBoxSize = 10*m;
  DefineMaterials();
  SetMaterial("Molybdenum98");  
  fDetectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ delete fDetectorMessenger;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
 // define a Material from isotopes
 //
 MaterialWithSingleIsotope("Molybdenum98", "Mo98",  10.28*g/cm3, 42, 98);
 
 //NE213
 G4Element* H  = new G4Element("Hydrogen" ,"H" , 1.,  1.01*g/mole);
 G4Element* C  = new G4Element("Carbon"   ,"C" , 6., 12.00*g/mole);
 G4Material* ne213 = 
 new G4Material("NE213", 0.874*g/cm3, 2);
 ne213->AddElement(H,    9.2*perCent);
 ne213->AddElement(C,   90.8*perCent);
 
 G4Material* hydrogen = 
 new G4Material("hydrogen", 1.0*g/cm3, 1);
 hydrogen->AddElement(H, 1);
 
 G4Material* carbon = 
 new G4Material("carbon", 1.0*g/cm3, 1);
 carbon->AddElement(C, 1);
 
 G4Material* plastic = 
 new G4Material("plastic", 1.0*g/cm3, 2);
 plastic->AddElement(H, 1);
 plastic->AddElement(C, 1);
 
 // or use G4-NIST materials data base
 //
 G4NistManager* man = G4NistManager::Instance();
 man->FindOrBuildMaterial("G4_B");

 G4Element*  O = man->FindOrBuildElement("O");
 G4Element* Hf = man->FindOrBuildElement("Hf");
 
 G4Material* HfO2 = new G4Material("HfO2", 9.68*g/cm3, 2);
 HfO2->AddElement(Hf, 1);
 HfO2->AddElement(O , 2);
 
 ///G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* DetectorConstruction::MaterialWithSingleIsotope( G4String name,
                           G4String symbol, G4double density, G4int Z, G4int A)
{
 // define a material from an isotope
 //
 G4int ncomponents;
 G4double abundance, massfraction;

 G4Isotope* isotope = new G4Isotope(symbol, Z, A);
 
 G4Element* element  = new G4Element(name, symbol, ncomponents=1);
 element->AddIsotope(isotope, abundance= 100.*perCent);
 
 G4Material* material = new G4Material(name, density, ncomponents=1);
 material->AddElement(element, massfraction=100.*perCent);

 return material;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::ConstructVolumes()
{
    // Cleanup old geometry
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    G4Box*
    worldBox = new G4Box("Container",                         //its name
                     fBoxSize/2,fBoxSize/2,fBoxSize/2);   //its dimensions

    G4NistManager* man = G4NistManager::Instance();
    G4Material* Air  = man->FindOrBuildMaterial("G4_AIR");

    fLBox = new G4LogicalVolume(worldBox,                     //its shape
                             Air,                 //its material
                             "World");  //its name
    fPBox = new G4PVPlacement(0,
                              G4ThreeVector(0, 0, 0),
                              "World",
                              fLBox,
                              nullptr,
                              false,
                              0);

    G4Material* vacuum = G4NistManager::Instance()->FindOrBuildMaterial( "G4_Galactic" );

    G4String sphName = "scoring";
    // orb to measure neutron flux
    fScoringSphere = new G4Sphere(sphName, 5*cm, 5*cm + 1., 0.0, 360*degree, 0.0, 180*degree);
    fLScoring = new G4LogicalVolume(fScoringSphere, vacuum, sphName);
    G4VPhysicalVolume* PhSphere = new G4PVPlacement(0,
                                                 G4ThreeVector(0, 0, 0),
                                                 fLScoring,
                                                 sphName,
                                                 fLBox,
                                                 false,
                                                 0);

    G4Material* W = man->FindOrBuildMaterial("G4_W");
    G4double startPos = -9*mm;
    for (int i = 0; i < 10; i++)
    {
        G4String name = &"plate" [ i];
        G4Box* plate = new G4Box(name,
                                 0.5*mm, 8*mm, 8*mm);
        G4LogicalVolume* LPlate = new G4LogicalVolume(plate,
                                                      W,
                                                      name);
        G4VPhysicalVolume* PhPlate = new G4PVPlacement(0,
                                                       G4ThreeVector(startPos + 2*i*mm, 0, 0),
                                                       LPlate,
                                                       name,
                                                       fLBox,
                                                       false,
                                                       0);
    }

    G4double z, a, density;
    G4String name, symbol;
    G4int ncomponents, natoms;

    a = 28.085*g/mole;
    G4Element* elSi  = new G4Element(name="Silicon",symbol="Si" , z= 14., a);

    a = 16.00*g/mole;
    G4Element* elO  = new G4Element(name="Oxygen"  ,symbol="O" , z= 8., a);

    density = 2.600*g/cm3;
    // quartz fiber
    G4Material* quartz = new G4Material(name="Water",density,ncomponents=2);
    quartz->AddElement(elSi, natoms=1);
    quartz->AddElement(elO, natoms=2);

    G4String torName = "quartz";
    G4Tubs* quartzSam = new G4Tubs(torName, 0, 5*mm, 5*mm, 0, 360*degree);
    G4LogicalVolume* LTor = new G4LogicalVolume(quartzSam, quartz, torName);
    G4VPhysicalVolume* PhTor = new G4PVPlacement(0,
                                                 G4ThreeVector(0, 0, 4*cm),
                                                 LTor,
                                                 torName,
                                                 fLBox,
                                                 false,
                                                 0);

    fLQuartz = LTor;
    fPQuartz = PhTor;

    PrintParameters();

    //always return the root volume
    //
    return fPBox;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::PrintParameters()
{
  G4cout << "\n The Box is " << G4BestUnit(fBoxSize,"Length")
         << " of " << fMaterial->GetName() 
         << "\n \n" << fMaterial << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial = 
     G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);
  
  if (pttoMaterial) { 
    if(fMaterial != pttoMaterial) {
      fMaterial = pttoMaterial;
      if(fLBox) { fLBox->SetMaterial(pttoMaterial); }
      G4RunManager::GetRunManager()->PhysicsHasBeenModified();
    }
  } else {
    G4cout << "\n--> warning from DetectorConstruction::SetMaterial : "
           << materialChoice << " not found" << G4endl;
  }              
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetSize(G4double value)
{
  fBoxSize = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
