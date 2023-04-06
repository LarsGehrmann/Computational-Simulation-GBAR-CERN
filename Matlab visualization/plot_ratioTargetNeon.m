function plot_ratioTargetNeon()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dirStart = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\ratioTargetNeonScaleNe";
dirEnd1 = "_nt_SampleWalls.csv";
dirEnd2 = "Parameters0_nt_Parameters.csv";

noNeonScales = 4;
neonScale = zeros(1,noNeonScales);
lastWallHit = zeros(noNeonScales,0);
stdDev = zeros(noNeonScales,0);
ratio = -1;

for i=1:noNeonScales
    j = 0.5;
    ratioCount = 1;
    while true
        if j < 0.999
            dir1 = dirStart + string(i) + ".000000ratio"  + string(j) + "000000" + dirEnd1;
            dir2 = dirStart + string(i) + ".000000ratio"  + string(j) + "00000" + dirEnd2;
        elseif round(10*j) == 10
            dir1 = dirStart + string(i) + ".000000ratio"  + string(j) + ".0000000" + dirEnd1;
            dir2 = dirStart + string(i) + ".000000ratio"  + string(j) + ".000000" + dirEnd2;
        else
            dir1 = dirStart + string(i) + ".000000ratio"  + string(j) + "000000" + dirEnd1;
            dir2 = dirStart + string(i) + ".000000ratio"  + string(j) + "00000" + dirEnd2;
            a = 3;
        end
        try
            M = csvread(dir1, 8, 0);
            if i == 1
                lastWallHit(:,end+1) = zeros(noNeonScales,1);
                stdDev(:,end+1) = zeros(noNeonScales,1);
            end
            lastWallHit(i,ratioCount) = 0;
            stdDev(i,ratioCount) = 0;
            tempStore = zeros(3,1);
            for k = 1:length(M)
                if M(k,1) == 4
                    lastWallHit(i,ratioCount) = lastWallHit(i,ratioCount) + 1;
                    tempStore(:,lastWallHit(i,ratioCount)) = [M(k,2), M(k,3), M(k,4)] / 10; % mm -> cm
                end
            end
            stdDev(i,ratioCount) = std(tempStore(1,:)) + std(tempStore(3,:));
            M = csvread(dir2, 14, 0);   %% read parameters
            neonScale(i) = M(1,7);
            ratio(ratioCount) = M(1,9) / neonScale(i);
        catch ME
            break
        end
        ratioCount = ratioCount + 1;
        j = j + 0.1;
    end
end


colors = ["b","g","r","c","m"];
figure
hold on
grid on
legendHelp = "empty";
for i = 1:noNeonScales
    plot(ratio,lastWallHit(i,:),colors(i))
    legendHelp(i) = "scaleNeon = " + string(neonScale(i));
end
xlabel('$\textrm{scaleTarget / scaleNeon}$')
ylabel('$\textrm{No. hits}$')
legend(legendHelp)
title('$\textbf{Number of hits vs. ratio}$')

figure
hold on
grid on
for i = 1:noNeonScales
    plot(ratio,stdDev(i,:),colors(i))
    legendHelp(i) = "scaleNeon = " + string(neonScale(i));
end
xlabel('$\textrm{scaleTarget / scaleNeon}$')
ylabel('$(\sigma_x + \sigma_z) / \textrm{cm}$')
legend(legendHelp)
title('$\textbf{Standard deviation vs. ratio}$')

% figure
% hold on
% for field=1:5
%     plot(scale(field,:),lastWallHit(field,:), colors(field))
% end

%plot(distTarOri, lastWallHit, 'kX')
% f = fit(distTarOri',lastWallHit','gauss2');
% X = min(distTarOri);
% Y = max(distTarOri);
% x = linspace(X,Y,1000);
% plot(x,f(x),'r')
% grid on
% legendHelp = ["$B_{\textrm{Dipole}}$","$B_{\textrm{Neon}}$","$B_{\textrm{Solenoid}}$","$B_{\textrm{Target}}$","$E$"];
% legend(legendHelp,'Location','Southwest')
% xlabel('$\textrm{scale}$')
% ylabel('$\textrm{Number of hits}$')
% titleHelp = {"$\textbf{Number of positron hits for different scalings}$", "$\textbf{of magnetic and electric fields}$"};
% title(titleHelp)
end
