%visualize the deposited energy in the moderator because Geant4 is not working properly with that

function plot_sampleWallsScore(modRadius, L_plus)

set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');
saveDirStart = "C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\safe 5\Score";
saveName = "test";
saveDirEnd = ".png";

dir = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\Standard_nt_modFrontAnnihis.csv";
M = dlmread(dir, ',', 9, 0);
noHits = length(M);
annihis = M(:,1:3);
fprintf("Total number of annihilations in moderator: " + length(annihis))
annihis = annihis / 10; % mm->cm

% read moderator height;
dir = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\StandardParameters0_nt_Parameters.csv";
M = dlmread(dir, ',', 14, 0);
modHeight = M(1,5) / 10; %% mm->cm
dist = annihis(:,2) - modHeight;

scoreRow = score(dist,L_plus);
annihis = [annihis,scoreRow];
nBins = 20;
offset = 10;

plotWallScore(annihis,nBins,offset, saveDirStart, saveName, saveDirEnd, modRadius, L_plus)

end


