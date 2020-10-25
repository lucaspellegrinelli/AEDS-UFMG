import os
import pandas as pd
import json
from common import *

with open("book_ids.json") as book_ids_file:
	book_ids = json.load(book_ids_file)

	all_books = pd.DataFrame()
	for filename in os.listdir("raw_data/book/"):
		print("Reading file", filename)
		csv = pd.read_csv("raw_data/book/" + filename)
		csv.columns = map(str.lower, csv.columns)
		csv["id"] = csv.apply(lambda row: book_ids[process_book_name(row["name"])], axis=1)
		all_books = all_books.append(csv, ignore_index=True)

	print(all_books.head())
	print(all_books.shape)
	all_books = all_books.set_index("id")
	all_books.to_csv("all_books.csv")