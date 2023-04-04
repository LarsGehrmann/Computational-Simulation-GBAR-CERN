

clear all; close all; clc

set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');


%dirStart = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\eDep_distTarMod_";
%dirEnd = ".txt";

dir = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\AA0_nt_Title1.csv";

M = csvread(dir,7,0);
size(M)
noPos = M(end,2)