%visualize the deposited energy in the moderator because Geant4 is not working properly with that

function plot_sampleWalls()
close all
clc
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


saveDirStart = "C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\safe 4\Heatmaps\";
saveDirEnd = ".png";





% 0th wall -------------------------------------------------------------------------%
nBins = 2;
nBins = [nBins,nBins];
figure
% EGrid = zeros(nBins+1,nBins+1);
% EGridCount = zeros(nBins+1,nBins+1);
offset = 25; % walls from -offset...offset
step = 2*offset / (nBins(1)-1);
% for k = 1:length(wall0)
%     y = 2*floor(wall0(2,k)/2) + step/2;
%     i = floor((y+offset)/step) + 2;
%     z = 2*floor(wall0(3,k)/2)+ step/2;
%     j = floor((z+offset)/step) + 2;
%     EGrid(i,j) = EGrid(i,j) + wall0(4,k);
%     EGridCount(i,j) = EGridCount(i,j) + 1;
% end
% for i = 1:nBins+1
%     for j = 1:nBins+1
%         if EGridCount(i,j) ~= 0
%             EGrid(i,j) = EGrid(i,j) / EGridCount(i,j);
%         end
%     end
% end
edges = -offset:step:offset;
edges = {edges,edges};
data = [wall0(2,:); wall0(3,:)]';
hh3 = hist3(data,'Edges',edges)';
hh3 = hist3(data,'nbins',nBins)';
size(hh3)
%y = -offset:2:offset;
y = cell2mat(edges(1));
z = cell2mat(edges(2));
imagesc(y,z,hh3)
set(gca,'YDir','normal')
xlabel('$y / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$N \textrm{ hits}$','Interpreter','Latex');
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
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$\bar{E} / \textrm{MeV}$','Interpreter','Latex');
titleHelp = {"$\bar{E} \textbf{ of positrons passing through zeroth sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall0(1,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + string(0) + "E" +  saveDirEnd;
saveas(gcf,saveDir);
clear y z

% 1st -------------------------------------------------------------------------%
nBins = 25;
figure
EGrid = zeros(nBins+1,nBins+1);
EGridCount = zeros(nBins+1,nBins+1);
offset = 25; % walls from -offset...offset
step = 2*offset / nBins;
for k = 1:length(wall1)
    y = 2*floor(wall1(2,k)/2);
    i = floor((y+offset)/step) + 2;
    z = 2*floor(wall1(3,k)/2);
    j = floor((z+offset)/step) + 2;
    EGrid(i,j) = EGrid(i,j) + wall1(4,k);
    EGridCount(i,j) = EGridCount(i,j) + 1;
end

for i = 1:nBins+1
    for j = 1:nBins+1
        if EGridCount(i,j) ~= 0
            EGrid(i,j) = EGrid(i,j) / EGridCount(i,j);
        end
    end
end
edges = {(-offset:step:offset),(-offset:step:offset)};
data = [wall1(2,:); wall1(3,:)]';
hh3 = hist3(data, edges)';
y = -offset:2:offset;
z = -offset:2:offset;
imagesc(y,z,hh3)
set(gca,'YDir','normal')
xlabel('$y / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$N \textrm{ hits}$','Interpreter','Latex');
titleHelp = {"$\textbf{Positrons passing through first sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall1(1,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + string(1) + saveDirEnd;
saveas(gcf,saveDir);

figure
data = [EGrid(2,:); EGrid(3,:)]';
y = -offset:offset;
z = -offset:offset;
imagesc(y,z,EGrid)
set(gca,'YDir','normal')
xlabel('$y / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$\bar{E} / \textrm{MeV}$','Interpreter','Latex');
titleHelp = {"$\bar{E} \textbf{ of positrons passing through first sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall1(1,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + string(1) + "E" +  saveDirEnd;
saveas(gcf,saveDir);
clear y z

% 2nd wall -------------------------------------------------------------------------%
nBins = 25;
figure
EGrid = zeros(nBins+1,nBins+1);
EGridCount = zeros(nBins+1,nBins+1);
offset = 25; % walls from -offset...offset
step = 2*offset / nBins;
for k = 1:length(wall2)
    y = 2*floor(wall2(2,k)/2);
    i = floor((y+offset)/step) + 2;
    z = 2*floor(wall2(3,k)/2);
    j = floor((z+offset)/step) + 2;
    EGrid(i,j) = EGrid(i,j) + wall2(4,k);
    EGridCount(i,j) = EGridCount(i,j) + 1;
end
for i = 1:nBins+1
    for j = 1:nBins+1
        if EGridCount(i,j) ~= 0
            EGrid(i,j) = EGrid(i,j) / EGridCount(i,j);
        end
    end
end
edges = {(-offset:step:offset),(-offset:step:offset)};
data = [wall2(2,:); wall2(3,:)]';
hh3 = hist3(data, edges)';
y = -offset:2:offset;
z = -offset:2:offset;
imagesc(y,z,hh3)
set(gca,'YDir','normal')
xlabel('$y / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$N \textrm{ hits}$','Interpreter','Latex');
titleHelp = {"$\textbf{Positrons passing through second sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall2(1,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + string(2) + saveDirEnd;
saveas(gcf,saveDir);

figure
data = [EGrid(2,:); EGrid(3,:)]';
y = -offset:2:offset;
z = -offset:2:offset;
imagesc(y,z,EGrid)
set(gca,'YDir','normal')
xlabel('$y / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$\bar{E} / \textrm{MeV}$','Interpreter','Latex');
titleHelp = {"$\bar{E} \textbf{ of positrons passing through second sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall2(1,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + string(2) + "E" +  saveDirEnd;
saveas(gcf,saveDir);
clear y z
% 3rd wall -------------------------------------------------------------------------%
nBins = 25;
figure
EGrid = zeros(nBins+1,nBins+1);
EGridCount = zeros(nBins+1,nBins+1);
offset = 25; % walls from -offset...offset
step = 2*offset / nBins;
for k = 1:length(wall3)
    x = 2*floor(wall3(1,k)/2);
    i = floor((x+offset)/step) + 2;
    z = 2*floor(wall3(3,k)/2);
    j = floor((z+offset)/step) + 2;
    EGrid(i,j) = EGrid(i,j) + wall3(4,k);
    EGridCount(i,j) = EGridCount(i,j) + 1;
end
for i = 1:nBins+1
    for j = 1:nBins+1
        if EGridCount(i,j) ~= 0
            EGrid(i,j) = EGrid(i,j) / EGridCount(i,j);
        end
    end
end
edges = {(-offset:step:offset),(-offset:step:offset)};
data = [wall3(1,:); wall3(3,:)]';
hh3 = hist3(data, edges)';
x = -offset:2:offset;
z = -offset:2:offset;
imagesc(x,z,hh3)
set(gca,'YDir','normal')
xlabel('$x / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$N \textrm{ hits}$','Interpreter','Latex');
titleHelp = {"$\textbf{Positrons passing through third sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall2(1,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + string(3) + saveDirEnd;
saveas(gcf,saveDir);

figure
data = [EGrid(1,:); EGrid(3,:)]';
x = -offset:offset;
z = -offset:offset;
imagesc(x,z,EGrid)
set(gca,'YDir','normal')
xlabel('$x / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$\bar{E} / \textrm{MeV}$','Interpreter','Latex');
titleHelp = {"$\bar{E} \textbf{ of positrons passing through third sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall2(1,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + string(3) + "E" +  saveDirEnd;
saveas(gcf,saveDir);
clear x z

% 4th wall -----------------------------------------------------------------------------------------------------------------------------------------------------------
nBins = 20;
EGrid = zeros(nBins+1,nBins+1);
EGridCount = zeros(nBins+1,nBins+1);
offset = 10; % walls from -offset...offset
step = 2*offset / nBins;
for k = 1:length(wall4)
    x = floor(wall4(1,k));
    i = floor((x+offset)/step)+2;
    z = floor(wall4(3,k));
    j = floor((z+offset)/step)+2;
    EGrid(i,j) = EGrid(i,j) + wall4(4,k);
    EGridCount(i,j) = EGridCount(i,j) + 1;
end
for i = 1:nBins+1
    for j = 1:nBins+1
        if EGridCount(i,j) ~= 0
            EGrid(i,j) = EGrid(i,j) / EGridCount(i,j);
        end
    end
end

figure
edges = {(-10:1:10),(-10:1:10)};
data = [wall4(1,:); wall4(3,:)]';
hh3 = hist3(data, edges)';
x = -10:10;
z = -10:10;
imagesc(x,z,hh3)
set(gca,'YDir','normal')
xlabel('$x / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$N \textrm{ hits}$','Interpreter','Latex');
titleHelp = {"$\textbf{Positrons passing through fourth sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall4(1,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + string(4) + saveDirEnd;
saveas(gcf,saveDir);

figure
data = [EGrid(1,:); EGrid(3,:)]';
x = -offset:offset;
z = -offset:offset;
imagesc(x,z,EGrid)
set(gca,'YDir','normal')
xlabel('$x / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$\bar{E} / \textrm{MeV}$','Interpreter','Latex');
titleHelp = {"$\bar{E} \textbf{ of positrons passing through fourth sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall4(1,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + string(4) + "E" +  saveDirEnd;
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


