%visualize the deposited energy in the moderator because Geant4 is not working properly with that

function plot_sampleWalls()

saveName = "Default";
xmin = -1;
xmax = 4;
zmin = -2;
zmax = 3;

set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dir = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\Standard_nt_SampleWalls.csv";
M = dlmread(dir, ',', 9, 0);
noHits = length(M);
wall0 = zeros(4,0);
wall1 = zeros(4,0);
wall2 = zeros(4,0);
wall3 = zeros(4,0);
wall4 = zeros(4,0);
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


saveDirStart = "C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\safe 4\Heatmaps\";
saveDirEnd = ".png";

nBins = 25;
figure
EGrid = zeros(nBins,nBins);
EGridCount = zeros(nBins,nBins);
offset = 25; % walls from -offset...offset
step = 2;
for k = 1:length(wall0)
    y = 2*floor(wall0(2,k)/2);
    i = floor((y+offset)/step) + 1;
    z = 2*floor(wall0(3,k)/2);
    j = floor((z+offset)/step) + 1;
    EGrid(i,j) = EGrid(i,j) + wall0(4,k);
    EGridCount(i,j) = EGridCount(i,j) + 1;
end
for i = 1:nBins
    for j = 1:nBins
        if EGridCount(i,j) ~= 0
            EGrid(i,j) = EGrid(i,j) / EGridCount(i,j);
        end
    end
end

