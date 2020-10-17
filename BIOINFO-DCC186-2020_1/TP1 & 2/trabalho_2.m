load primates

% Setando um valor para o gerador de números aleatórios para os resultados
% poderem ser replicados
rng(123)

% Definindo constantes para a execução do programa
rel = containers.Map({'A', 'T', 'C', 'G'}, {0, 1, 2, 3});

% Definindo o tamanho da janela deslizante
window_size = 6;

% Criando a matriz onde os valores serão armazenados
groups = zeros(4^window_size, length(primates));
names = string.empty

% Populando o vector space model
for i = 1:length(primates)
    genome = primates(i).Sequence;
    names(i) = replace(primates(i).Header, "_", " ")
    for j = window_size:length(genome)
        item = genome(j-window_size+1: j);
        if ~contains(item, "N")
            ind = 0;

            for k = 1:window_size
                ind = ind + rel(item(k)) * 4^(window_size-k);
            end

            groups(ind+1, i) = groups(ind+1, i) + 1;
        end
    end
end

% Calculando a decomposição SVD da matriz
[T, S, D] = svd(groups);

% Calcula os pontos no sistema coordenada definido pelo SVD
S3 = S(1:3, 1:3);
D3 = D(:, 1:3);
Aux = S3 * transpose(D3);
x = Aux (1, :);
y = Aux (2, :);
z = Aux (3, :);

% Criando a árvore
tree = linkage(transpose(Aux (1:3, :)), 'average');

% Plotando o diagrama
dendrogram(tree, 'Orientation', 'left', 'Labels', names);

% plot3(x, y, z, ".", 'MarkerSize', 35);

% % Define o número de grupos para o K-Means
% km_groups = 4
% 
% % Executa o K-Means
% [idx] = kmeans(transpose(Aux(1:3, :)) , km_groups);
% 
% % Plota cada grupo do kmeans de uma cor diferente
% for i = 1:km_groups
%     p = plot3(x(idx==i), y(idx==i), z(idx==i), ".");
%     set(p, 'MarkerSize', 35);
%     hold on;
% end
% 
% % Nomes das espécies do lado dos pontos
% for i = 1:length(x)
%     ht = text(x(i) - 0.2, y(i) - 0.2, z(i), primates(i).Header);
%     set(ht, 'Rotation', 45);
%     set(ht, 'FontSize', 8);
%     set(ht, 'HorizontalAlignment', 'right');
% end