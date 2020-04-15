# Geant4TileFCC

Geant 4 application to simulate experimental setup to test FCC calorimeter tile light yield response  

Starting from geant4 example B1: https://gitlab.cern.ch/geant4/geant4/tree/master/examples/basic/B1

At fermi/pauli (following http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/GettingStarted/makeFile.html):
- source setup.sh (does module load of geant4, cmake11 and root6)
- cd build
- cmake -DGeant4_DIR=<path to geant installation> <path to CMakeLists.txt> or -DGeant4_DIR=`which geant`
- make
- ./TileFCC -m run.mac -u vis.mac 

Current strategy for building the experimental setup:
- TileFCCDetectorConstruction.cc is the file where we collect all the pieces and place them in the correct position
- Each piece should be a class that returns a G4LogicalVolume (see TileFCCTile.cc as an example)
- In order to be able to access this class from inside TileFCCDetectorConstruction.cc we must create a shared library. In the CMakeLists file add:
  - add_library(TileFCCTile SHARED
  src/TileFCCTile.cc)
  - Link it: target_link_libraries(TileFCC ${Geant4_LIBRARIES} TileFCCTile)


GODDeSS repository: https://git.rwth-aachen.de/3pia/forge/goddess-package (not used, for inspiration only)
