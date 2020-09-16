class Node:
  def __init__(self, label="", child=[], is_end=False):
    self.child = child[:]
    self.label = label
    self.is_end = is_end