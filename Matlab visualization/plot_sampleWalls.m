%visualize the deposited energy in the moderator because Geant4 is not working properly with that

function plot_sampleWalls()

saveName = "test";

set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dir = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\Standard0_nt_SampleWalls.csv";
M = dlmread(dir, ',', 8, 0);
noHits = length(M);
wall0 = zeros(3,0);
wall1 = zeros(3,0);
wall2 = zeros(3,0);
wall3 = zeros(3,0);
wall4 = zeros(3,0);
for k = 1:noHits
    switch M(k,1)
        case 0
            wall0(:,end+1) = M(k,2:4);
        case 1
            wall1(:,end+1) = M(k,2:4);
        case 2
            wall2(:,end+1) = M(k,2:4);
        case 3
            wall3(:,end+1) = M(k,2:4);
        case 4
            wall4(:,end+1) = M(k,2:4);
    end
end
wall0 = wall0/10;    % mm -> cm
wall1 = wall1/10;
wall2 = wall2/10;
wall3 = wall3/10;
wall4 = wall4/10;

saveDirStart = "C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\safe 4\Heatmaps\";
saveDirEnd = ".png";

figure
edges = {(-25:2:25),(-25:2:25)}; 
data = [wall0(2,:); wall0(3,:)]';
hh3 = hist3(data, edges)';
y = -25:25;
z = -25:25;
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
edges = {(-25:2:25),(-25:2:25)}; 
data = [wall1(2,:); wall1(3,:)]';
hh3 = hist3(data, edges)';
y = -25:25;
z = -25:25;
imagesc(y,z,hh3)
set(gca,'YDir','normal')
xlabel('$y / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
colorbar
titleHelp = {"$\textbf{Positrons passing through first sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall1(1,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + string(1) + saveDirEnd;
saveas(gcf,saveDir);

figure
edges = {(-25:2:25),(-25:2:25)}; 
data = [wall2(2,:); wall2(3,:)]';
hh3 = hist3([wall2(2,:)', wall2(3,:)'],'Edges', edges)';
y = -25:25;
z = -25:25;
imagesc(y,z,hh3)
set(gca,'YDir','normal')
xlabel('$y / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
colorbar
titleHelp = {"$\textbf{Positrons passing through second sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall2(1,:)))};
title(titleHelp,'FontSize',14)

saveDir = saveDirStart + saveName + string(2) + saveDirEnd;
saveas(gcf,saveDir);

figure
edges = {(-25:2:25),(-25:2:25)}; 
data = [wall3(1,:); wall3(3,:)]';
hh3 = hist3(data, edges)';
y = -25:25;
z = -25:25;
imagesc(y,z,hh3)
set(gca,'YDir','normal')
xlabel('$x / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
colorbar
titleHelp = {"$\textbf{Positrons passing through third sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall3(1,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + string(3) + saveDirEnd;
saveas(gcf,saveDir);

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

xmin = -4;
xmax = 1;
zmin = -3;
zmax = 2;
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

fprintf("Average x-component for positrons hitting the fourth wall: " + string(mean(wall4(1,:)) + "\n"))
fprintf("Average y-component for positrons hitting the second wall: " + string(mean(wall2(2,:)) + "\n"))
fprintf("Average z-component for positrons hitting the fourth wall: " + string(mean(wall4(3,:)) + "\n"))

saveDir = saveDirStart + saveName + string(4) + saveDirEnd;
saveas(gcf,saveDir);
end