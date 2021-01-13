%Arq = '1FJR.pdb';   %proteína MTH_DROME
Arq =  '4I6R.pdb';
[residuos, x, y , z, n] = LeiaCoordenadasPDB(Arq);
D = pdist([x y z]);% o resultado é uma matriz triangular
D = squareform(D); % transforma numa matriz quadrada
[U, S, V] = svd(D, 'econ');
s = diag(S);
plot(s, '*')
grid on
figure 
grid on
plot(s(1:10), '*')
grid on
