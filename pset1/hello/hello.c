#include <stdio.h>
#include <cs50.h>


int main(void)
{
    //ask for a name
    string name = get_string("What's your name?\n");

    //prints hello with the given name
    printf("hello, %s!\n", name);
}