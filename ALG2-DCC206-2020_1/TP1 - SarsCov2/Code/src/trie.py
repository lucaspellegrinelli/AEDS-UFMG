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

  def insert_all_prefixes(self, word):
    for i in range(len(word)):
      self.insert(word[i:])

  def insert(self, word):
    curr = self.root
    
    while len(curr.child) > 0:
      has_home = False
      for i, node in enumerate(curr.child):
        interc = self.intercection(word, node.label)

        if len(interc) > 0:
          label_remainder = node.label[len(interc):]
          word = word[len(interc):]
          
          if len(label_remainder) > 0:
            new_prefix_child = [Node(label=label_remainder, child=node.child, is_end=node.is_end)]
          else:
            new_prefix_child = node.child

          curr.child[i] = Node(label=interc, child=new_prefix_child, is_end=len(word) == 0)
          curr = curr.child[i]
          has_home = True
          break

      if not has_home: break

    if len(word) > 0:
      curr.child.append(Node(label=word, is_end=True))

  def count_occurences(self, word):
    curr = self.root

    while len(curr.child) > 0 and len(word) > 0:
      has_prefix = False
      for node in curr.child:
        interc = self.intercection(word, node.label)

        if len(interc) > 0:
          curr = node
          word = word[len(interc):]
          has_prefix = True
          break
      
      if not has_prefix: return False

    return len(curr.child) + (1 if curr.is_end else 0)

  def get_longest_repeating(self):
    def utility_dfs(node, ans):
      new_ans = ans
      for n in node.child:
        if len(n.child) == 0: continue
        leaf_ans = utility_dfs(n, ans + n.label)
        if len(leaf_ans) > len(new_ans):
          new_ans = leaf_ans
  
      return new_ans

    return utility_dfs(self.root, "")

  def print_branch(self, root, aggr=""):
    curr_str = aggr + root.label + " -> "
    for node in root.child:
      print(curr_str + node.label)
      self.print_branch(root=node, aggr=curr_str)

  def __repr__(self):
    self.print_branch(root=self.root)
    return ""