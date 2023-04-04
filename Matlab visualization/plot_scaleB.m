function plot_scaleB()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dirStart1 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\scaleBValues";
dirStart2 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\scaleBParameters";
dirEnd1 = "_nt_Title1.csv";
dirEnd2 = "_nt_Title3.csv";
scaleB = -1;
i = 1;
while true
    dir1 = dirStart1 + num2str(i-1) + dirEnd1;
    dir2 = dirStart2 + num2str(i-1) + dirEnd2;
    try
        M = csvread(dir1, 14, 0);
        noAnnihi(i) = M(1,7); % annihilations in moderator
        M = csvread(dir2, 9, 0);
        scaleB(i) = M(1,5);
    catch ME
        break
    end
    i = i + 1;
end
figure
plot(scaleB, noAnnihi , 'kX')
hold on
grid on
f = fit(scaleB',noAnnihi','gauss2');
X = min(scaleB);
Y = max(scaleB);
x = linspace(X,Y,1000);
plot(x,f(x),'r')
xline(1,'b')
titleHelp1 = '$\textbf{Number of moderator-annihilation as a}$';
titleHelp2 =  '$\textbf{function of scaling of magnetic field}$';
titleHelp = {titleHelp1,titleHelp2};
title(titleHelp,'FontSize',12)
xlabel('$B_{\textrm{scale}}$','FontSize',12)
ylabel('$\textrm{No annihilations}$','FontSize',12)
legend('$\textrm{Simulated values}$', '$\textrm{Gaussian fit}$', '$\textrm{No scaling}$' ,'Location','East')
%saveas(gcf,"C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\Plots for presentation\P_dModerator.png")
end