class Node:
  def __init__(self, label="", child=[]):
    self.child = child[:]
    self.label = label