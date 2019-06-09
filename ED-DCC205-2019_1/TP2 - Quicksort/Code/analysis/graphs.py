import numpy as np
import matplotlib.pyplot as plt

from data_gatherer import *

vec_type = "OrdC"
metric = "time"

colors = dict()
colors["QPE"] = '#f0932b'
colors["QC"] = '#e74c3c'
colors["QM3"] = '#2980b9'
colors["QI1"] = '#e84393'
colors["QI5"] = '#2ecc71'
colors["QI10"] = '#9b59b6'
colors["QNR"] = '#f1c40f'

labels = dict()
labels["QPE"] = 'Quicksort Primeiro Elemento'
labels["QC"] = 'Quicksort Clássico'
labels["QM3"] = 'Quicksort Mediana de Três'
labels["QI1"] = 'Quicksort Inserção 1%'
labels["QI5"] = 'Quicksort Inserção 5%'
labels["QI10"] = 'Quicksort Inserção 10%'
labels["QNR"] = 'Quicksort Não Recursivo'

plt.style.use('ggplot')

plt.suptitle("Comparação do tempo de execução em um vetor ordenado crescente", fontsize=20)

xs = np.arange(50000, 500001, 50000)

plt.subplot(1, 2, 1).set_title("Comparação entre todas as implementações")
plt.ylabel('Tempo (us)')
plt.xlabel('Tamanho do vetor')
for key in data:
  plt.plot(xs, data[key][vec_type][metric], '.-', label=labels[key], color=colors[key])
plt.legend(loc='upper left', frameon=True)

plt.subplot(1, 2, 2).set_title("Comparação entre todas as implementações, exceto 'Quicksort Primeiro Elemento'")
plt.ylabel('Tempo (us)')
plt.xlabel('Tamanho do vetor')
for key in data:
  if key != "QPE":
    plt.plot(xs, data[key][vec_type][metric], '.-', label=labels[key], color=colors[key])
plt.legend(loc='upper left', frameon=True)
plt.show()
