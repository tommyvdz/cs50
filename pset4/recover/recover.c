#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int BLOCKSIZE = 512;

void findImages(FILE *imagefile);

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

    //find the actual JPEGs in the given file
    findImages(imagefile);

    //close the current file
    fclose(imagefile);
    return 0;

}

void findImages(FILE *imagefile)
{
    BYTE block[BLOCKSIZE];
    int filecount = 0;
    char filename[8] = {};
    bool openFile = false;
    FILE *img;

    while (fread(block, BLOCKSIZE, 1, imagefile) == 1)
    {
        // Check first three bytes for pattern and look at first four bits of 4th byte
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            if (openFile) //if already working on a file, close that file and open a new one
            {
                fclose(img);
                filecount++;
                sprintf(filename, "%.3i.jpg", filecount);
                img = fopen(filename, "w");
                fwrite(block, 1, 512, img);
            }
            else //open a new file
            {
                sprintf(filename, "%.3i.jpg", filecount);
                img = fopen(filename, "w");
                openFile = true;
                fwrite(block, 1, 512, img);
            }

        }
        else //if no JPEG block is found, check if we are currently writing to a file, then continue writing. If not, do nothing
        {
            if (openFile)
            {
                fwrite(block, 1, 512, img);
            }
        }
    }
}


