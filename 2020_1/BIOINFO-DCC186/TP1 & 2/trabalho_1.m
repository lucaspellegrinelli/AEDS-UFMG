% Definindo a matriz 'A'
A = [0 0 0 1 0;
     0 0 0 0 1;
     0 0 0 0 1;
     1 0 1 0 0;
     1 0 0 0 0;
     0 1 0 0 0;
     1 0 1 1 0;
     0 1 1 0 0;
     0 0 1 1 1;
     0 1 1 0 0];

% Definindo a query 'q'
q = transpose([0, 0, 0, 0, 0, 0, 0, 1, 1, 1]);

% Calculando o singular value decomposition da matriz A
[T, S, D] = svd(A);

% Caso essa norma seja 0, então A = TSD'
norm(A - T * S * transpose(D), 2)

% O resuldado obtido pelo comando acima é 2.8812e-15, que é maior que zero
% apesar do resultado estar correto devido a imprecisões nas operações de
% ponto flutuante.

% Calcula os pontos no sistema coordenada definido pelo SVD
S2 = S(1:2, 1:2);
D2 = D(:, 1:2);
Aux = S2 * transpose(D2);
x = Aux (1, :);
y = Aux (2, :);

% Plote os pontos
plot(x, y, '.', 'MarkerSize', 35);

hold on

% Projetando a query no espaço reduzido
query_pt = linsolve(T(:, 1:2), q)

% Plotando o ponto no gráfico
plot(query_pt(1), query_pt(2), 'r.', 'MarkerSize', 35);