function plot_sigmaPos_P()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dirStart1 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\sigmaPosValues";
dirStart2 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\sigmaPosParameters";
dirEnd1 = "_nt_Title1.csv";
dirEnd2 = "_nt_Title3.csv";
sigmaPos = -1;
i = 1;
while true
    dir1 = dirStart1 + num2str(i-1) + dirEnd1;
    dir2 = dirStart2 + num2str(i-1) + dirEnd2;
    try
        M = csvread(dir1, 7, 0);    % read values
        eDepTot(i) = M(end,3) * 10^6;        % convert MeV -> eV
        n = M(end,1);       % largest event number
        M = csvread(dir2, 8, 0);    % read parameters
        sigmaPos(i) = M(1,3);
    catch ME
        break
    end
    i = i + 1;
end
noElectrons = 10^(ceil(log10(n)))
eDepRel = eDepTot / noElectrons;
P = reqW(eDepRel);
figure
plot(sigmaPos, P, 'kX')
hold on
grid on
% [X,Y,sigma] = myAvg(sigmaPos, P);
% plot(X,Y,'k')
titleHelp1 = '$\textbf{Required cooling power as a function of}$';
titleHelp2 =  '$\textbf{locational standard deviation}$';
titleHelp = {titleHelp1,titleHelp2};
title(titleHelp,'FontSize',12)
xlabel('$\sigma_{\textrm{Pos}} / \textrm{mm}$','FontSize',12)
ylabel('$P / \textrm{W}$','FontSize',12)
% legendHelp = "$\textrm{Mean-fit: } \mu=$" + num2str(Y(1)) + ", $\sigma=$" + num2str(sigma);
% legend('$\textrm{Simulated values}$', legendHelp,'Location','NorthWest')
saveas(gcf,"C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\Plots for presentation\sigmaPos_P.png")
end