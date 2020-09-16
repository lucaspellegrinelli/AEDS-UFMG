class Node:
  def __init__(self, interval, child=[], is_end=False):
    self.interval = interval
    self.child = child[:]
    self.is_end = is_end