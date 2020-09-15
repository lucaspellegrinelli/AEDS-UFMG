from node import Node

class Trie:
  def __init__(self):
    self.root = Node()

  def intercection(self, a, b):
    out = ""
    for x, y in zip(a, b):
      if x == y: out += x
      else: break
    return out

  def insert(self, word):
    curr = self.root
    
    while len(curr.child) > 0:
      has_home = False
      for i, node in enumerate(curr.child):
        interc = self.intercection(word, node.label)

        if len(interc) > 0:
          label_remainder = node.label[len(interc):]
          word_remainder = word[len(interc):]
          
          if len(label_remainder) > 0:
            new_prefix_child = [Node(label=label_remainder, child=node.child)]
          else:
            new_prefix_child = node.child

          curr.child[i] = Node(label=interc, child=new_prefix_child)

          word = word_remainder
          curr = curr.child[i]
          has_home = True

      if not has_home: break

    if len(word) > 0:
      curr.child.append(Node(label=word))

  def print_branch(self, root, aggr=""):
    curr_str = aggr + root.label + " -> "
    for node in root.child:
      print(curr_str + node.label)
      self.print_branch(root=node, aggr=curr_str)

  def __repr__(self):
    self.print_branch(root=self.root)
    return ""