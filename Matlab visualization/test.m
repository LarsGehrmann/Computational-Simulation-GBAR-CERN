clc; clear all; close all



elField = load("\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\elField.TAB");
n = length(elField);
elField = [elField, zeros(n,1)];
for i=1:n
    elField(i,7) = norm(elField(i,4:6));
end
[maxElField, maxIdx] = max(elField(:,7))





% magDir(1) = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\magFieldDipole.txt";
% magDir(2) = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\magFieldNeon.txt";
% magDir(3) = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\magFieldTarget.txt";
% magDir(4) = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\magFieldSolenoid.txt";
% magField = load(magDir(1));
% n = length(magField);
% for i=2:4
%     newMag = load(magDir(i));
%     magField(:,4:6) = magField(:,4:6) + newMag(:,4:6);
% end
% 
% magField = [magField, zeros(n,1)];
% 
% for i=1:n
%     magField(i,7) = norm(magField(i,4:6));
% end
% 
% [maxFieldNorm,maxIdx] = max(magField(:,7))
% 
% totField = load("\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\magField.TAB");
% [maxFieldTot, maxIdxTot] = max(totField(:,4:6))

a = 3;