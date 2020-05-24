import sys
from sys import argv
import cs50
import csv

# check correct commandline arguments
if len(argv) != 2:
    print("Usage: python roster.py house")
    sys.exit(1)

house = argv[1]
db = cs50.SQL("sqlite:///students.db")

# execute query, store result in variable query, inset name of house as filter
query = db.execute(f"SELECT last, middle, first, birth FROM students WHERE house =\"{house}\" ORDER BY last ASC, first ASC;")

# iterate over each dict in the returned list and print result
for person in query:
    first = person['first']
    middle = person['middle']
    last = person['last']
    birth = person['birth']

    # logic to deal with optional middle name
    if middle == None:
        print(f"{first} {last}, born {birth}")
    else:
        print(f"{first} {middle} {last}, born {birth}")