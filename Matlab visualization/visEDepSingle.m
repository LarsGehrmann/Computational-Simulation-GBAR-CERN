%visualize the deposited energy in the moderator because Geant4 is not working properly with that

function visEDepSingle()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

figure
dir = "\\wsl.localhost\ubuntu\home\lars\Geant4\Task1\build\eDep_ShowSingle.txt";
M = dlmread(dir, ',', 3, 0);
n = round(sqrt(length(M')));
E = zeros(n,n);          % [MeV]->[a.u.] deposited energy
for i = 1:n
    for j = 1:n
        E(i,j) = M(n * (i-1) + j,4);
    end
end
imagesc([0 19],[0 19],E);
%axis manual
c = colorbar;
c.Label.String = "[a.u.]";
set(c,'FontSize',14);
xlabel('$x / \textrm{mm}$')
ylabel('$y / \textrm{mm}$')
titleHelp = "$\textbf{Total deposited energy in the copper foil }$";
title(titleHelp,'Fontsize', 14)
saveas(gcf,"C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\Plots for presentation\eDep_ShowSingle.png")
end