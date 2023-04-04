%visualize the deposited energy in the moderator because Geant4 is not working properly with that

function plot_Sample4Fields()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

fieldNames = ["BDipole", "BNeon", "BSolenoid", "BTarget", "E"];

dirStart1 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\";
dirStart2 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\";
dirEnd1 = "_nt_SampleWalls.csv";
dirEnd2 = "_nt_Parameters.csv";

scale = zeros(5,0);
lastWallHit = zeros(5,0);
fieldType = 1;
for field=1:5
    i = 1;
    while true
        dir1 = dirStart1 + fieldNames(field)  + num2str(i-1) + dirEnd1;
        dir2 = dirStart2 + fieldNames(field) + "Parameters" + num2str(i-1) + dirEnd2;
        try
            M = csvread(dir1, 8, 0);
            lastWallHit(field,i) = 0;
            for k = 1:length(M)
                if (M(k,1) == 4)
                    lastWallHit(field,i) = lastWallHit(field,i) + 1; % hits on last sampling wall
                end
            end
            M = csvread(dir2, 14, 0);   %% read parameters
            scale(field,i) = M(1,5 + field);
            M(1,5 + field);
        catch ME
            break
        end
        i = i + 1;
    end
end


colors = ["b","g","r","c","m"];
figure
hold on
for field=1:5
    plot(scale(field,:),lastWallHit(field,:), colors(field))
end

%plot(distTarOri, lastWallHit, 'kX')
% f = fit(distTarOri',lastWallHit','gauss2');
% X = min(distTarOri);
% Y = max(distTarOri);
% x = linspace(X,Y,1000);
% plot(x,f(x),'r')
grid on
legendHelp = ["$B_{\textrm{Dipole}}$","$B_{\textrm{Neon}}$","$B_{\textrm{Solenoid}}$","$B_{\textrm{Target}}$","$E$"];
legend(legendHelp,'Location','Southwest')
xlabel('$\textrm{scale}$')
ylabel('$\textrm{Number of hits}$')
titleHelp = {"$\textbf{Number of positron hits for different scalings}$", "$\textbf{of magnetic and electric fields}$"};
title(titleHelp)
end