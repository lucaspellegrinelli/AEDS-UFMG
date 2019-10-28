import os
import random
import time
import numpy as np
import matplotlib.pyplot as plt

PROGRAM_PATH = "tp2"
INPUT_PATH = "input.in"
RUN_OPTIONS = "no_dynamic"

XS_LABEL = "Número de ilhas"

xs = []
ys = []

def run_program(path, input_path):
  command = "./" + PROGRAM_PATH + " " + INPUT_PATH + " " + RUN_OPTIONS
  start = time.time()
  os.popen(command)
  end = time.time()
  return end - start

def generate_test_case(run_test_case):
  for island_count in range(0, 500001, 50000):
    island_count = max(10, island_count)
    in_str = str(island_count * 10) + " " + str(island_count) + "\n"

    for island in range(island_count):
      in_str += str(random.randint(10, island_count)) + " " + str(random.randint(0, 1000)) + "\n"

    with open(INPUT_PATH, "w+") as in_file:
      in_file.write(in_str)

    run_test_case(x=island_count)

    os.remove(INPUT_PATH)

def run_test_case(x, iterations=25):
  xs.append(x * 160)
  print("Executing for x =", x)
  runtimes = [run_program(PROGRAM_PATH, INPUT_PATH) for _ in range(iterations)]
  print(" Mean:", np.mean(runtimes))
  print(" STD:", np.std(runtimes))
  ys.append(np.mean(runtimes))

generate_test_case(run_test_case)

plt.plot(xs, ys, label="Tempo de execução")
plt.xlabel(XS_LABEL)
plt.ylabel("Tempo (ms)")
plt.suptitle("Gráfico de #ilhas x tempo do algoritmo Programação Dinâmica")
plt.legend(loc="upper left")
plt.show()
