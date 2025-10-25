#ifndef TASK2_DETECTOR_CONSTRUCTION_HH
#define TASK2_DETECTOR_CONSTRUCTION_HH 1

#include "G4VUserDetectorConstruction.hh"

namespace TASK2
{
	class DetectorConstruction : public G4VUserDetectorConstruction
	{
	public:
		DetectorConstruction() = default;
		~DetectorConstruction() override = default;

		G4VPhysicalVolume* Construct() override;

		G4LogicalVolume* GetGammaDetector() const { return fGammaDetector; }
		G4LogicalVolume* GetWorld() const { return fWorld; }

	private:
		G4LogicalVolume* fGammaDetector = nullptr;
		G4LogicalVolume* fWorld = nullptr;
	};
}


#endif // TASK2_DETECTOR_CONSTRUCTION_HH