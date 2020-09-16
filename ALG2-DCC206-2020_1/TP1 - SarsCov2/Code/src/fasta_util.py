class FastaUtil:
  @staticmethod
  def load_fasta(path):
    with open(path) as fasta:
      lines = fasta.readlines()
      meta = lines[0]
      content = ("".join(lines[1:])).replace("\n", "")
      return meta, content
