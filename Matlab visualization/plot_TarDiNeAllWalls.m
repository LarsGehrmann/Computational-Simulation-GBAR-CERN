function plot_TarDiNeAllWalls()

set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

offset = 10; % offset for fourth sample wall -10cm...10cm

dirStart1 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\testField";
dirStart2 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\testFieldParameters";
dirEnd1 = "_nt_SampleWalls.csv";
dirEnd2 = "_nt_Parameters.csv";

noScales = 13;


scales = zeros(noScales,1);
hits = zeros(3,noScales,4); % fieldType,scale,noSampleWall

fieldNames = ["BTarget","BDipole", "BNeon"];
noFields = length(fieldNames);
% noLastWall = zeros(length(fieldNames),noScales);
% noCircleLastWall = zeros(length(fieldNames),noScales);
% metric = "hits";
% printBool = false;
for i =1:noScales
    dir2 = dirStart2 + fieldNames(1) + "scaleRun" + num2str(i-1) + dirEnd2;
    M = csvread(dir2, 14, 0);   %% read parameters
    scales(i) = M(1,9);
end
for field=1:3
    for i = 1:noScales
        dir1 = dirStart1 + fieldNames(field)  + "scaleRun" + num2str(i-1) + dirEnd1;
        M = csvread(dir1, 9, 0);
        for k = 1:length(M)
            noWall = M(k,1);
            if noWall ~= 0
                hits(field,i,noWall) = hits(field,i,noWall) + 1;
            end
        end

    end
end

legendHelp = ["$\textrm{Hits on first wall}$","$\textrm{Hits on second wall}$","$\textrm{Hits on third wall}$","$\textrm{Hits on fourth wall}$"];
fieldNamesTitle = ["target coil}$","dipole coils}$","neon coils}$"];
colors = ["r", "b", "k", "m","c", "g", "y"];
hold on
for field=1:3
    figure
    for wall=1:4
        plot(scales,hits(field,:,wall),colors(wall))
        hold on
        grid on
        xlabel('$\textrm{scale}$')
        ylabel('$\textrm{No hits}$')
        titleHelp = {"$\textbf{Number of positron hits as a function of}$", ...
            "$\textbf{scaling of magnetic field from " + fieldNamesTitle(field)
            };
        legend(legendHelp,'Location','southoutside')
        title(titleHelp)
    end
    hold off
end

% figure('Renderer', 'painters', 'Position', [10 10 900 600])
% pbaspect([1 1 1])
% for field=1:length(fieldNames)
%     hold on
%     yyaxis left
%     plotMatrix(2*field-1) = plot(scales,noLastWall(field,:),colors(field) + "-");
%     yyaxis right
%     plotMatrix(2*field) = plot(scales,noCircleLastWall(field,:), colors(field) + "-.");
%     legendHelp(2*field-1) = string(fieldNames(field)) + "$\textrm{ fourth wall hits}$";
%     legendHelp(2*field) = string(fieldNames(field)) + "$\textrm{ circle hits}$";
% end
% hold off
% grid on
% xlabel('$\textrm{scale}$')
% yyaxis left
% ylabel('$\textrm{No hits on fourth sample wall}$')
% yyaxis right
% ylabel('$\textrm{No hits in optimal circle}$')
% grid on
% legend(plotMatrix,legendHelp,'Location','eastoutside')
% legendHelp = ["$B_{\textrm{Dipole}}$","$B_{\textrm{Neon}}$","$B_{\textrm{Solenoid}}$","$B_{\textrm{Target}}$","$E$"];
% titleHelp = {"$\textbf{Number of positron hits for different scalings}$", "$\textbf{of magnetic and electric fields with circle radius }r = $" + ...
%     string(modRadius) + "$\textbf{cm}$"};
% title(titleHelp)
end