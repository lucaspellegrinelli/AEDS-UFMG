import numpy as np
import math

class BoostingClassifier:
  def __init__(self, iterations):
    self.iterations = iterations
    self.x_classes = 2
    self.classifiers = []
    self.alphas = []

  def fit(self, x, y):
    self.x_classes = len(np.unique(x))
    x = self.process_input(x)

    h, a = self.create_weak_classifiers(x, y)
    self.classifiers = h
    self.alphas = a
    return self
    
  def create_weak_classifiers(self, x, y):
    weights = np.ones(len(x)) * (1 / len(x))
    alphas = np.zeros((self.iterations))
    h = [None for _ in range(self.iterations)]

    col_availability = np.ones((x.shape[1]))
    for t in range(self.iterations):
      h[t] = self.decide_stump(x, y, col_availability)
      col_availability[h[t][0]] = 0
      htx = self.get_stump_classification(x, h[t])
      error = np.sum(weights * (y != htx))
      alphas[t] = 0.5 * math.log((1 - error) / error)
      weights = weights * math.e ** (-alphas[t] * htx * y)
      weights /= weights.sum()
    
    return h, alphas

  def get_stump_classification(self, x, stump):
    classifications = np.zeros((len(x)))
    for i, x_val in enumerate(x):
      classifications[i] = 1 if (x_val[stump[0]] == stump[1]) == stump[2] else -1
    return classifications

  def decide_stump(self, x, y, col_availability=None):
    best_stump = (-1, -1, False, len(x) + 1)

    for col in range(x.shape[1]):
      if col_availability is not None and col_availability[col] == 0: continue
      for stump_test in range(self.x_classes):
        missclassifications = np.zeros((2))
        for c_val, target in zip(x.transpose()[col], y):
          missclassifications[(c_val == stump_test) == (target == -1)] += 1
        
        for i, mc in enumerate(missclassifications):
          if mc < best_stump[3]:
            best_stump = (col, stump_test, i == 0, mc)
        
    return best_stump

  def predict(self, x):
    x = self.process_input(x)

    weak_pred = np.zeros((len(x)))
    for i in range(self.iterations):
      hx = self.get_stump_classification(x, self.classifiers[i])
      weak_pred += self.alphas[i] * hx

    weak_pred = weak_pred > 0
    weak_pred = np.where(weak_pred == True, 1, weak_pred)
    weak_pred = np.where(weak_pred == False, 0, weak_pred)
    return weak_pred

  def process_input(self, x):
    nx = np.empty((x.shape[0], x.shape[1] + self.x_classes))
    nx[:, :-self.x_classes] = x
    for c in range(self.x_classes):
      nx[:, -(c + 1)] = np.ones((x.shape[0])) * c
    return nx