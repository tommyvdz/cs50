import sys
from sys import argv
import cs50
import csv


if len(argv) != 2:
    print("Usage: python import.py file.csv")
    sys.exit(1)
elif ".csv" not in argv[1]:
    print("Usage: python import.py file.csv")
    sys.exit(1)

file = argv[1]
db = cs50.SQL("sqlite:///students.db")

with open(file, "r") as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        # initalize variables
        names = row["name"].split()
        first = ""
        middle = ""
        last = ""
        house = row["house"]
        birth = row["birth"]

        if len(names) == 2:
            first = names[0]
            last = names[1]
            db.execute("INSERT INTO students (first, last, house, birth) VALUES(?, ?, ?, ?)", first, last, house, birth)
        elif len(names) == 3:
            first = names[0]
            middle = names[1]
            last = names[2]
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       first, middle, last, house, birth)

