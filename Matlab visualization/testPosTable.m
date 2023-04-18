clear all, clc, close all;
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');


dir = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\posTableNew.csv";
posTable = csvread(dir);
% mm -> cm
posTable(:,1:3) = posTable(:,1:3) / 10; 
avgE = 0;1
for i = 1:length(posTable)
    avgE = avgE + posTable(i,7);
end
avgE = avgE / i;
fprintf("Average energy of all positrons: " + avgE + "MeV \n");
ymin = min(posTable(:,2));
ymax = max(posTable(:,2));
zmin = min(posTable(:,3));
zmax = max(posTable(:,3));
fprintf("ymin: " + ymin + "cm, ymax: " + ymax + "cm\n");
fprintf("zmin: " + zmin + "cm, zmax: " + zmax + "cm\n");