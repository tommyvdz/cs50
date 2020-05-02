#include <stdio.h>
#include <math.h>
#include <cs50.h>

//program to check valid checksum of credit card number. It will return type of credit card if valid or otherwise return invalid

long get_input(void); //returns number if adheres to specific credit card lengths
string cctype(long n); // returns string with creditcard provider or invalid
bool checksum(long n); // returns true if supplied number passes the checksum
int length(long n); //returns the number of digits in the supplied number
int first_digits(long n, int l); //returns the value of the first number of digits of the supplied number

int main(void)
{
    // ask for the number:
    long n;
    n = get_long("Number: ");

    //check whether the number has a valid length and then performs the checksum
    if (length(n) == 13 || length(n) == 15 || length(n) == 16)
    {
        if (checksum(n))
        {
            printf("%s\n", cctype(n));
        }
        else
        {
            printf("INVALID\n"); //if the checksum did not return true, the credit card number is invalid
        }
    }
    else
    {
        printf("INVALID\n"); //if the length doesnt match that of a valid credit card, number is invalid
    }
}

int length(long n)
{
    int l = 0;
    for (long i = 1; i <= n; i *= 10)
    {
        l += 1;
    }
    return l;
}

bool checksum(long n)
{
    int d1 = 0; //this will store the sum of all non multiplied digits
    int d2 = 0; // this will store the sum of all digits of the products
    long r = n; // this will store the remaining number
    int l = length(n);

    for (int i = 1; i <= l; i++)
    {
        int digit = r % 10;

        if (i % 2 == 0)
        {
            // if the digit is higher than 5 it results in a 2 digit number, for which the seperate digits need to be added to the sum
            if (digit < 5)
            {
                d2 += 2 * digit;
            }
            else
            {
                d2 += (2 * digit) % 10;
                d2 += ((2 * digit) - ((2 * digit) % 10)) / 10;
            }
        }
        else
        {
            d1 += digit;
        }
        //reduce the remaining number by the digit and divide by 10 to move one digit up
        r = (r - digit) / 10;
    }

    if ((d1 + d2) % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string cctype(long n)
{
    string s = "INVALID";

    //Check if VISA
    if (first_digits(n, 1) == 4)
    {
        s = "VISA";
    }
    //Check if AMEX
    else if (first_digits(n, 2) == 34 || first_digits(n, 2) == 37)
    {
        s = "AMEX";
    }
    //Check if Mastercard
    else if (first_digits(n, 2) == 51 || first_digits(n, 2) == 52 || first_digits(n, 2) == 53
             || first_digits(n, 2) == 54 || first_digits(n, 2) == 55)
    {
        s = "MASTERCARD";
    }

    return s;
}

int first_digits(long n, int l)
{
    return (n - (n % (long) pow(10, (length(n) - l)))) / (long) pow(10, (length(n) - l));
}


