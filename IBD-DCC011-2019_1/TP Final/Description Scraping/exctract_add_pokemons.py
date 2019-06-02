import csv

pokemons = dict()
flavors = dict()

with open('pokemon.csv') as pokemon_files:
  csv_reader = csv.reader(pokemon_files, delimiter=',')
  c = 0
  for row in csv_reader:
    if c > 0 and int(row[2]) not in pokemons:
      pokemons[int(row[2])] = row[1]
    c += 1

with open('pokemon_species_flavor_text.csv') as csv_file:
  csv_reader = csv.reader(csv_file, delimiter=',')
  c = 0
  for row in csv_reader:
    if c > 0 and row[2] == '9' and int(row[0]) not in flavors:
      flavors[int(row[0])] = row[3]
    c += 1

sql = open("sql/add_pokemons.sql", "w+")
for key in pokemons:
  name = pokemons[key].capitalize()
  flavour = flavors[key]
  flavour = flavour.replace('\n', ' ').replace('\r', '')
  comm = 'INSERT INTO Pokemon (id_pokemon, nome, descricao) VALUES ("' + str(key) + '", "' + name + '", "' + flavour + '");\n'
  sql.write(comm)
