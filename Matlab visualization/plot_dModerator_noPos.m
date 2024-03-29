function plot_dModerator_noPos()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dirStart1 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\dModeratorValuesNeon";
dirStart2 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\dModeratorParametersNeon";
dirEnd1 = "_nt_Title1.csv";
dirEnd2 = "_nt_Title3.csv";

dirStart3 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\dModeratorValuesTungsten";
dirStart4 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\dModeratorParametersTungsten";
dirEnd3 = "_nt_Title1.csv";
dirEnd4 = "_nt_Title3.csv";
dModerator = 0;
i = 1;
while true
    dir1 = dirStart1 + num2str(i-1) + dirEnd1;
    dir2 = dirStart2 + num2str(i-1) + dirEnd2;
    try     
        % read values for Neon
        M = csvread(dir1, 6, 0);
        noPos(1,i) = M(end,2);    % stores number of positrons
        n = M(end,1);       % largest event number
        M = csvread(dir2, 8, 0);
        dModerator(i) = M(1,2);
    catch ME
        break
    end
    i = i + 1;
end
k = 1;
while true
    dir3 = dirStart3 + num2str(i-1) + dirEnd3;
    dir4 = dirStart4 + num2str(i-1) + dirEnd4;
    try     
        % read values for Tungsten
        M = csvread(dir3, 6, 0);
        noPos(2,k) = M(end,2);    % stores number of positrons
        n = M(end,1);       % largest event number
        M = csvread(dir4, 8, 0);
    catch ME
        break
    end
    i = i + 1;
    k = k + 1;
end
figure
hold on
plot(dModerator, noPos(1,:), 'rX')
plot(dModerator, noPos(2,:), 'bX')
grid on
%[X,Y,r2] = myLinReg(dModerator, noPosEff);
%plot(X,Y,'k')
titleHelp1 = '$\textbf{Number of positron annihilations as a function of}$';
titleHelp2 =  '$\textbf{moderator thickness}$';
titleHelp = {titleHelp1,titleHelp2};
title(titleHelp,'FontSize',12)
xlabel('$d_{\textrm{Moderator}} / \textrm{mm}$','FontSize',12)
ylabel('$\textrm{Number of annihilations}$','FontSize',12)
legend('$Ne$', '$W$')
%legendHelp = '$\textrm{Linear fit: }' + "r^2=$ "+ num2str(r2);
%legend('$\textrm{Simulated values}$', legendHelp ,'Location','NorthEast')
saveas(gcf,"C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\Plots for presentation\dModeratorEff.png")
end