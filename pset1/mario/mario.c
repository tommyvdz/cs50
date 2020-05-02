#include <stdio.h>
#include <cs50.h>

void pyramid(int h);
void hash(int i);
void gap(int i, int h);
int get_valid_input(void);

int main(void)
{
    //ask for the height of the pyramid
    int height = get_valid_input();

    //call function pyramid and pass the height as input
    pyramid(height);
}

//validates if the input is between 1 and 8. If not it will continue to ask the user for input
int get_valid_input(void)
{
    int n;
    do
    {
        n = get_int("How tall do you want the pyramid to be?\n");
    }
    while (n < 1 || n > 8);
    return n;
}

void pyramid(int h)
{
    //iterate until height is reached
    for (int i = 0; i < h; i++)
    {

        //print gaps before the hashes
        gap(i, h);

        //print the first set of hashes
        hash(i);

        //prints the gap in between the hashes
        printf("  ");

        //prints the second set of hashes
        hash(i);

        //move to a new line
        printf("\n");
    }
}

//prints hashes when called
void hash(int i)
{
    for (int j = 0; j <= i; j++)
    {
        printf("#");
    }
}


//prints gaps when called
void gap(int i, int h)
{
    // store the number of gaps for the current line
    int gaps = h - i - 1;
    for (int j = 0; j < gaps; j++)
    {
        printf(" ");
    }
}

