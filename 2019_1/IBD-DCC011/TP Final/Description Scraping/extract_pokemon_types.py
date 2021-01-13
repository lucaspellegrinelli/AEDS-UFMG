import csv

types = [
  "normal", "lutador", "voador", "venenoso", "terra", "pedra", "inseto", "fantasma", "metal", "fogo",
  "agua", "grama", "eletrico", "psiquico", "gelo", "dragao", "noturno", "fada"
]

t = open("sql/add_types.sql", 'w')
with open('pokemon_types.csv') as pokemon_files:
  csv_reader = csv.reader(pokemon_files, delimiter=',')
  for row in csv_reader:
    id = int(row[0])
    type = types[int(row[1]) - 1]
    comm = 'INSERT INTO TipoPokemon (id_pokemon, tipo) VALUES ("' + str(id) + '", "' + str(type) + '");\n'
    t.write(comm)
