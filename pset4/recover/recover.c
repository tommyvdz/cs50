#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

void findImages(FILE* imagefile);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open file
    FILE *imagefile = fopen(argv[1], "r");

    if (!imagefile)
    {
        printf("Error reading file");
        return 1;
    }

    findImages(imagefile);

    fclose(imagefile);
    return 0;

}

void findImages(FILE* imagefile)
{
    BYTE block[512];
    int filecount = 0;
    char filename[8] ={};

    while (fread(block, 512, 1, imagefile) == 1)
    {
         // Check first three bytes for pattern and look at first four bits of 4th byte
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            // implement fwrite and find a way to continue writing the next block until a new start of a jpeg is found
            sprintf(filename, "%.3i.jpg", filecount);
            FILE *img = fopen(filename,"w");
            filecount++;
        }
        else
        {
            printf("No\n");
        }
    }

}
