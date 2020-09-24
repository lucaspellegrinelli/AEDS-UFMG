from suffix_tree import SuffixTree

import time
import os
import psutil

process = psutil.Process(os.getpid())

def benchmark_it(f, arg=None):
  time_start = time.time()
  mem_start = process.memory_info().rss
  out = f() if arg is None else f(arg)
  mem_end = process.memory_info().rss
  time_end = time.time()
  return out, time_end - time_start, mem_end - mem_start

# Creating Suffix Tree datatype and loading FASTA
t = SuffixTree()
t.load_fasta("../data/sarscov2.fasta")

# Inserting the sufixes to the tree
_, s_time, s_mem = benchmark_it(t.build_sufixes)

# Get longest repeating word
(lr_str, lr_pos), lr_time, lr_mem = benchmark_it(t.get_longest_repeating)

# Get number of occurences of longest repeating word
rc_val, rc_time, rc_mem = benchmark_it(t.count_occurences, lr_str)

# Prints
print(" > Processamento de sufixos")
print("   > Tempo de execução:", round(s_time, 3), "segundos")
print("   > Memória usada:", round(s_mem / 1024, 3), "KB")
print("")

print(" > Procura da maior string repetida")
print("   > Tempo de execução:", round(lr_time, 3), "segundos")
print("   > Memória usada:", round(lr_mem / 1024, 3), "KB")
print("   > Resultado:", lr_str)
print("   > Posição:", lr_pos)
print("")

print(" > Contagem de ocorrências")
print("   > Tempo de execução:", round(rc_time, 5), "segundos")
print("   > Memória usada:", round(rc_mem / 1024, 3), "KB")
print("   > Resultado:", rc_val)
print("")