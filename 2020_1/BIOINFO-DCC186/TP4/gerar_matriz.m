A = [];

arqs = {'3l2j.pdb','5xf1.pdb','5xez.pdb','6kk7.pdb','6kk1.pdb','6kjv.pdb','5vex.pdb','5vew.pdb','4z9g.pdb','4k5y.pdb','4rwg.pdb'};

for arq_i = 1:length(arqs)
    [residuos, x, y, z, n] = LeiaCoordenadasPDB(strcat('proteins/', arqs{arq_i}));
    D = pdist([x y z]);
    D = squareform(D);
    [U, S, V] = svd(D, 'econ');
    s = diag(S);
    A = [A s(1:10)];
end

save("matA.mat", 'A');