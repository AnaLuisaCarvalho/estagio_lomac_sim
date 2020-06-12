#!/bin/bash 
# --- Start Batch System Options ---
# Allow the taks to inherit the submitter environment 
#....#$ -V  

# Transfer input file (MyMacro.c) to the execution machine 
#$ -v SGEIN1=../TileFCC

# Transfer output files from the execution machine
#....#$ -v SGEOUT1=../build/outputNtupleTileFCC.root

# By default a job will run o lipq queue. If you are authorized to use other queues a user should uncomment this option specifying the queue_name.
#....#$ -l lipq                                                                                                         
#$ -q lipq                                                                                                              

# Send me an e-mail when finished                                                                                       
#$ -M ana.luisa.mc@ua.pt                              

cd TileFCC
ls

module load geant/4.10.06
module load cmake/3.11.2
module load root/6.18.04

rm -rf build
mkdir build
cd build

cmake -DGeant4_DIR=`which geant` ../
make
./TileFCC -m run.mac
