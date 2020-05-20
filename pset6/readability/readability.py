from cs50 import get_string


text = get_string("Text: ")
w = len(text.split())  # splits the string in words using spaces as delimiter, then takes length as number of words
l = 0
s = 0

for i in text:
    if i.isalpha():  # each alphabetic character is counted as a letter
        l += 1
    elif i in [".", "?", "!"]:  # each . or ? or ! is counted as end of a sentence
        s += 1
l = l / w * 100  # divide by number of words and multiplied by a 100 gives the average number of letters per 100 words
s = s / w * 100

coleman = 0.0588 * l - 0.296 * s - 15.8  # calculate the Coleman Liau index

if coleman >= 16:
    print("Grade 16+")
elif coleman < 1:
    print("Before Grade 1")
else:
    print(f"Grade {int(round(coleman))}")
