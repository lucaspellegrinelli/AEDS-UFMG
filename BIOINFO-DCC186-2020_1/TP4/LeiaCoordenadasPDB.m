function [residuos, x, y , z, n] = LeiaCoordenadasPDB(Arq)
regPDB = pdbread(Arq, 'ModelNum', 1);

m = size(regPDB.Model.Atom, 2);
residuos = '';
x = zeros(m, 1);
y = zeros(m, 1);
z = zeros(m, 1);
i = 1;
regPDB.Model.Atom(1).AtomName 

for j =1:m
    if (size(regPDB.Model.Atom(j).AtomName, 2) == 2) & (regPDB.Model.Atom(j).chainID == 'B')
       if regPDB.Model.Atom(j).AtomName == 'CA'
                residuos = [residuos regPDB.Model.Atom(j).resName];
                x(i) = regPDB.Model.Atom(j).X; 
                y(i) = regPDB.Model.Atom(j).Y;
                z(i) = regPDB.Model.Atom(j).Z;
                i = i + 1;
        end
    end
end
n = i - 1;
x = [x(1:n)];
y = [y(1:n)];
z = [z(1:n)];
residuos = aminolookup(residuos);
end