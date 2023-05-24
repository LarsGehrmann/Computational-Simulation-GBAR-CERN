function showPosTableHisto()
fontSizeLegend = 13;
fontSizeAxes = 20;
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dir = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\posTable.txt";


M = load(dir);
E = M(:,7);
n = length(E);
avgE = round(sum(E) / n * 1000) / 1000;
edges = logspace(-2,1,50);

figure
hist(E, edges)
set(gca,'xscale','log')
xlim([10^-2,10])
grid on

titleHelp = {"$\textbf{Kinetic energy of sampled positrons}$","$\textbf{Total number of positrons: }$" + n + "$\textbf{; } \bar{E} = $" + avgE + "$\textbf{MeV}$"};
%title(titleHelp, 'Fontsize', 12)

a = get(gca,'XTickLabel');
set(gca,'XTickLabel',a,'FontName','Times','fontsize',20)
h=xlabel('$y$/cm') %or h=get(gca,'xlabel')
set(h, 'FontSize', 25)

h=ylabel('$z$/cm') %or h=get(gca,'xlabel')
set(h, 'FontSize', 25)
a = get(gca,'YTickLabel');
set(gca,'YTickLabel',a,'FontName','Times','fontsize',20)
set(gca,'YDir','normal')


xlabel('$E / \textrm{MeV}$')
ylabel('$\textrm{N}$')
hLegend = findobj(gcf, 'Type', 'Legend');
set(hLegend,'FontSize', fontSizeLegend)
hAxis = findobj(gcf,'Type','Axes')
set(hAxis,'FontSize', fontSizeAxes)
avgE
end