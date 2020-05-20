from cs50 import get_string
import math


def main():
    n = get_string("Number: ")
    if len(n) in [13, 15, 16] and checksum(n[::-1]):  # using [::-1] it passes the string in reverse order
        print(cctype(int(n[:2])))  # the string is sliced to only the first two characters, and converted to int
    else:
        print("INVALID")  # if the length and/or checksum is invalid it must be invalid


def checksum(n):

    result = 0
    d2 = []
    for i, c in enumerate(n):  # using enumerate you get the index (i) instead of only the character
        if i % 2 != 0:  # i starts at 0, so if the modulo of 2 is zero it concerns the 2nd character
            if int(c) < 5:  # double digits need to be processed one by one, so I check if the number is smaller than 5
                result += 2 * int(c)
            else:
                result += (2 * int(c)) % 10
                result += ((2 * int(c)) - ((2 * int(c)) % 10)) / 10
        else:
            result += int(c)

    if result % 10 == 0:
        return True
    else:
        return False


def cctype(n):
    if 40 <= n <= 49:  # if first digit is 4 its a VISA card
        return "VISA"
    if n == 34 or n == 37:
        return "AMEX"
    if 51 <= n <= 55:
        return "MASTERCARD"
    else:  # to be sure, if the checksum and length are corrected but the first digits are not recognized it is still invalid.
        return "INVALID"


main()
