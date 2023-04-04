function plot_distTargetOrigin()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dirStart1 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\distTargetOriginValues";
dirStart2 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\distTargetOriginParameters";
dirEnd1 = "_nt_Title1.csv";
dirEnd2 = "_nt_Title3.csv";
distTargetorigin = -1;
i = 1;
while true
    dir1 = dirStart1 + num2str(i-1) + dirEnd1;
    dir2 = dirStart2 + num2str(i-1) + dirEnd2;
    try
        M = csvread(dir1, 14, 0);    % values
        noAnnihi(i) = M(1,7); % annihilations in moderator
        M = csvread(dir2, 10, 0);     % parameters
        distTargetOrigin(i) = M(1,5);
    catch ME
        break
    end
    i = i + 1;
end
distTargetOrigin = distTargetOrigin / 10; % mm -> cm
i
figure
plot(distTargetOrigin, noAnnihi , 'kX')
hold on
grid on
f = fit(distTargetOrigin',noAnnihi','gauss2');
X = min(distTargetOrigin);
Y = max(distTargetOrigin);
x = linspace(X,Y,1000);
plot(x,f(x),'r')
xline(50.5,'b')
titleHelp1 = '$\textbf{Number of moderator-annihilation as a function}$';
titleHelp2 =  '$\textbf{of distance between target and origin}$';
titleHelp = {titleHelp1,titleHelp2};
title(titleHelp,'FontSize',12)
xlabel('$\textrm{dist}_{\textrm{Target,Origin}}/\textrm{cm}$','FontSize',12)
ylabel('$\textrm{No annihilations}$','FontSize',12)
%legend('$\textrm{Simulated values}$', '$\textrm{Gaussian fit}$', '$\textrm{No scaling}$' ,'Location','East')
legend('$\textrm{Simulated values}$', '$\textrm{Gaussian fit}$','$\textrm{Default geometry}$')
%saveas(gcf,"C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\Plots for presentation\P_dModerator.png")
end