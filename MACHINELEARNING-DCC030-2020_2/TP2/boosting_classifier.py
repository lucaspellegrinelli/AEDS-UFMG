import numpy as np
import math
from sklearn.tree import DecisionTreeClassifier

class BoostingClassifier:
  def __init__(self, iterations):
    self.iterations = iterations
    self.x_classes = 2
    self.classifiers = []
    self.alphas = []

  def fit(self, x, y):
    self.x_classes = len(np.unique(x))
    x = self.process_input(x)
    y = self.process_output(y)

    h, a = self.create_weak_classifiers(x, y)
    self.classifiers = h
    self.alphas = a
    return self
    
  def create_weak_classifiers(self, x, y):
    weights = np.ones(len(x)) * (1 / len(x))
    alphas = np.zeros((self.iterations))
    h = [None for _ in range(self.iterations)]

    for t in range(self.iterations):
      d_stump = DecisionTreeClassifier(max_depth=1, max_leaf_nodes=2)
      d_stump.fit(x, y, sample_weight=weights)

      h[t] = d_stump
      htx = d_stump.predict(x)

      error = np.sum(weights[(y != htx)])
      alphas[t] = 0.5 * math.log((1 - error) / error)
      weights = weights * math.e ** (-alphas[t] * htx * y)
      weights /= weights.sum()
    
    return h, alphas

  def predict(self, x):
    x = self.process_input(x)

    weak_pred = np.zeros((len(x)))
    for i in range(self.iterations):
      hx = self.classifiers[i].predict(x)
      weak_pred += self.alphas[i] * hx

    weak_pred = np.sign(weak_pred)
    weak_pred[weak_pred == -1] = 0
    return weak_pred

  def process_output(self, y):
    ny = y.copy()
    ny[ny == 0] = -1
    return ny

  def process_input(self, x):
    nx = np.empty((x.shape[0], x.shape[1] + self.x_classes))
    nx[:, :-self.x_classes] = x
    for c in range(self.x_classes):
      nx[:, -(c + 1)] = np.ones((x.shape[0])) * c
    return nx