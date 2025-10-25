
#include "../include/DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Scintillation.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"


#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4Mag_UsualEqRhs.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"

#include "G4VSolid.hh"

#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4PVReplica.hh"
#include "G4UserLimits.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4GenericMessenger.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"
#include "G4SystemOfUnits.hh"


#include "G4SubtractionSolid.hh"
#include "G4BooleanSolid.hh"


namespace TASK2
{
	G4VPhysicalVolume* DetectorConstruction::Construct()
	{



		// construct our detectors here

        // Get nist material manager
        G4NistManager* nist = G4NistManager::Instance();


		// Start with constructing the world:
        G4double worldSize = 1 * m;
        //G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");
        G4Material* air = nist->FindOrBuildMaterial("G4_AIR");

        auto solidWorld = new G4Box("World",
            worldSize / 2,
            worldSize / 2,
            worldSize);

        auto logicWorld = new G4LogicalVolume(solidWorld,
            air,
            "World");

        auto physWorld = new G4PVPlacement(nullptr,
            G4ThreeVector(), 
            logicWorld, 
            "World", 
            nullptr, 
            false, 
            0);

//---------------------Detector construction------------------------
        G4String name, symbol;
        G4double a, z;
        G4double density, fractionmass;
        G4int nel, ncomponents;


    //---------------------NaI construction---------------------
        a = 22.989 * g / mole;
        G4Element* elNa = new G4Element("Natrium", "Na", z=11., a);
        a = 126.904 * g / mole;
        G4Element* elI = new G4Element("Iodium", "I", z=53., a); 

        density = 3.67 * g / cm3;
        G4Material* NaI = new G4Material("NaI", density, ncomponents = 2);

        NaI->AddElement(elNa, 1);
        NaI->AddElement(elI, 1);

    //---------------------LSO construction---------------------

        a = 174.96 * g / mole;
        G4Element* elLu = new G4Element("Lutetium", "Lu", z=71., a);
        a = 28.085 * g / mole;
        G4Element* elSi = new G4Element("Silicium", "Si", z=14., a);
        a = 16.00 * g / mole;
        G4Element* elO = new G4Element(name = "Oxygen", symbol = "O", z = 8., a);

        density = 7.4 * g / cm3;
        G4Material* LSO = new G4Material("LSO", density, ncomponents = 3);

        LSO->AddElement(elLu, 2);
        LSO->AddElement(elSi, 1);
        LSO->AddElement(elO,  5);

        
    //---------------------scintillator construction---------------------     
        G4ThreeVector pos0 = G4ThreeVector(0, 0, 0);
        G4double shape0_D = 3. * cm;
        G4double shape0_Z = 4. * cm;
        G4Material* sciMaterial = NaI;
        //G4Box* solidShape0 = new G4Box("Shape0", 0.5 * shape0_XY, 0.5 * shape0_XY, 0.5 * shape0_Z);
        auto solidShape0 = new G4Tubs("Shape0",
            0, 
            shape0_D / 2.0,
            shape0_Z / 2.0,
            0.0,
            360.0 * deg);
        G4LogicalVolume* logicShape0 = new G4LogicalVolume(solidShape0, sciMaterial, "Shape0");
        new G4PVPlacement(0, pos0, logicShape0, "Shape0", logicWorld, false, 0);

    //---------------------collimator construction---------------------

        // collimator material
        G4Material* tungsten = nist->FindOrBuildMaterial("G4_Al");

        //collimator size
        G4double plate_XY = 3. * cm; 
        G4double pltThickness = 1. * mm;

        //collimator geometry
        auto solidPlate = new G4Box("Plate",
            plate_XY / 2, 
            plate_XY / 2,
            pltThickness / 2.0
        );

        G4LogicalVolume* logicPlt = new G4LogicalVolume(solidPlate, tungsten, "Plate");

        // collimator position and rotation
        G4double pltZ = (pltThickness / 2);

        // place the collimator in the world
        G4ThreeVector posPlt = G4ThreeVector(0, 0, - ((shape0_Z + pltThickness) / 2 + 5 * mm));
        new G4PVPlacement(0, posPlt, logicPlt, "Plate", logicWorld, false, 0);



//---------------------colourization---------------------  

        G4Colour grey(0.5, 0.5, 0.5);
        G4Colour yellow(1.0, 1.0, 0.0);
        G4Colour black(0.0, 0.0, 0.0);


        G4VisAttributes* VisAtt_1 = new G4VisAttributes(yellow);
        VisAtt_1->SetForceSolid(true);
        logicShape0->SetVisAttributes(VisAtt_1);

        G4VisAttributes* VisAtt_2 = new G4VisAttributes(grey);
        VisAtt_2->SetForceSolid(true);
        logicPlt->SetVisAttributes(VisAtt_2);

        //setting scintillator as scoring volume
        fGammaDetector = logicShape0;
        fWorld = logicWorld;

        return physWorld;
    }

}