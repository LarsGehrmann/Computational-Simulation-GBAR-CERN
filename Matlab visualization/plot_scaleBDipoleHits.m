function plot_scaleBDipoleHits()

saveName = "test";

set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dirStart1 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\dipoleSecondWall";
dirStart2 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\dipoleSecondWallParameters";
dirEnd1 = "_nt_SampleWalls.csv";
dirEnd2 = "_nt_Parameters.csv";



wallHit = zeros(4,0);

i = 1;
while true
    dir1 = dirStart1 + num2str(i-1) + dirEnd1;
    dir2 = dirStart2 + num2str(i-1) + dirEnd2;
    try
        M = csvread(dir1, 8, 0);
        wallHit(:,end+1) = zeros(4,1);
        for k = 1:length(M)
            wallNo = M(k,1);
            if wallNo ~= 0    
                wallHit(wallNo,i) = wallHit(wallNo,i) + 1;
            end
        end
        M = csvread(dir2, 14, 0);   %% read parameters
        scaleBDipole(i) = M(1,6);
    catch ME
        break
    end
    i = i + 1;
end
fprintf("Number of data points: " + string(i) + "\n")

saveDirStart = "C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\safe 4\";
saveDirEnd = ".png";


plotHelp = ['b','g','r','c'];
figure
hold on
for i = 1:4
    plot(scaleBDipole,wallHit(i,:),plotHelp(i));
end
grid on
xlabel('$\textrm{scale}B_{\textrm{Dipole}}$')
ylabel('$\textrm{No hits}$')
xlim([0.8 3.1])
legend('$\textrm{First wall}$','$\textrm{Second wall}$','$\textrm{Third wall}$','$\textrm{Fourth wall}$','Location','East')
titleHelp = {"$\textbf{Number of hits for different scaling of}$", "$\textbf{dipole coils magnetic field for scaleBTarget = 2}$"};
title(titleHelp)



% figure
% edges = {(-25:2:25),(-25:2:25)};
% data = [wall2(2,:); wall2(3,:)]';
% hh3 = hist3(data, edges);
% y = -25:25;
% z = -25:25;
% imagesc(y,z,hh3)
% set(gca,'YDir','normal')
% xlabel('$y / \textrm{cm}$')
% ylabel('$z / \textrm{cm}$')
% colorbar
% titleHelp = {"$\textbf{Positrons passing through zeroth sample wall}$", "$\textbf{Total positrons: } $" + string(length(wall0(1,:)))};
% title(titleHelp,'FontSize',14)
% saveDir = saveDirStart + saveName + string(0) + saveDirEnd;
% saveas(gcf,saveDir);

end