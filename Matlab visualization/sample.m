function sample()

clc
close all
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dir = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\posTable.txt";
M = load(dir);


totScore = 0;
frontLength = 15;
for i=1:10000
    E = M(i,7);
    [sc,dist] = scoreEnergy(E,15);
    totScore = totScore + sc;
end

totScore


noSamples = length(M);
fprintf("Number of samples: " + string(noSamples) + newline);

r = M(:,1:3);
p = M(:,4:6);
E = M(:,7);

figure
pts = linspace(-25, 25, 41);
N = histcounts2(r(:,2), r(:,3), pts, pts);
imagesc(pts, pts, N);
colorbar
axis equal
hcb = colorbar;
set(gca, 'XLim', pts([1 end]), 'YLim', pts([1 end]), 'YDir', 'normal');
xlabel('$y$/cm')
ylabel('$z$/cm')
titleHelp = {"$\textbf{Positron distribution in the }y\textbf{-}z\textbf{-plane}$", ...
    "$\textbf{Total positrons: } $" + string(length(M))
    };
title(titleHelp)
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$N \textrm{ hits}$','Interpreter','Latex');


figure
subplot(3,1,1)
nBins = 50;
histogram(p(:,1), nBins);
xlim([-1,1])
grid on
title("$\textbf{Distribution of momentum x-components of sampled positrons}$")
% %--------------------------------------------------------------%
subplot(3,1,2)
nBins = 50;
histogram(p(:,2), nBins);
xlim([-1,1])
grid on
title("$\textbf{Distribution of momentum y-components of sampled positrons}$")
%--------------------------------------------------------------%
subplot(3,1,3)
nBins = 50;
histogram(p(:,3), nBins);
xlim([-1,1])
grid on
title("$\textbf{Distribution of momentum z-components of sampled positrons}$")
%--------------------------------------------------------------%
 end