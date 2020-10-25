import os
import pandas as pd
import json
from common import *

def get_book_id(book_name, book_ids):
	p_book_name = process_book_name(book_name)
	if p_book_name in book_ids:
		return book_ids[p_book_name]
	else:
		return -1

with open("book_ids.json") as book_ids_file:
	book_ids = json.load(book_ids_file)

	all_reviews = pd.DataFrame()
	for filename in os.listdir("raw_data/ratings/"):
		print("Reading file", filename)
		csv = pd.read_csv("raw_data/ratings/" + filename)
		csv.columns = map(str.lower, csv.columns)
		csv["book_id"] = csv.apply(lambda row: get_book_id(row["name"], book_ids), axis=1)
		all_reviews = all_reviews.append(csv, ignore_index=True)
	
	all_reviews["user_id"] = all_reviews["id"]
	del all_reviews["id"]
	del all_reviews["name"]
	all_reviews = all_reviews[all_reviews["book_id"] != -1]
	print(all_reviews.head())
	print(all_reviews.shape)
	all_reviews.to_csv("all_reviews.csv")