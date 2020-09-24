from trie import Trie

from memory_profiler import profile

@profile
def main():
  t = Trie()
  t.load_fasta("../data/sarscov2.fasta")
  t.build_sufixes()

main()