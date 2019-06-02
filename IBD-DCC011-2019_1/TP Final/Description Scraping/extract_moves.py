import csv

types = [
  "normal", "lutador", "voador", "venenoso", "terra", "pedra", "inseto", "fantasma", "metal", "fogo",
  "agua", "grama", "eletrico", "psiquico", "gelo", "dragao", "noturno", "fada"
]

flavors = dict()
with open('move_flavor_text.csv') as pokemon_files:
  csv_reader = csv.reader(pokemon_files, delimiter=',')
  for row in csv_reader:
    id = int(row[0])
    lang = int(row[2])
    txt = row[3]
    if lang == 9 and id not in flavors:
      flavors[id] = txt

t = open("sql/moves.sql", 'w')
with open('moves.csv') as pokemon_files:
  csv_reader = csv.reader(pokemon_files, delimiter=',')
  for row in csv_reader:
    if int(row[3]) < 10000:
      id = int(row[0])
      name = row[1].capitalize()
      type = types[int(row[3]) - 1]
      fla = flavors[id].replace('\n', ' ').replace('\r', '')
      comm = 'INSERT INTO Ataque (id_ataque, nome, descricao, tipo) VALUES ("' + str(id) + '", "' + name + '", "' + fla + '", "' + type + '");\n'
      t.write(comm)
