# Geant4TileFCC

Geant 4 application to simulate experimental setup to test FCC calorimeter tile light yield response  

Starting from geant4 example B1: https://gitlab.cern.ch/geant4/geant4/tree/master/examples/basic/B1

At fermi/pauli (following http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/GettingStarted/makeFile.html):
- module load geant
- module load cmake newest version
- cd build
- cmake -DGeant4_DIR=<path to geant installation> <path to CMakeLists.txt> or -DGeant4_DIR=`which geant`
- make

Compile GODDeSS:
- 