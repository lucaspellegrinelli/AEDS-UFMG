from trie import Trie
from fasta_util import FastaUtil

_, content = FastaUtil.load_fasta("../data/sarscov2.fasta")

t = Trie()
t.insert_all_prefixes(content)
longest_rep = t.get_longest_repeating()
rep_count = t.count_occurences(longest_rep)

print("Repeating:", longest_rep)
print("Count:", rep_count)