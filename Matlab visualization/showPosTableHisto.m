function showPosTableHisto()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dir = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\posTable.txt";


M = load(dir);
n = 10^4;
E = M(1:n,7);
avgE = round(sum(E) / n * 1000) / 1000;
edges = logspace(-2,1,50);

figure
hist(E, edges)
set(gca,'xscale','log')
xlim([10^-2,10])
grid on
titleHelp = {"$\textbf{Kinetic energy of sampled positrons}$","$\textbf{Total number of positrons: }$" + n + "$\textbf{; } \bar{E} = $" + avgE + "$\textbf{MeV}$"};
title(titleHelp, 'Fontsize', 12)
xlabel('$E / \textrm{MeV}$')
ylabel('$\textrm{No}$')

end