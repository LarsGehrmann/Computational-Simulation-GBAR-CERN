function sample()

set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dir = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\OutputSample0_nt_Title7.csv";
M = csvread(dir, 11, 0);
noSamples = length(M);
fprintf("Number of samples: " + string(noSamples) + newline);
r = zeros(noSamples,3);
p = zeros(noSamples,3);
E = zeros(noSamples,1);

for i = 1:noSamples
    for j = 1:3 
        r(i,j) = M(i,j);
        p(i,j) = M(i,j+3);
    end
    E(i) = M(i,7);
end
%--------------------------------------------------------------%
%--------------------------------------------------------------%
figure
edges = logspace(-3,1,25);
Nbins = 50;
histfit(E,Nbins, 'gamma');
pd = fitdist(E,'Gamma');
xlim([10^-2,10])
hold on
grid on
legendHelp = {'Simulated values', 'Gamma fit with $a =$' + string(pd.a) + ' and $b = $' + string(pd.b)};
legend(legendHelp)
title('$\textbf{Kinetic energy of positrons}$', 'Fontsize', 12)
xlabel('$E / \textrm{MeV}$')
ylabel('$\textrm{No}$')
%--------------------------------------------------------------%
%--------------------------------------------------------------%
% nBins = 50;
% figure
% hist(r(:,1), nBins);
% grid on
% title("$\textbf{Distribution of spatial x-components of positrons}$")
%--------------------------------------------------------------%
%--------------------------------------------------------------%
figure
pts = linspace(-20, 20, 41);
N = histcounts2(r(:,2), r(:,3), pts, pts);
imagesc(pts, pts, N);
colorbar
axis equal
set(gca, 'XLim', pts([1 end]), 'YLim', pts([1 end]), 'YDir', 'normal');
xlabel('$y$/cm')
ylabel('$z$/cm')
title('Spatial occurence of positrons in $y$-$z$-plane')
%--------------------------------------------------------------%
%--------------------------------------------------------------%
% radial = sqrt(r(:,2).^2 + r(:,3).^2);
% figure
% nBins = 50;
% histfit(radial, nBins);
% radialParameters = fitdist(radial,'Normal');
% xlabel('$r$\cm')
% ylabel('$N$')
% legendHelp = {'Simulated values', 'Gaussian fit with $\mu =$' + string(radialParameters.mu) + ' and $\sigma = $' + string(radialParameters.sigma)};
% legend(legendHelp)
% grid on
% title('Radial distribution in $y$-$z$-plane')
%--------------------------------------------------------------%
%--------------------------------------------------------------%
figure
subplot(2,1,1)
nBins = 50;
histfit(r(:,2), nBins);
pd = fitdist(r(:,2),'Normal');
grid on
legendHelp = {'Simulated values', 'Gaussian fit with $\mu =$' + string(pd.mu) + ' and $\sigma = $' + string(pd.sigma)};
legend(legendHelp)
title("$\textbf{Distribution of spatial y-components of positrons}$")
%--------------------------------------------------------------%
subplot(2,1,2)
nBins = 50;
histfit(r(:,3), nBins);
pd = fitdist(r(:,3),'Normal');
grid on
legendHelp = {'Simulated values', 'Gaussian fit with $\mu =$' + string(pd.mu) + ' and $\sigma = $' + string(pd.sigma)};
legend(legendHelp)
title("$\textbf{Distribution of spatial z-components of positrons}$")
%--------------------------------------------------------------%
%--------------------------------------------------------------%
figure
subplot(3,1,1)
p(:,1) = 1+p(:,1);
%idx = (p(:,1) < 0);
%p(idx,1) = 0;
nBins = 50;
histfit(p(:,1), nBins,'exponential');
pd = fitdist(p(:,1),'exponential');
legendHelp = {'Simulated values', 'Exponential fit with $\mu =$' + string(pd.mu)};
legend(legendHelp)
xlim([0,1])
grid on
title("$\textbf{Distribution of momentum x-components of positrons}$")
% %--------------------------------------------------------------%
subplot(3,1,2)
nBins = 50;
histfit(p(:,2), nBins);
xlim([-1,1])
pd = fitdist(p(:,2),'Normal');
legendHelp = {'Simulated values', 'Gaussian fit with $\mu =$' + string(pd.mu) + ' and $\sigma = $' + string(pd.sigma)};
legend(legendHelp, 'Location', 'South')
grid on
title("$\textbf{Distribution of momentum y-components of positrons}$")
%--------------------------------------------------------------%
subplot(3,1,3)
nBins = 50;
histfit(p(:,3), nBins);
xlim([-1,1])
pd = fitdist(p(:,3),'Normal');
legendHelp = {'Simulated values', 'Gaussian fit with $\mu =$' + string(pd.mu) + ' and $\sigma = $' + string(pd.sigma)};
legend(legendHelp, 'Location', 'South')
grid on
title("$\textbf{Distribution of momentum z-components of positrons}$")
%--------------------------------------------------------------%
 end