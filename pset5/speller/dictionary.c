// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 170000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    char *lcw = malloc(strlen(word) + 1);
    strcpy(lcw, word);
    for (int i = 0; i < strlen(lcw); i++)
    {
        lcw[i] = tolower(lcw[i]); //get lowercase string
    }

    int hword = hash(lcw);

    for (node *tmp = table[hword]; tmp != NULL; tmp = tmp->next)
    {
        if (strcmp(lcw, tmp->word) == 0)
        {
            free(lcw);
            return true;
        }
    }
    free(lcw);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //Adapted from Section 6.6 of the book: C Programming Language, 2nd Edition by Brian W. Kernighan & Dennis M. Ritchie
    unsigned hashval;
    for (hashval = 0; *word != '\0'; word++)
    {
        hashval = *word + 31 * hashval;
    }

    return hashval % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (!dict)
    {
        printf("Error loading dictionary\n");
        return false;
    }

    char w[LENGTH + 1]; //creates an array of chars with enough space for the max word.

    while (fgets(w, LENGTH + 2, dict) != NULL)  //reads throug the file line by line (fgets reads 1 character less than length)
    {
        w[strcspn(w, "\n")] =
            '\0'; //removes the newline character from the string (example found on stackoverlow 36903528/make-fgets-ignore-a-new-line)
        int hword = hash(w);
        node *n = malloc(sizeof(node)); //allocate memory for a node
        strcpy(n->word, w); //copies string w to n->word
        n->next = NULL; //sets address of next node to null

        if (table[hword] == NULL)
        {
            table[hword] = n;
        }
        else // if there is a node already it is moved down and linked to the new node placed at the beginning
        {
            n->next = table[hword];
            table[hword] = n;
        }

    }

    fclose(dict); //close the file after loading into hash table


    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int c = 0;
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
            {
                c++;
            }
        }
    }

    return c;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }

    return true;
}
