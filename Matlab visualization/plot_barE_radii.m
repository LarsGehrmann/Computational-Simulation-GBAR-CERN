function plot_barE_radii()

set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');
offset = 10;
xlabelString = '$x / \textrm{cm}$';
ylabelString = '$z / \textrm{cm}$';
dir = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\Standard_nt_SampleWalls.csv";
allHits = csvread(dir, 9, 0);
wallHit = zeros(4,0);
for k = 1:length(allHits)
    if (allHits(k,1) == 4)
        wallHit(:,end+1) = allHits(k,2:5);
    end
end
% mm->cm
wallHit(1:3,:) = wallHit(1:3,:) / 10;
modRadius = [3.5,3.0,2.5];
metric = "hits";
printBool = false;
xCenters = zeros(1,3);
zCenters = zeros(1,3);
avgEVec = zeros(1,3);
for i=1:3
    [xCenter,zCenter,idx,maxPoints,noHits, avgE] = findCircle(wallHit, modRadius(i), metric, printBool);
    xCenters(i) = xCenter;
    zCenters(i) = zCenter;
    avgEVec(i) = avgE
end

ECircle = zeros(0,3);
for i=1:3
    circleCount = 1;
    for j=1:length(wallHit)
        if sqrt( (xCenters(i) - wallHit(1,j))^2 + (zCenters(i) - wallHit(3,j))^2 ) <= modRadius(i)
            ECircle(circleCount,i) = wallHit(4,j);
            circleCount = circleCount + 1;
        end
    end
end


colors = ["r","k","b"];




figure
plot(wallHit(1,:), wallHit(3,:), 'k.','MarkerSize', 5)
hold on
grid on
th = linspace(0,2*pi,1000);
legendHelp = "$\textrm{Hits}$";
for i=1:3
    xCircleHits = modRadius(i) * cos(th) + xCenters(i);
    zCircleHits = modRadius(i) * sin(th) + zCenters(i);
    plot(xCircleHits,zCircleHits,colors(i)+'-')
    legendHelp(i+1) = "$r = $" + string(modRadius(i)) + "$\textrm{cm}$";
end
legend(legendHelp,'Location','Northwest')
xlim([-offset,offset])
xlabel(xlabelString)
ylabel(ylabelString)
axis equal
titleHelp = {"$\textbf{Comparison between circle placements for different radii}$"
    };
title(titleHelp)


clear legendHelp
edges = logspace(-2,1,50);

figure('Renderer', 'painters', 'Position', [10 10 1000 500])
%pbaspect([1 1 1])
circleHitsPrint = zeros(1,3);
histHits = zeros(3,49);
for i=1:3
    helpCircleLog = ECircle(:,i)~= 0;
    helpCircle = ECircle(helpCircleLog,i);
    circleHitsPrint(i) = length(helpCircle);
    histHits(i,:) = histcounts(helpCircle,edges);
    legendHelp(i) = "$r = $" + string(modRadius(i)) + "$\textrm{cm}$";
end

fprintf("")
barWidth = 0.55;
barDiag = bar(log10(edges(1:end-1)),histHits','hist');
hold on
%set(barDiag,'BarLayout','grouped')
%set(barDiag,'BarWidth',barWidth);
%end
set(gca,'Xtick',-2:1); %// adjust manually; values in log scale
set(gca,'Xticklabel',10.^get(gca,'Xtick')); %// use labels with linear values
grid on
xlabel('$E / \textrm{MeV}$')
ylabel('$\textrm{No}$')
legend(legendHelp,'Location','Northeast')
titleHelp = {"$\textbf{Comparison between energy distribution inside optimal circle for different circle radii}$"
    };
title(titleHelp)
fprintf("Distance between center of largest and smallest circle: " + string(sqrt((xCenters(end)-xCenters(1))^2 + ...
    (zCenters(end)-zCenters(1))^2 )) + "cm\n");
fprintf("Number of hits in circles from smallest to largest circle: " + string(circleHitsPrint(3)) + ", " + string(circleHitsPrint(2)) + ", " +string(circleHitsPrint(1)) + "\n")
fprintf("Average energy in circles from smallest to largest circle: " + string(avgEVec(3)) + ", " + string(avgEVec(2)) + ", " +string(avgEVec(1)) + "\n")
end