function eDepBar()

set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

eDepParticle = zeros(3,3); % tungsten, neon, copper; gammas, electrons, positrons
noPairProd = zeros(3,3); % tungsten, neon, copper; Target, Moderator, ModeratorEnd
noAnnihi = zeros(3,3); % tungsten, neon, copper; Target, Moderator, ModeratorEnd
materialString = ['Tungsten', 'Neon', 'Copper'];


dirMatrix = ["\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\eDepBarTungstenValues0_nt_Title1.csv", "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\eDepBarTungstenParameters0_nt_Title3.csv";
    "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\eDepBarNeonValues1_nt_Title1.csv", "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\eDepBarNeonParameters1_nt_Title3.csv";
    "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\eDepBarCopperValues2_nt_Title1.csv",              "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\eDepBarCopperParameters2_nt_Title3.csv"];

for i=1:3   % for every material
    M = csvread(dirMatrix(i,1), 14, 0);
    for j = 1:3 % for every particle
        eDepParticle(i,j) = M(1,j+1);
    end
    for j = 1:3 % for every thing (target, moderator, moderator end)
        noPairProd(i,j) = M(1,4 + 2 *j);
        noAnnihi(i,j) = M(1,3 + 2 * j);
    end
end
eDepParticle = eDepParticle / 10^7;


figure
bar(1:3,eDepParticle)

set(gca, 'XTickLabel',{'Tungsten','Neon','Copper'})
set(gca,'YScale','log')
grid on
lgd = legend('$\gamma$','$e^{-}$','$e^{+}$');
legend('Location','Eastoutside')
lgd.Title.String = '$\textbf{Energy deposited by:}$';
lgd.FontSize = 10;
lgd.Title.FontSize = 12;
ylabel('$\bar{E}_{\textrm{dep}} / \textrm{MeV}$')
titleHelp = {"$\textbf{Average energy deposition in the}$","$\textbf{moderator for different particles}$"}
%title(titleHelp,'FontSize', 15)

% figure
% bar(1:3,noPairProd)
% set(gca, 'XTickLabel',{'Tungsten','Neon','Copper'})
% set(gca,'YScale','log')
% grid on
% lgd = legend('$\textrm{Target}$','$\textrm{Moderator}$','$\textrm{End of moderator}$');
% legend('Location','Eastoutside')
% lgd.Title.String = '$\textbf{Pair-production in:}$';
% lgd.FontSize = 10;
% lgd.Title.FontSize = 12;
% ylabel('$\textrm{No. of events}$')
% title('$\textbf{Number of pair-production}$','FontSize', 15)

% figure
% bar(1:3,noAnnihi)
% set(gca, 'XTickLabel',{'Tungsten','Neon','Copper'})
% set(gca,'YScale','log')
% grid on
% lgd = legend('$\textrm{Target}$','$\textrm{Moderator}$','$\textrm{End of moderator}$');
% legend('Location','Eastoutside')
% lgd.Title.String = '$\textbf{Annihilation in:}$';
% lgd.FontSize = 10;
% lgd.Title.FontSize = 12;
% ylabel('$\textrm{No. of events}$')
% title('$\textbf{Number of annihilations}$','FontSize', 15)



end