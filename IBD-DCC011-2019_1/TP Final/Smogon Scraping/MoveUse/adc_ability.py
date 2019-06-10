import csv
import re

mes = 11
ano = 2014
print("Adicionou o mes " + str(mes) + " ano " + str(ano))

pokemons = dict()
with open('../../Description Scraping/pokemon.csv') as pokemon_files:
  csv_reader = csv.reader(pokemon_files, delimiter=',')
  for row in csv_reader:
    k = int(row[0])
    if k > 9999:
      continue
    id = int(row[2])
    name = row[1].lower().replace("'", "")

    if "-" in name:
      if "tapu" in name or "mime" in name:
        name = name.replace("-", "")
      else:
        name = name.split("-")[0]

    if id not in pokemons:
      pokemons[name.split("-")[0]] = id

all_moves = dict()
with open('../../Description Scraping/moves.csv') as pokemon_files:
  csv_reader = csv.reader(pokemon_files, delimiter=',')
  for row in csv_reader:
    if int(row[3]) < 10000:
      id = int(row[0])
      name = row[1].lower().replace(" ", "").replace("-", "")
      all_moves[name] = id

all_abilities = dict()
with open('../../Description Scraping/ability_names.csv') as pokemon_files:
  csv_reader = csv.reader(pokemon_files, delimiter=',')
  for row in csv_reader:
    if row[0] != "ability_id" and int(row[0]) < 10000 and int(row[1]) == 9:
      id = int(row[0])
      name = row[2].lower().replace(" ", "").replace("-", "")
      all_abilities[name] = id

stats = []
t = open("adc_uso_ataque.sql", 'a')
t2 = open("adc_aliados.sql", 'a')
t3 = open("adc_uso_habilidades.sql", 'a')
#with open('gen7ou-1825.txt') as smogon:
with open('ou-1825.txt') as smogon:
  lines = smogon.readlines()
  # Cuida de pegar os teammates
  for i in range(len(lines)):
    if i == 1 or i > 1 and "+-" in lines[i - 2] and "+-" in lines[i - 1]:
      name = lines[i].replace("\t", "").replace("\n", "").replace(" ", "").replace("|", "").replace("'", "").replace(".", "")
      if name.lower() == "type:null" or name[-1] == "F" or name[-1] == "M":
        continue
      while "Teammates" not in lines[i]:
        i += 1
      i += 1
      while "+-" not in lines[i]:
        teammate = lines[i].replace("\t", "").replace("\n", "").replace(" ", "").replace("|", "").replace("'", "")

        if "Null" in teammate:
          i += 1
          continue

        match = re.match(r"([a-z\-\'\.]+)([0-9\+].+)", teammate, re.I)
        teammate_name = str(match.groups()[0]).split("-")[0].replace(".", "").lower()
        teammate_id = pokemons[teammate_name]
        pokemon_id = pokemons[name.split("-")[0].lower().replace("-", "")]
        used = float(str(match.groups()[1]).split("+")[1].split("%")[0]) / 100

        com = 'INSERT INTO AliadosComuns (id_pokemon, id_aliado, ano, mes, porcentagem) VALUES  VALUES ("' + str(pokemon_id) + '", "' + str(teammate_id) + '", "' + str(ano) + '", "' + str(mes) + '", "' + str(used) + '");\n'
        # t2.write(com)
        i += 1

  # Cuida de pegar os ataques
  for i in range(len(lines)):
    if i == 1 or i > 1 and "+-" in lines[i - 2] and "+-" in lines[i - 1]:
      name = lines[i].replace("\t", "").replace("\n", "").replace(" ", "").replace("|", "").replace("'", "").replace(".", "")
      if name.lower() == "type:null" or name[-1] == "F" or name[-1] == "M":
        continue
      while "Moves" not in lines[i]:
        i += 1
      i += 1
      while "+-" not in lines[i]:
        move = lines[i].replace("\t", "").replace("\n", "").replace(" ", "").replace("|", "")
        match = re.match(r"([a-z\-\']+)([0-9].+)", move, re.I)
        move_name = str(match.groups()[0])

        used = '{0:f}'.format(float(str(match.groups()[1].split("%")[0])) / 100)
        pokemon_id = pokemons[name.split("-")[0].lower().replace("-", "")]

        move_name = move_name.lower().replace("-", "").replace("'", "")
        if "hiddenpower" in move_name:
          move_name = "hiddenpower"

        if move_name == "other" or move_name == "nothing":
          i += 1
          continue

        com = 'INSERT INTO UsoAtaque (id_pokemon, id_ataque, ano, mes, porcentagem) VALUES ("' + str(pokemon_id) + '", "' + str(all_moves[move_name]) + '", "' + str(ano) + '", "' + str(mes) + '", "' + str(used) + '");\n'
        # t.write(com)
        i += 1

  # Cuida de pegar as habilidades
  for i in range(len(lines)):
    if i == 1 or i > 1 and "+-" in lines[i - 2] and "+-" in lines[i - 1]:
      name = lines[i].replace("\t", "").replace("\n", "").replace(" ", "").replace("|", "").replace("'", "").replace(".", "")
      if name.lower() == "type:null" or name[-1] == "F" or name[-1] == "M":
        continue

      pokemon_id = pokemons[name.split("-")[0].lower().replace("-", "")]

      while "Abilities" not in lines[i]:
        i += 1

      i += 1
      while "+-" not in lines[i]:
        ability = lines[i].replace("\t", "").replace("\n", "").replace(" ", "").replace("|", "")
        match = re.match(r"([a-z\-\']+)([0-9].+)", ability, re.I)
        ability_name = str(match.groups()[0])

        used = '{0:f}'.format(float(str(match.groups()[1].split("%")[0])) / 100)
        pokemon_id = pokemons[name.split("-")[0].lower().replace("-", "")]

        ability_name = ability_name.lower().replace("-", "").replace("'", "")

        comm = 'INSERT INTO UsoHabilidade (id_pokemon, id_habilidade, ano, mes, porcentagem) VALUES ("' + str(pokemon_id) + '", "' + str(all_abilities[ability_name]) + '", "' + str(ano) + '", "' + str(mes) + '", "' + str(used) + '");\n'
        t3.write(comm)
        i += 1
