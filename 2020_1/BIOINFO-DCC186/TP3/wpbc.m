all_data = readtable('wpbc_data.csv');
all_data = sortrows(all_data, 2)

features = all_data(:, 3:end);
features = features{:,:};
features(isnan(features)) = 0
labels = all_data(:, 2);
labels = labels{:,:};

% Calcula o svd
[T, S, D] = svd(transpose(features));

% Calcula as coordenadas no novo sistema de coordenadas das instâncias
Sn = S(1:2, 1:2);
Dn = D(:, 1:2);
Aux = Sn * transpose(Dn);
x = Aux (1, :);
y = Aux (2, :);

% Define o número de grupos para o K-Means
km_groups = 2;

% Executa o K-Means
[idx, C] = kmeans(transpose(Aux(1:2, :)), km_groups);

% Plota cada grupo do kmeans de uma cor diferente
for i = 1:km_groups
    p = plot(x(idx==i), y(idx==i), ".");
    set(p, 'MarkerSize', 20);
    hold on;
end
plot(C(:,1),C(:,2),'kx', 'MarkerSize',15,'LineWidth',3);
title("Classificação utilizando K-Means");

% Faz a regressão logística separando o Iris-Virginica do resto
lgCh0 = log(0.0001 / (1 - 0.0001));
lgCh1 = log(0.9999 / (1 - 0.9999));
b = zeros(198, 1);
b(1:151) = lgCh0;
b(152:end) = lgCh1;
alpha = features \ b;
aux = features * alpha;
num = exp(aux);
p = num./(1 + num);
figure
plot(p, '.', 'MarkerSize', 10);
title("Classificação utilizando Regressão Logística");