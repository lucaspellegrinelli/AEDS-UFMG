from suffix_tree import SuffixTree
from memory_profiler import profile

@profile
def main():
  t = SuffixTree()
  t.load_fasta("../data/sarscov2.fasta")
  t.build_sufixes()

main()