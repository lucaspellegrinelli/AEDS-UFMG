# Classe que representa um dos nós de uma àrvore de sufixos
class Node:
  def __init__(self, interval, child=[], is_end=False):
    self.interval = interval
    self.child = child[:]
    self.is_end = is_end

# Classe que representa a arvore de sufixos
class SuffixTree:
  def __init__(self, text=""):
    self.root = Node(interval=[0, 0])
    self.text = text

  # Popula a variavel "self.text" com o conteudo de um arquivo do tipo FASTA
  def load_fasta(self, path):
    with open(path) as fasta:
      lines = fasta.readlines()
      meta = lines[0]
      content = ("".join(lines[1:])).replace("\n", "")
      self.text = content

  # Retorna o tamanho do maior prefixo comum entre duas strings definidas por dois
  # intervalos em duas strings
  def common_prefix_size(self, a_word, a, b_word, b):
    interval = min(a[1] - a[0], b[1] - b[0])
    for i in range(interval):
      if a_word[a[0] + i] != b_word[b[0] + i]:
        return i
    return interval

  # Loop ingênuo de para popular a trie de sufixos, adicionando todos os possíveis
  # sufixos na trie.
  def build_sufixes(self):
    for i in range(len(self.text)):
      self.insert(self.text, i)

  # Método principal de inserção de uma palavra na trie. O algoritmo aqui envolve
  # descer pelas ramificações da árvore que possuem um prefixo igual ao da nova
  # palavra. Caso o algoritmo encontre um nó cuja 'label' seja sufixo da palavra,
  # um novo nó deve ser criado separando o prefixo do sufixo. Caso em um galho não
  # existam nós passíveis de admitir a nova palavra, um novo nó é criado naquele nível.
  def insert(self, word, start=0):
    curr = self.root
    l, r = start, len(word)

    while len(curr.child) > 0:
      has_prefix = False
      for i, node in enumerate(curr.child):
        pref_size = self.common_prefix_size(word, [l, r], word, node.interval)

        if pref_size > 0:
          label_pref = [node.interval[0], node.interval[0] + pref_size]
          label_suf = [node.interval[0] + pref_size, node.interval[1]]
          l += pref_size
          
          if label_suf[1] > label_suf[0]:
            prefix_child = [Node(interval=label_suf, child=node.child, is_end=node.is_end)]
          else:
            prefix_child = node.child

          curr.child[i] = curr = Node(interval=label_pref, child=prefix_child, is_end=r == l)
          has_prefix = True
          break

      if not has_prefix: break

    if r != l:
      curr.child.append(Node(interval=[l, r], is_end=True))

  # Para encontrar a maior substring que se repete no texto de entrada basta checar
  # qual o nó mais prodfundo que possui nós filhos.
  def get_longest_repeating(self):
    def utility_dfs(node, ans):
      new_pref, new_pos = ans
      for n in node.child:
        if len(n.child) == 0: continue
        suf = self.text[n.interval[0] : n.interval[1]]
        leaf_pref, leaf_pos = utility_dfs(n, (ans[0] + suf, n.interval[1]))
        if len(leaf_pref) > len(new_pref):
          new_pref = leaf_pref
          new_pos = leaf_pos
  
      return new_pref, new_pos

    pref, pos = utility_dfs(self.root, ("", -1))
    return pref, pos - len(pref)

  # Para contar o número de ocorrências de um certo padrão a partir de um árvore de
  # sufixos basta encontrar onde a palavra estaria caso fossemos procura-la na árvore
  # e contar o número de nós filhos e adicionar 1 caso ela seja um nó final para algum
  # sufixo.
  def count_occurences(self, word):
    curr = self.root
    l, r = 0, len(word)

    while len(curr.child) > 0 and r != l:
      has_prefix = False
      for node in curr.child:
        pref_size = self.common_prefix_size(word, [l, r], self.text, node.interval)

        if pref_size > 0:
          curr = node
          l += pref_size
          has_prefix = True
          break
      
      if not has_prefix: return False

    return len(curr.child) + (1 if curr.is_end else 0)

  # Métodos de visualização da árvore
  def print_branch(self, root, aggr=""):
    curr_str = aggr + self.text[root.interval[0] : root.interval[1]] + " -> "
    for node in root.child:
      print(curr_str + self.text[node.interval[0] : node.interval[1]])
      self.print_branch(root=node, aggr=curr_str)

  def __repr__(self):
    self.print_branch(root=self.root)
    return ""