from cs50 import get_int


def main():
    n = 0
    valid = range(1, 9)  # upper limit is exclusive, so 1 higher than actual range
    while n not in valid:
        n = get_int("Height: ")
    o = n
    pyramid(n, o)


def pyramid(n, o):
    if n == 0:
        return
    else:
        pyramid(n-1, o)
        print(" " * (o-n), end="")  # print leading spaces
        print("#" * n, end="")  # print n blocks
        print("  ", end="")  # print 2 middle spaces
        print("#" * n, end="")  # print n blocks
        print("")  # newline


main()
