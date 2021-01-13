import csv

mes = 11
ano = 2014
print("Adicionou o mes" + str(mes) + " ano " + str(ano))

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

stats = []
t = open("adc_uso_pokemon.sql", 'a')
with open('ou-1825.txt') as smogon:
  lines = smogon.readlines()
  total_battles = int(lines[0].split(": ")[1])
  c = 0
  for line in lines:
    if c > 4:
      if "+" in line:
        continue
      l = line.replace("\t", "").split("|")
      name = l[2].replace(" ", "").replace("'", "").replace(".", "")
      if name.lower() == "type:null" or name[-1] == "F" or name[-1] == "M":
        continue
      uses = '{0:f}'.format(float(l[3].split("%")[0]) / 100)
      if float(uses) == 0.0:
        continue
      id = pokemons[name.split("-")[0].lower().replace("-", "")]
      com = 'INSERT INTO UsoPokemon (id_pokemon, ano, mes, porcentagem) VALUES ("' + str(id) + '", "' + str(ano) + '", "' + str(mes) + '", "' + str(uses) + '")\n'
      t.write(com)
    c += 1
