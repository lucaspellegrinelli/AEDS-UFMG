import os
import random

VARIABLE_INSTRUCTION_COUNT = True

test_dir = "../test_cases/generated" + ("_var_instr" if VARIABLE_INSTRUCTION_COUNT else "_const_instr")

if not os.path.exists(test_dir):
  os.makedirs(test_dir)

for m_count in range(5, 51, 5):
  file_name = test_dir + "/" + str(m_count) + ".txt"
  file = open(file_name, "w")

  max_edges = (m_count * (m_count - 1)) // 2

  if VARIABLE_INSTRUCTION_COUNT:
    swap_count = max_edges // 4
    commander_count = max_edges // 4
  else:
    swap_count = 5
    commander_count = 5

  n_instructions = swap_count + commander_count

  file.write(str(m_count) + " " + str(max_edges) + " " + str(n_instructions + 1) + '\n')

  ages = [random.randint(12, 100) for _ in range(m_count)]
  file.write(" ".join(str(i) for i in ages) + "\n")

  connections = []
  for i in range(1, m_count + 1):
    for j in range(i + 1, m_count + 1):
      connections.append((i, j))
      file.write(str(i) + " " + str(j) + "\n")

  for i in range(n_instructions):
    is_swap = random.choice([True] * swap_count + [False] * commander_count)

    if is_swap:
      swap_count -= 1
      file.write("S " + str(random.randint(1, m_count)) + " " + str(random.randint(1, m_count)) + "\n")
    else:
      commander_count -= 1
      file.write("C " + str(random.randint(1, m_count)) + "\n")

  file.write("M\n")
  file.close()
