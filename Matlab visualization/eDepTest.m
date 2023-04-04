% Test to obtain total energy stored

clc; clear all; close all
noel = 10^4;
M = dlmread("\\wsl.localhost\ubuntu\home\lars\Geant4\Task1\build\eDepTest.txt", ',', 3, 0);

eDep = sum(M(:,4))
eDepRel = eDep / noel
P = reqW(eDepRel*10^6)   % 10^6 for MeV -> eV