edges = {(-offset:step:offset),(-offset:step:offset)}; 
data = [wall0(2,:); wall0(3,:)]';
hh3 = hist3(data, edges)';
y = -offset:offset;
z = -offset:offset;
imagesc(y,z,hh3)
set(gca,'YDir','normal')
xlabel('$y / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
colorbar
titleHelp = {"$\textbf{Positrons passing through zeroth sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall0(1,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + string(0) + saveDirEnd;
saveas(gcf,saveDir);

figure
data = [EGrid(2,:); EGrid(3,:)]';
y = -offset:offset;
z = -offset:offset;
imagesc(y,z,EGrid)
set(gca,'YDir','normal')
xlabel('$y / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
colorbar
titleHelp = {"$\bar{E} \textbf{ of positrons passing through zeroth sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall0(1,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + string(0) + saveDirEnd;
saveas(gcf,saveDir);
clear y z 

%-------------------------------------------------------------------------%
% figure
% edges = {(-25:2:25),(-25:2:25)}; 
% data = [wall1(2,:); wall1(3,:)]';
% hh3 = hist3(data, edges)';
% y = -25:25;
% z = -25:25;
% imagesc(y,z,hh3)
% set(gca,'YDir','normal')
% xlabel('$y / \textrm{cm}$')
% ylabel('$z / \textrm{cm}$')
% colorbar
% titleHelp = {"$\textbf{Positrons passing through first sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall1(1,:)))};
% title(titleHelp,'FontSize',14)
% saveDir = saveDirStart + saveName + string(1) + saveDirEnd;
% saveas(gcf,saveDir);
% 
% figure
% edges = {(-25:2:25),(-25:2:25)}; 
% data = [wall2(2,:); wall2(3,:)]';
% hh3 = hist3([wall2(2,:)', wall2(3,:)'],'Edges', edges)';
% y = -25:25;
% z = -25:25;
% imagesc(y,z,hh3)
% set(gca,'YDir','normal')
% xlabel('$y / \textrm{cm}$')
% ylabel('$z / \textrm{cm}$')
% colorbar
% titleHelp = {"$\textbf{Positrons passing through second sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall2(1,:)))};
% title(titleHelp,'FontSize',14)
% 
% saveDir = saveDirStart + saveName + string(2) + saveDirEnd;
% saveas(gcf,saveDir);
% 
% figure
% edges = {(-25:2:25),(-25:2:25)}; 
% data = [wall3(1,:); wall3(3,:)]';
% hh3 = hist3(data, edges)';
% y = -25:25;
% z = -25:25;
% imagesc(y,z,hh3)
% set(gca,'YDir','normal')
% xlabel('$x / \textrm{cm}$')
% ylabel('$z / \textrm{cm}$')
% colorbar
% titleHelp = {"$\textbf{Positrons passing through third sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall3(1,:)))};
% title(titleHelp,'FontSize',14)
% saveDir = saveDirStart + saveName + string(3) + saveDirEnd;
% saveas(gcf,saveDir);
% clear y z
% 
% 
% 
% 
% 
% 
% 
% 
% 
% % figure
% % edges = {(-10:1:10),(-10:1:10)}; 
% % data = [wall4(1,:); wall4(3,:)]';
% % hh3 = hist3(data, edges)';
% % y = -10:10;
% % z = -10:10;
% % imagesc(y,z,hh3)
% % set(gca,'YDir','normal')
% % xlabel('$x / \textrm{cm}$')
% % ylabel('$z / \textrm{cm}$')
% % colorbar
% % titleHelp = {"$\textbf{Positrons passing through fourth sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall4(1,:)))};
% % title(titleHelp,'FontSize',14)

% -----------------------------------------------------------------------------------------------------------------------------------------------------------
nBins = 20;
EGrid = zeros(nBins,nBins);
EGridCount = zeros(nBins,nBins);
offset = 10; % walls from -offset...offset
step = 1;
for k = 1:length(wall4)
    x = floor(wall4(1,k));
    i = floor((x+offset)/step)+1;
    z = floor(wall4(3,k));
    j = floor((z+offset)/step)+1;
    EGrid(i,j) = EGrid(i,j) + wall4(4,k);
    EGridCount(i,j) = EGridCount(i,j) + 1;
end
for i = 1:nBins
    for j = 1:nBins
        if EGridCount(i,j) ~= 0
            EGrid(i,j) = EGrid(i,j) / EGridCount(i,j);
        end
    end
end

figure
edges = {(-10:1:10),(-10:1:10)}; 
data = [wall4(1,:); wall4(3,:)]';
hh3 = hist3(data, edges)';
y = -10:10;
z = -10:10;
imagesc(y,z,hh3)
set(gca,'YDir','normal')
xlabel('$x / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
colorbar
titleHelp = {"$\textbf{Positrons passing through fourth sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall4(1,:)))};
title(titleHelp,'FontSize',14)

figure
data = [EGrid(1,:); EGrid(3,:)]';
x = -offset:offset;
z = -offset:offset;
imagesc(y,z,EGrid)
set(gca,'YDir','normal')
xlabel('$x / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
colorbar
titleHelp = {"$\bar{E} \textbf{ of positrons passing through fourth sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall4(1,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + string(0) + "E" +  saveDirEnd;
saveas(gcf,saveDir);




% -----------------------------------------------------------------------------------------------------------------------------------------------------------
smallHits = 0;
for i=1:length(wall4)
    x = wall4(1,i);
    z = wall4(3,i);
    if x > xmin && x < xmax
        if z > zmin && z < zmax
                    smallHits = smallHits + 1;

        end
    end
end
fprintf("Number of hits for x in [" + string(xmin) + "," + string(xmax) + "] and z in [" + string(zmin) + "," + string(zmax) + "]: ");
fprintf(string(smallHits) + "\n");

fprintf("Avg. 0th wall, (x,y,z)/cm: " + string(mean(wall0(1,:))) + ", " + string(mean(wall0(2,:))) +  ", " + string(mean(wall0(3,:))) + "\n");
fprintf("Avg. 1st wall, (x,y,z)/cm: " + string(mean(wall1(1,:))) + ", " + string(mean(wall1(2,:))) +  ", " + string(mean(wall1(3,:))) + "\n");
fprintf("Avg. 2nd wall, (x,y,z)/cm: " + string(mean(wall2(1,:))) + ", " + string(mean(wall2(2,:))) +  ", " + string(mean(wall2(3,:))) + "\n");
fprintf("Avg. 3rd wall, (x,y,z)/cm: " + string(mean(wall3(1,:))) + ", " + string(mean(wall3(2,:))) +  ", " + string(mean(wall3(3,:))) + "\n");
fprintf("Avg. 4th wall, (x,y,z)/cm: " + string(mean(wall4(1,:))) + ", " + string(mean(wall4(2,:))) +  ", " + string(mean(wall4(3,:))) + "\n");

saveDir = saveDirStart + saveName + string(4) + saveDirEnd;
saveas(gcf,saveDir);
end