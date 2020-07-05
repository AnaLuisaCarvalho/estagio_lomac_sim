# Geant4TileFCC

Geant 4 application to simulate experimental setup to test FCC calorimeter tile light yield response  

At fermi/pauli machines: 
- source setup.sh (does module load of geant4, cmake11 and root6)
- mkdir build
- cd build
- ``cmake -DGeant4_DIR=`which geant` ../``
 **or** ``cmake -DGeant4_DIR=<path to geant installation> <path to CMakeLists.txt> ``
- ``make``
  - The last two steps compile the code. 
  - The last one (``make``) needs to be done whenever something is changed in the .cc and .hh files
  - The preivous one needs to be done only when adding new files in the src/ or include/ directories. It also copies the vis.mac and run.mac from the main folder to the build folder
- ``./TileFCC``: will run with macro vis.mac and produce a graphical output. Do not use to run over a large number of events
**or**
- ``./TileFCC -m run.mac``: will not produce graphical output