import os
import pandas as pd
import json
from common import *

all_book_names = set()
for filename in os.listdir("raw_data/book/"):
	print("Reading file", filename)
	csv = pd.read_csv("raw_data/book/" + filename)
	for _, row in csv.iterrows():
		book_name = process_book_name(row["Name"])
		all_book_names.add(book_name)

print("Ended reading files")
print("Started creating id dict")
book_id_dict = {}
for i, e in enumerate(all_book_names):
	book_id_dict[e] = i

print("Saving id dict")
with open('book_ids.json', 'w') as fp:
  json.dump(book_id_dict, fp)