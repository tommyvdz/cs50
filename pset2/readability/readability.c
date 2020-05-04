#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int letters(string text);
int words(string text);
int sentences(string text);
int coleman_index(int letters, int words, int sentences);

int main(void)
{
    string s = get_string("Text: ");
    int index = coleman_index(letters(s), words(s), sentences(s));

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

//iterate through the string and increment l for every letter found
int letters(string text)
{
    int l = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            l++;
        }
    }

    return l;
}

//iterate through the string and increment w for every word found.
//it looks for a word by looking for a space or a dot or comma etc.
//and then looking back at the previous char to verify that is a letter.
int words(string text)
{
    int w = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 32 || text[i] == 33 || text[i] == 44 || text[i] == 46 || text[i] == 58 || text[i] == 59 || text[i] == 63)
        {
            if (((text[i - 1] >= 65 && text[i - 1] <= 90) || (text[i - 1] >= 97 && text[i - 1] <= 122)))
            {
                w++;
            }
        }
    }

    return w;
}

//iterate through the string and increment s for every sentence found.
//it looks for a . ! or ? and then looks if the previous char was a letter
int sentences(string text)
{
    int s = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 33 || text[i] == 63 || text[i] == 46)
        {
            if (((text[i - 1] >= 65 && text[i - 1] <= 90) || (text[i - 1] >= 97 && text[i - 1] <= 122)))
            {
                s++;
            }
        }
    }

    return s;
}

//calculates the index using a given formula, returning a rounded integer
int coleman_index(int letters, int words, int sentences)
{
    int result = 0;
    float l = 0;
    float s = 0;
    float index = 0;

    //calculates average number of letters per 100 words
    l = ((float) letters * 100) / (float) words;
    //calculates average number of sentences per 100 words
    s = ((float) sentences * 100) / (float) words;
    index = round((0.0588 * l) - (0.296 * s) - 15.8);
    result = (int) index;

    return result;
}