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
annihis = annihis / 10; % mm->cm



plotWallScore(annihis,20,10, saveDirStart, saveName, saveDirEnd, modRadius, L_plus)

end


