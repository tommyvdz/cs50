import sys
from sys import argv
import csv


def main():

    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)
    elif ".csv" not in argv[1]:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)
    elif ".txt" not in argv[2]:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    db, strc = load(argv[1])

    with open(argv[2], "r") as file:
        dnaseq = file.read()

    oc = {}

    for s in strc:
        oc[s] = findseq(s, dnaseq)

    findmatch(oc, db)

    sys.exit(0)


def load(file):
    db = {}
    with open(file, "r") as csvfile:
        reader = csv.reader(csvfile)
        strc = next(reader)[1:]
        for row in reader:
            db[str(row[1:])] = row[0]
        return db, strc


def findseq(s, dnaseq):
    l = len(s)
    maxlength = len(dnaseq)
    counter = 0
    maxc = 0
    i = 0

    if dnaseq.find(s) == -1:
        return 0
    else:
        while i < maxlength:  # runs through dna sequence
            if i+l < maxlength:
                if dnaseq[i:i + l] == s:
                    counter += 1
                    i = i+l
                    continue
                else:
                    if counter > maxc:  # update the new max if the counter exceeded the max
                        maxc = counter
                        counter = 0
                    else:
                        counter = 0
            i += 1

    return maxc


def findmatch(oc, db):
    seq = []
    for i in oc:
        seq.append((str(oc[i])))
    if str(seq) in db:
        print(db[str(seq)])
    else:
        print("No Match")


main()

