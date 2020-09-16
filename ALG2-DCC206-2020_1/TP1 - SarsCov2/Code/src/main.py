from trie import Trie
from fasta_util import FastaUtil

_, content = FastaUtil.load_fasta("../data/sarscov2.fasta")
print(content)

t = Trie()
t.insert_all_prefixes(content)

print("\n\nRepeating:", t.get_longest_repeating())