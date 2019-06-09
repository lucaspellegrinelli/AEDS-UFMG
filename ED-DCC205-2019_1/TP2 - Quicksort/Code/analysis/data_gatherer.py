import os

data = dict()

for r, d, f in os.walk("../outputs/"):
  for file in f:
    variation = file.split(".")[0]
    path = os.path.join(r, file)
    arch = open(path, "r")

    data[variation] = dict()

    data[variation]["Ale"] = dict()
    data[variation]["Ale"]["comp"] = [0] * 10
    data[variation]["Ale"]["move"] = [0] * 10
    data[variation]["Ale"]["time"] = [0] * 10

    data[variation]["OrdC"] = dict()
    data[variation]["OrdC"]["comp"] = [0] * 10
    data[variation]["OrdC"]["move"] = [0] * 10
    data[variation]["OrdC"]["time"] = [0] * 10

    data[variation]["OrdD"] = dict()
    data[variation]["OrdD"]["comp"] = [0] * 10
    data[variation]["OrdD"]["move"] = [0] * 10
    data[variation]["OrdD"]["time"] = [0] * 10

    for line in arch:
      line_s = line.split(" ")
      arr_type = line_s[1]
      array_s = int(line_s[2])
      array_s_id = int(array_s / 50000 - 1)
      comps = int(line_s[3])
      moves = int(line_s[4])
      time = int(line_s[5])

      data[variation][arr_type]["comp"][array_s_id] = comps
      data[variation][arr_type]["move"][array_s_id] = moves
      data[variation][arr_type]["time"][array_s_id] = time
