%visualize the deposited energy in the moderator because Geant4 is not working properly with that

function plot_testFields(modRadius)
fontSizeLegend = 13;
fontSizeAxes = 13;
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

fieldNames = ["BDipole", "BNeon", "BSolenoid", "BTarget", "E"];
offset = 10; % offset for fourth sample wall -10cm...10cm

dirStart1 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\testField";
dirStart2 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\testFieldParameters";
dirEnd1 = "_nt_SampleWalls.csv";
dirEnd2 = "_nt_Parameters.csv";

noScales = 13;


scales = zeros(noScales,1);
noLastWall = zeros(length(fieldNames),noScales);
noCircleLastWall = zeros(length(fieldNames),noScales);
metric = "hits";
printBool = false;
for field=1:length(fieldNames)
    for i = 1:noScales
        dir1 = dirStart1 + fieldNames(field)  + "scaleRun" + num2str(i-1) + dirEnd1;
        dir2 = dirStart2 + fieldNames(field) + "scaleRun" + num2str(i-1) + dirEnd2;
        M = csvread(dir1, 9, 0);
        lastWallHit = zeros(4,0);
        for k = 1:length(M)
            if (M(k,1) == 4)
                lastWallHit(:,end+1) = M(k,2:5);
            end
        end
        % mm->cm
        lastWallHit(1:3,:) = lastWallHit(1:3,:) / 10;
        noLastWall(field,i) = length(lastWallHit);
        [xCenter,zCenter,idx,maxPoints,noHits, avgE] = findCircle(lastWallHit, modRadius, metric, printBool);
        metric = "hits";
        noCircleLastWall(field,i) = maxPoints;
        M = csvread(dir2, 14, 0);   %% read parameters
        scales(i) = M(1,5 + field);
    end
end


colors = ["r", "b", "k", "m","c", "g", "y"];
figure('Renderer', 'painters', 'Position', [10 10 900 600])
pbaspect([1 1 1])
for field=1:length(fieldNames)
    hold on
    yyaxis left
    plotMatrix(2*field-1) = plot(scales,noLastWall(field,:),colors(field) + "-");
    yyaxis right
    plotMatrix(2*field) = plot(scales,noCircleLastWall(field,:), colors(field) + "-.");
    legendHelp(2*field-1) = string(fieldNames(field)) + "$\textrm{ fourth wall hits}$";
    legendHelp(2*field) = string(fieldNames(field)) + "$\textrm{ circle hits}$";
end
hold off
grid on
xlabel('$\textrm{scale}$')
yyaxis left
ylabel('$\textrm{No hits on fourth sample wall}$')
yyaxis right
ylabel('$\textrm{No hits in optimal circle}$')
grid on
legend(plotMatrix,legendHelp,'Location','eastoutside')
%legendHelp = ["$B_{\textrm{Dipole}}$","$B_{\textrm{Neon}}$","$B_{\textrm{Solenoid}}$","$B_{\textrm{Target}}$","$E$"];
titleHelp = {"$\textbf{Number of positron hits for different scalings}$", "$\textbf{of magnetic and electric fields with circle radius }r = $" + ...
    string(modRadius) + "$\textbf{cm}$"};
%title(titleHelp)
hLegend = findobj(gcf, 'Type', 'Legend');
set(hLegend,'FontSize', fontSizeLegend)
hAxis = findobj(gcf,'Type','Axes')
set(hAxis,'FontSize', fontSizeAxes)
end