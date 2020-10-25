load("matA.mat");

arqs = {'3l2j.pdb','5xf1.pdb','5xez.pdb','6kk7.pdb','6kk1.pdb','6kjv.pdb','5vex.pdb','5vew.pdb','4z9g.pdb','4k5y.pdb','4rwg.pdb'};

% Calculando o SVD e os pontos no espaço reduzido
[T, S, D] = svd(A);
Sn = S(1:3, 1:3);
Dn = D(:, 1:3);
Aux = Sn * transpose(Dn);
x = Aux (1, :);
y = Aux (2, :);

% Plot das classes originais
figure
orig_groups = [1, 2, 2, 3, 3, 3, 3, 3, 4, 4, 5];
for i = 1:6
    p = plot(x(orig_groups==i), y(orig_groups==i), '.');
    set(p, 'MarkerSize', 20);
    hold on;
end

% Plot do kmeans
km_groups = 5;
[idx] = kmeans(transpose(Aux(1:2, :)) , km_groups);
figure
for i = 1:km_groups
    p = plot(x(idx==i), y(idx==i), ".");
    set(p, 'MarkerSize', 20);
    hold on;
end

figure
tree = linkage(transpose(A), 'average');
dendrogram(tree, 'Orientation', 'left', 'Labels', arqs);