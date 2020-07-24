# LIP Summer Internship 2020 - LOMAC simulation

Geant 4 application to simulate experimental setup to test calorimeter tile light yield response  

## How to get the code

- log into the pauli machines at LIP: ``ssh -XY username@pauli.ncg.ingrid.pt``
- go to your prefered working directory or create a new one
- clone the repository: ``git clone https://github.com/AnaLuisaCarvalho/estagio_lomac_sim.git``
- create a new branch: ``git checkout -b <name of your branch>``
  - a branch is a copy of the repository that you can change without interfering with the original repository 
- ``source setup.sh`` (does module load of geant4, cmake11 and root6)
- ``mkdir build``
- ``cd build``
- ``cmake -DGeant4_DIR=`which geant` ../``
 **or** ``cmake -DGeant4_DIR=<path to geant installation> <path to CMakeLists.txt> ``
- ``make``
  - The last two steps compile the code. 
  - The last one (``make``) needs to be done whenever something is changed in the .cc and .hh files
  - The preivous one needs to be done only when adding new files in the src/ or include/ directories. It also copies the vis.mac and run.mac from the main folder to the build folder
- ``./TileFCC``: will run with macro vis.mac and produce a graphical output. Do not use to run over a large number of events
**or**
- ``./TileFCC -m run.mac``: will not produce graphical output

- the following times you can just ``cd build`` (no need to recreate ``build`` directory)

## Keeping track of your work

It is a good practice to keep the remote copy of your repository up to date to what you have locally. This means commiting your code often and especially when making some major changes. To do that:

- go to the main project folder
- ``git add --all``
- ``git commit -m <explanotory message for your future self>``
- ``git push origin <name of your branch>``

This way even if you accidentally delete some file you will have a copy on the web!

## Output of the code

At the moment (July 2020, before internships started) the code creates a ROOT output file. This file contains a TTree with the following branches:

- Edep: total energy in eV deposited in the scintillator tile
- HitX/Y/Z: position in X/Y/Z in mm in the tile where the incident (primary) particle hit
- NScintPhotons: number of scintillation photons produced in the tile
- TileHitsEdep: vector quantity with the energy (in eV) of each of the scintillation photons 
- NWLSPhotons: number of wavelength shifiting photons produced in the fiber
- FiberHitsEdep: vector quantity with the energy (in eV) of each of the wave length shfiting photons produced in the fiber
- NPMTPhotons: number of photons hitting the photomultiplier

## Inputs of the code

The simulation takes as main physical inputs the emission spectrum of the scintillator tile, the absorption and emissions spectrums of the optical fiber. The spectrums are defined as a function of the photon energy. At the moment (July 2020, before internships started) these are simplified spectrums (step functions) that are directly defined in the TileFCCDetectorConstruction.cc file in the form of arrays:

- Energy range: {2.0,2.87,2.9,3.47} (in eV)
- Scintillator tile emissions spectrum: {0,0,1,1}
  - The numbers represent the relative emissions for each energy
- Fiber absorption spectrum: {9 m, 9 m, 0.1 mm, 0.1 mm}
  - The number represent the absorption length for each energy
- Fiber emission spectrum: {1,1,0,0}
  - Relative emission for each energy

Note that, for the fiber, the emission only happens for energies between 2.0 and 2.87 eV which are the energies for which the absorption length of the fiber is large (9 m). This makes sense because it means that the optical photons produced through wavelength shifting inside the fiber can travel long distances inside the fiber without being absorbed.
