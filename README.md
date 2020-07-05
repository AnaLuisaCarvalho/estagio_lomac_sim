# LIP Summer Internship 2020 - LOMAC simulation

Geant 4 application to simulate experimental setup to test calorimeter tile light yield response  

## How to get the code

- log into the pauli machines at LIP: ssh -XY <username>@pauli.ncg.ingrid.pt
- go to your prefered working directory or create a new one
- clone the repository: ``git clone https://github.com/AnaLuisaCarvalho/estagio_lomac_sim.git``
- create a new branch: ``git checkout -b <name of your branch>``
  - a branch is a copy of the repository that you can change without interfering with the original repository 
- source setup.sh (does module load of geant4, cmake11 and root6)
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

- got to the main project folder
- ``git add --all``
- ``git commit -m <explanotory message for your future self>``
- ``git push origin <name of your branch>``

This way even if you accidentally delete some file you will have a copy on the web!