function plot_distTargetOrigin()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

modRadius = 2.5;
noDist = 11;
distances = zeros(1,noDist);
dirStart1 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\testDistances";
dirStart2 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\testDistancesParameters";
dirEnd1 = "_nt_SampleWalls.csv";
dirEnd2 = "_nt_Parameters.csv";
distTargetorigin = -1;
noLastWall = zeros(1,noDist);
noCircleLastWall = zeros(1,noDist);
metric = "hits";
printBool = false;

for i = 1:noDist
    dir1 = dirStart1 + num2str(i-1) + dirEnd1;
    dir2 = dirStart2 +  num2str(i-1) + dirEnd2;
    M = csvread(dir1, 9, 0);
    lastWallHit = zeros(4,0);
    for k = 1:length(M)
        if (M(k,1) == 4)
            lastWallHit(:,end+1) = M(k,2:5);
        end
    end
    % mm->cm
    lastWallHit(1:3,:) = lastWallHit(1:3,:) / 10;
    noLastWall(i) = length(lastWallHit);
    [xCenter,zCenter,idx,maxPoints,noHits, avgE] = findCircle(lastWallHit, modRadius, metric, printBool);
    metric = "hits";
    noCircleLastWall(i) = maxPoints;
    M = csvread(dir2, 14, 0);   %% read parameters
    distances(i) = M(1,4);
end

% mm->cm
distances = distances / 10;

figure
hold on
grid on
yyaxis left
plotMatrix(1) = plot(distances,noLastWall,"k-");
yyaxis right
plotMatrix(2) = plot(distances,noCircleLastWall, "k-.");
xlabel('$\textrm{dist}_{\textrm{Target,Origin}}/\textrm{cm}$','FontSize',12)
yyaxis left
ylabel('$\textrm{No hits on fourth sample wall}$','FontSize',12)
yyaxis right
ylabel('$\textrm{No hits in optimal circle}$')
legend('$\textrm{Hits on fourth sample wall}$', '$\textrm{Hits inside optimal circle}$', 'Location', 'northwest')
titleHelp = {"$\textbf{Number of positron hits as a function}$", "$\textbf{of distance between target and origin}$"
    };
%title(titleHelp)

% f = fit(distTargetOrigin',noAnnihi','gauss2');
% X = min(distTargetOrigin);
% Y = max(distTargetOrigin);
% x = linspace(X,Y,1000);
% plot(x,f(x),'r')
% xline(50.5,'b')
% titleHelp1 = '$\textbf{Number of moderator-annihilation as a function}$';
% titleHelp2 =  '$\textbf{of distance between target and origin}$';
% titleHelp = {titleHelp1,titleHelp2};
% title(titleHelp,'FontSize',12)
% xlabel('$\textrm{dist}_{\textrm{Target,Origin}}/\textrm{cm}$','FontSize',12)
% ylabel('$\textrm{No annihilations}$','FontSize',12)
% %legend('$\textrm{Simulated values}$', '$\textrm{Gaussian fit}$', '$\textrm{No scaling}$' ,'Location','East')
% legend('$\textrm{Simulated values}$', '$\textrm{Gaussian fit}$','$\textrm{Default geometry}$')
% %saveas(gcf,"C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\Plots for presentation\P_dModerator.png")
end