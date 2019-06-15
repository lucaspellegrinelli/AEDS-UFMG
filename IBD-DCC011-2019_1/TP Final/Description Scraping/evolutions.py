import csv

t = open("add_evolutions.sql", 'w')

f = open("pokemon_evolution.html", 'r')
lines = f.readlines()

pokemons = dict()
with open('pokemon.csv') as pokemon_files:
  csv_reader = csv.reader(pokemon_files, delimiter=',')
  for row in csv_reader:
    if int(row[2]) not in pokemons:
      pokemons[int(row[2])] = row[1]

all_evolutions = []
i = 0
while i < len(lines):
  if u"\u2192" in lines[i]:
    evo_line = []
    i -= 2
    while i < len(lines):
      if ' family' in lines[i]:
        break
      if 'tyle="color:#000;">' in lines[i]:
        name = lines[i].split('tyle="color:#000;">')[1].split('</span></a>')[0].lower()
        name = name.replace("é", "e")
        name = name.replace("jangmo-o", "jangmo")
        name = name.replace("hakamo-o", "hakamo")
        name = name.replace("kommo-o", "kommo")
        name = name.replace(u"\u2640", "-f")
        name = name.replace(u"\u2642", "-m")
        name = name.replace("mime jr.", "mime-jr")
        name = name.replace("mr. mime", "mr-mime")

        if name not in evo_line and "meltan" not in evo_line and "type: null" not in evo_line:
          evo_line.append(name)
      i += 1

    all_evolutions.append(evo_line)
  i += 1

def get_id(name):
  for key in pokemons:
    if name in pokemons[key]:
      return key
  return -1

for line in all_evolutions:
  for i in range(len(line) - 1):
    for j in range(i + 1, len(line)):
      id_from = get_id(line[i])
      id_to = get_id(line[j])
      degree = j - i

      comm = 'INSERT INTO Evolucao (id_de, id_para, grau) VALUES ("' + str(id_from) + '", "' + str(id_to) + '", "' + str(degree) + '");\n'
      t.write(comm)
