import matplotlib.pyplot as plt

# (N vertices, Time in ms)
vert_ms_var_instr = [
  (5, 21),
  (10, 24),
  (15, 32),
  (20, 42),
  (25, 56),
  (30, 73),
  (35, 92),
  (40, 112),
  (45, 137),
  (50, 165)
]

# (N arestas, Time in ms)
aresta_ms_var_instr = [
  (10, 21),
  (45, 24),
  (105, 32),
  (190, 42),
  (300, 56),
  (435, 73),
  (595, 92),
  (780, 112),
  (990, 137),
  (1225, 165)
]

# (N vértices, Time in ms)
vert_ms_const_instr = [
  (100, 24),
  (200, 32),
  (300, 36),
  (400, 44),
  (500, 53),
  (600, 70),
  (700, 91),
  (800, 112),
  (900, 134),
  (1000, 161)
]

# (N arestas, Time in ms)
arest_ms_const_instr = [
  (4950, 23),
  (19900, 29),
  (44850, 38),
  (79800, 44),
  (124750, 54),
  (179700, 70),
  (244650, 88),
  (319600, 111),
  (404550, 129),
  (499500, 159)
]

xs, ys = zip(*arest_ms_const_instr)
plt.plot(xs, ys)
plt.show()
