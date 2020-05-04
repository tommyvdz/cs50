//pset2 - substitution
//program takes a key as command line argument, and then asks for a message as input. the result is a ciphertext encrypted using the key.
//author: Tommy van de Zande

#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool verifyInput(string key);
string substitute(string key, string message);
bool isAlphabetic(char c);
string toLowerCase(string s);


int main(int argc, string argv[])
{
    //check of argc 2 is!
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    //check if the key is valid
    if (!verifyInput(key))
    {
        printf("Please provide a valid key containing 26 unique alpabetic characters.\n");
        return 1;
    }

    //ask for message input
    string message = get_string("plaintext:");

    //print ciphertext
    printf("ciphertext: %s\n", substitute(key, message));

}

//check if there are no duplicate characters in the provided input
bool verifyInput(string key)
{

    //check if the provided input is exactly 26 characters long
    if (strlen(key) != 26)
    {
        printf("keylength is %lu\n", strlen(key));
        return false;
    }

    for (int i = 0, n = strlen(key); i < n; i++)
    {
        //check if input contains only alphabetic characters
        if (!isAlphabetic(key[i]))
        {
            printf("non alpabetic\n");
            return false;
        }

        //check if input contains only unique charactes

        for (int j = i + 1; j < n; j++)
        {
            if (key[i] == key[j])
            {
                printf("non unique\n");
                return false;
            }
        }

    }
    return true;
}

string substitute(string key, string message)
{
    string m = message;
    string k = toLowerCase(key);
    string alpha = "abcdefghijklmnopqrstuvwxyz";

    // iterate through the message
    for (int i = 0, n = strlen(m); i < n; i++)
    {
        //if a character in the message is a-z or A-Z:
        if (isAlphabetic(m[i]))
        {
            //then find that characters position in the alphabet string
            for (int j = 0, o = strlen(alpha); j < o; j++)
            {
                //when found, replace it with the character at the same position in the key string, then break the for-loop.
                if (message[i] == alpha[j])
                {
                    m[i] = k[j];
                    break;
                }
                //if the character in the message is uppercase, replace it with the uppercase equivalent in key
                if (message[i] == alpha[j] - 32)
                {
                    m[i] = k[j] - 32;
                    break;
                }
            }

        }

    }
    return m;
}

//checks if a character is either a-z or A-Z.
bool isAlphabetic(char c)
{
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
    {
        return true;
    }
    else
    {
        return false;
    }
}


//converts a string to lowercase characters so that input can be treated case insensitive
string toLowerCase(string s)
{

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] >= 65 && s[i] <= 90)
        {
            s[i] += 32;
        }
    }

    return s;
}