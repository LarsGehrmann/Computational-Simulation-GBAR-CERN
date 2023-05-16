%visualize the deposited energy in the moderator because Geant4 is not working properly with that

function visEDepAll()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');
dist = [.0001 2 5 10];      % [mm] distance between Target and moderator
noDist = length(dist);


dirStart = "\\wsl.localhost\ubuntu\home\lars\Geant4\Task1\build\eDep_ShowAll_";
distString = num2str(dist(1));
dirEnd = ".txt";
dir = dirStart + distString + dirEnd;
M = dlmread(dir, ',', 3, 0);
n = round(sqrt(length(M')));
E = zeros(n,n);          % [MeV]->[a.u.] deposited energy
figure
for k = 1:noDist
    subplot(2,2,k);
    dirStart = "\\wsl.localhost\ubuntu\home\lars\Geant4\Task1\build\eDep_ShowAll_";
    if rem(dist(k),10) == 0 % if avgEnergy is whole number
       distString = num2str(round(dist(k))) + ".";
    else
        distString = num2str(dist(k));
    end
    dirEnd = ".txt";
    dir = dirStart + distString + dirEnd;
    M = dlmread(dir, ',', 3, 0);
    if k==1
        maxE = max(M(:,4));
    end
    for i = 1:n
        for j = 1:n
            E(i,j) = M(n * (i-1) + j,4);
        end
    end
    imagesc(1:19,1:19,E);
    c = colorbar;
    %caxis([0 maxE])
    xlabel('$x / \textrm{mm}$')
    ylabel('$y / \textrm{mm}$')
    c.Label.String = "[a.u.]";
    set(c,'FontSize',14);
    titleHelp1 = "$\textrm{dist} = $";
    titleHelp2 = num2str(dist(k));
    titleHelp3 = "$\textrm{mm}$";
    titleHelp = titleHelp1 + titleHelp2 + titleHelp3;
    title(titleHelp,'Fontsize', 12)
end
titleHelp1 = "$\textbf{Total deposited energy in the copper foil }$";
titleHelp2 = "$\textbf{for different distances between target and moderator}$";
titleHelp = [titleHelp1 , titleHelp2];
sgtitle(titleHelp,'FontSize',14);
saveas(gcf,"C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\Plots for presentation\eDep_ShowAll.png")
end