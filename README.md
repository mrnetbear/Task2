# Geant4 Scintillator Detector Simulation

## Project Overview

This project implements a scintillator detector simulation using CERN Geant4. The simulation models gamma radiation interaction with different scintillator materials (NaI and LSO) and includes collimator geometry for beam shaping.

## Project Structure

The code is organized into standard Geant4 user action classes:

- **DetectorConstruction**: Defines the geometry including scintillator, plate, and world volume
- **PhysicsList**: Implements electromagnetic physics processes
- **PrimaryGeneratorAction**: Generates gamma particles with dual energy sources (661 keV and 1461 keV)
- **ActionInit**: Initializes all user action classes
- **RunAction**: Manages run-level operations and data output
- **EventAction**: Handles event-level data accumulation
- **SteppingAction**: Processes step-by-step particle tracking

## Key Features

- **Dual Energy Source**: Simulates gamma rays at 661 keV and 1461 keV with equal probability
- **Multiple Scintillator Materials**: Supports both NaI and LSO scintillators
- **Collimator System**: Includes aluminum plate for beam definition
- **Data Output**: Stores energy deposition and position data in ROOT format
- **Visualization**: Compatible with Geant4 visualization systems

## Geometry Components

- **Scintillator**: Cylindrical detector (3cm diameter × 4cm height)
- **Plate**: Aluminum plate with defined aperture
- **World Volume**: 1m³ air-filled container

## Build Requirements

- Geant4 (version 11.0 or higher)
- CMake (version 3.8 or higher)
- C++ compiler with C++11 support
- ROOT (for data analysis)

## Building the Project

```bash
mkdir build
cd build
cmake ..
make -j4
```

## Usage

### Interactive Mode
```bash
./task2
```

### Batch Mode
```bash
./task2 macro.mac
```

## Output Data

The simulation generates ROOT files containing:
- Deposited energy in scintillator
- Interaction positions (X, Y, Z coordinates)
- Source energy identification

## Physics Processes

The simulation includes:
- Electromagnetic interactions (Compton scattering, photoelectric effect, pair production)
- Particle transportation
- Energy deposition tracking

## Configuration

Key parameters can be modified in the source files:
- Scintillator material (NaI/LSO) in `DetectorConstruction.cc`
- Gamma energies in `PrimaryGeneratorAction.cc`
- Geometry dimensions in `DetectorConstruction.cc`

## License

This project is intended for educational and research purposes.