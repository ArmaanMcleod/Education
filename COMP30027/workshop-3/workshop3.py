from csv import DictReader
from collections import defaultdict

classes = defaultdict(int)

with open('iris-data-nix.csv') as infile:
	csv_reader = DictReader(infile)
	headers = csv_reader.fieldnames

	for line in csv_reader:
		class_name = line['class']
		classes[class_name] += 1

for 