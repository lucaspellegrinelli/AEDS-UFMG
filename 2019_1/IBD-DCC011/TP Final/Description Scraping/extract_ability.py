import csv

abilities = dict()
flavors = dict()

with open('ability_names.csv') as ability:
  csv_reader = csv.reader(ability, delimiter=',')
  c = 0
  for row in csv_reader:
    if c > 0 and int(row[1]) == 9 and int(row[0]) < 10000:
      abilities[int(row[0])] = row[2]
      flavors[int(row[0])] = ""
    c += 1

with open('ability_flavor_text.csv') as flavor:
  csv_reader = csv.reader(flavor, delimiter=',')
  c = 0
  for row in csv_reader:
    if c > 0 and int(row[2]) == 9:
      flavors[int(row[0])] = row[3].replace("\n", " ")
    c += 1

t = open("sql/abilities.sql", 'w')
for key in abilities:
  comm = 'INSERT INTO Habilidade (id_habilidade, nome, descricao) VALUES ("' + str(key) + '", "' + abilities[key] + '", "' + flavors[key] + '")\n'
  t.write(comm)
