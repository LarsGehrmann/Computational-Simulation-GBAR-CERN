function plot_Annihis()

set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dir = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\OutputAnnihis0_nt_Title9.csv";
M = csvread(dir, 5, 0);
noAnnihis = length(M);
annihis = zeros(20,20);
annihisModFront = 0;
for k = 1:noAnnihis
    if M(k) > 999 && M(k) < 2000
        annihisModFront = annihisModFront + 1;
        i = floor((M(k)-1000)/20);
        j = mod(M(k)-1000,20);
        annihis(i+1,j+1) = annihis(i+1,j+1) + 1;
    end
end
fprintf("Number of total annihis: " + string(noAnnihis) + newline);
fprintf("Number of annihis in moderator front: " + string(annihisModFront) + newline);

size(annihis);
%--------------------------------------------------------------%
xStart = -10;   % cm
zStart = -10;
dx = 1;         % cm
dz = 1;
imagesc([-10 10],[-10 10],annihis); % cm
c = colorbar;
c.Label.String = 'No. annihlations';
xlabel('$x / \textrm{cm}$')
ylabel('$z / \textrm{cm}$')
titleHelp = '$\textbf{Annihilation counts in the moderator front }(50 \mu \textrm{m})$';
title(titleHelp,'Fontsize', 14)
end