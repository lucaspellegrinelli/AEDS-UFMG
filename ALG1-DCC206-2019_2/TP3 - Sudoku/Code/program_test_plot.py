import os
import random
import time
import numpy as np
import matplotlib.pyplot as plt

PROGRAM_PATH = "tp3"
SIZES = [2, 6, 8, 9]

exec_times = {}

def run_program(input_path, rep=1):
  command = "./" + PROGRAM_PATH + " " + input_path
  start = time.time()
  for _ in range(rep):
    os.popen(command)
  end = time.time()
  return (end - start) / rep

for path, subdirs, files in os.walk("test_cases/provided_dataset/"):
  for name in files:
    off_path = os.path.join(path, name)
    tab_size = int(name[0])
    print("Running", off_path, name)
    if tab_size not in exec_times:
      exec_times[tab_size] = []
    exec_times[tab_size].append(run_program(off_path, rep=100))

ys = []
for k, v in exec_times.items():
  print("Final", k, np.mean(v))
  ys.append(np.std(v))

plt.plot(ys, label="Tempo de execução")
plt.xticks(np.arange(len(ys)), SIZES)
plt.xlabel("Tamanho do tabuleiro")
plt.ylabel("Tempo (ms)")
plt.suptitle("Gráfico para tamanho do tabuleiro x Tempo de execução")
plt.legend(loc="upper left")
plt.show()
