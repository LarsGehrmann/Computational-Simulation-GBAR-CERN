%visualize the deposited energy in the moderator because Geant4 is not working properly with that

function plot_sampleWalls(modRadius, frontLength)

totalScore = 0;
noPos = 10^4;
posTable = load("\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\posTable.txt");
for i=1:noPos
    [sc,dist]= scoreEnergy(posTable(i,7), frontLength);
    totalScore = totalScore + sc;
end

fprintf("Total score of simulated positrons: " + totalScore + "\n");

set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');
saveDirStart = "C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\safe 4\Heatmaps\test\";
%saveDirStart = "C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\safe 5\Analysis Good hits\";
saveName = "goodHits";
saveDirEnd = ".png";

dir = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\Standard_nt_SampleWalls.csv";
dir = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\Standard_nt_SampleWalls.csv";
M = dlmread(dir, ',', 9, 0);
noHits = length(M);
wall0 = zeros(4,0);
wall1 = zeros(4,0);
wall2 = zeros(4,0);
wall3 = zeros(4,0);
wall4 = zeros(4,0);
avgE = zeros(1,5);
for k = 1:noHits
    switch M(k,1)
        case 0
            wall0(:,end+1) = M(k,2:5);
        case 1
            wall1(:,end+1) = M(k,2:5);
        case 2
            wall2(:,end+1) = M(k,2:5);
        case 3
            wall3(:,end+1) = M(k,2:5);
        case 4
            wall4(:,end+1) = M(k,2:5);
    end
end
% mm -> cm
wall0(1:3,:) = wall0(1:3,:)/10;
wall1(1:3,:) = wall1(1:3,:)/10;
wall2(1:3,:) = wall2(1:3,:)/10;
wall3(1:3,:) = wall3(1:3,:)/10;
wall4(1:3,:) = wall4(1:3,:)/10;


maxHits = 0;
maxE = 0;

wallNo = linspace(0,4,5);
nBins = 20*ones(5,1);
offset = [25,25,25,25,10];
% for i=1:5
%     if i==1
%         [maxHits, maxE] = plotWall(wallNo(i),wall0,nBins(i),offset(i), saveDirStart, saveName, saveDirEnd, modRadius, frontLength, maxHits, maxE)
%     elseif i == 2
%         [maxHits, maxE] = plotWall(wallNo(i),wall1,nBins(i),offset(i), saveDirStart, saveName, saveDirEnd, modRadius, frontLength, maxHits, maxE)
%     elseif i == 3
%         [maxHits, maxE] = plotWall(wallNo(i),wall2,nBins(i),offset(i), saveDirStart, saveName, saveDirEnd, modRadius, frontLength, maxHits, maxE)
%     elseif i == 4
%         [maxHits, maxE] = plotWall(wallNo(i),wall3,nBins(i),offset(i), saveDirStart, saveName, saveDirEnd, modRadius, frontLength, maxHits, maxE)
%     elseif i == 5
%         [maxHits, maxE] = plotWall(wallNo(i),wall4,nBins(i),offset(i), saveDirStart, saveName, saveDirEnd, modRadius, frontLength, maxHits, maxE)
%     end
% end

% close all
% for i=1:5
%     if i==1
%         [maxHits, maxE] = plotWall(wallNo(i),wall0,nBins(i),offset(i), saveDirStart, saveName, saveDirEnd, modRadius, frontLength, maxHits, maxE)
%     elseif i == 2
%         [maxHits, maxE] = plotWall(wallNo(i),wall1,nBins(i),offset(i), saveDirStart, saveName, saveDirEnd, modRadius, frontLength, maxHits, maxE)
%     elseif i == 3
%         [maxHits, maxE] = plotWall(wallNo(i),wall2,nBins(i),offset(i), saveDirStart, saveName, saveDirEnd, modRadius, frontLength, maxHits, maxE)
%     elseif i == 4
%         [maxHits, maxE] = plotWall(wallNo(i),wall3,nBins(i),offset(i), saveDirStart, saveName, saveDirEnd, modRadius, frontLength, maxHits, maxE)
%     elseif i == 5
%         [maxHits, maxE] = plotWall(wallNo(i),wall4,nBins(i),offset(i), saveDirStart, saveName, saveDirEnd, modRadius, frontLength, maxHits, maxE)
%     end
% end

plotWall(4,wall4,20,10, saveDirStart, saveName, saveDirEnd, modRadius, frontLength, maxHits, maxE)

end


