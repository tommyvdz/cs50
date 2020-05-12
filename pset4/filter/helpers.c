#include "helpers.h"
#include <stdio.h>
#include <math.h>

void avgColors(int i, int j, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE copy[height][width]);
int sobel(int i, int j, int height, int width, RGBTRIPLE image[height][width], char color);
int applySobelCalculation(int gx, int gy);



// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    //calculate average value and set grayscale as value for all 3 colors
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int greyscale = round(((double) image[i][j].rgbtBlue + (double) image[i][j].rgbtGreen + (double) image[i][j].rgbtRed) / (double) 3);

            image[i][j].rgbtBlue = greyscale;
            image[i][j].rgbtGreen = greyscale;
            image[i][j].rgbtRed = greyscale;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int w = round((double) width / 2.0); //only swap the first half of the column

    for (int i = 0; i < height; i++)
    {
        //for each row we swap each pixel until the middle
        int k = width - 1;
        for (int j = 0; j < w; j++)
        {
            RGBTRIPLE temppixel = image[i][k];
            image[i][k] = image[i][j];
            image[i][j] = temppixel;
            k--;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width]; //stores copy

    //create a copy of the image to keep a reference
    for (int ii = 0; ii < height; ii++)
    {
        for (int jj = 0; jj < width; jj++)
        {
            copy[ii][jj] = image[ii][jj];
        }
    }

    //iterate through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //average the colors of each pixel with its surrounding 3x3 matrix
            avgColors(i, j, height, width, image, copy);
        }
    }
    return;
}

void avgColors(int i, int j, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE copy[height][width])
{
    float avgRed = 0;
    float avgBlue = 0;
    float avgGreen = 0;
    int a = 0; //counts the number of pixels added

    //iterate through the 3x3 matrix of the copied image
    for (int i2 = -1; i2 < 2; i2++)
    {
        for (int j2 = -1; j2 < 2; j2++)
        {
            //conditions to prevent array out of bounds
            if ((i + i2 > -1) && (i + i2 < height) && (j + j2 > -1) && (j + j2 < width))
            {
                avgRed += copy[i + i2][j + j2].rgbtRed;
                avgGreen += copy[i + i2][j + j2].rgbtGreen;
                avgBlue += copy[i + i2][j + j2].rgbtBlue;
                a++; //counter to use for division
            }

        }
    }

    //calculate averages
    avgRed /= (float) a;
    avgGreen /= (float) a;
    avgBlue /= (float) a;

    //update result image
    image[i][j].rgbtRed = round(avgRed);
    image[i][j].rgbtGreen = round(avgGreen);
    image[i][j].rgbtBlue = round(avgBlue);

}



// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width]; //stores copy

    //create a copy of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    //iterate through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = sobel(i, j, height, width, copy, 'r');
            image[i][j].rgbtGreen = sobel(i, j, height, width, copy, 'g');
            image[i][j].rgbtBlue = sobel(i, j, height, width, copy, 'b');
        }
    }

    return;
}

int sobel(int i, int j, int height, int width, RGBTRIPLE copy[height][width], char color)
{
    int inputGx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int inputGy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    int gx = 0;
    int gy = 0;
    int result = 0;



    if (color == 'r')
    {
        for (int i2 = -1; i2 < 2; i2++)
        {
            for (int j2 = -1; j2 < 2; j2++)
            {
                if ((i + i2 > -1) && (i + i2 < height) && (j + j2 > -1) && (j + j2 < width))
                {
                    gx += copy[i + i2][j + j2].rgbtRed * inputGx[i2 + 1][j2 + 1];
                    gy += copy[i + i2][j + j2].rgbtRed * inputGy[i2 + 1][j2 + 1];
                }
            }
        }
    }

    else if (color == 'g')
    {
        for (int i2 = -1; i2 < 2; i2++)
        {
            for (int j2 = -1; j2 < 2; j2++)
            {
                if ((i + i2 > -1) && (i + i2 < height) && (j + j2 > -1) && (j + j2 < width))
                {
                    gx += copy[i + i2][j + j2].rgbtGreen * inputGx[i2 + 1][j2 + 1];
                    gy += copy[i + i2][j + j2].rgbtGreen * inputGy[i2 + 1][j2 + 1];
                }
            }
        }
    }

    else if (color == 'b')
    {
        for (int i2 = -1; i2 < 2; i2++)
        {
            for (int j2 = -1; j2 < 2; j2++)
            {
                if ((i + i2 > -1) && (i + i2 < height) && (j + j2 > -1) && (j + j2 < width))
                {
                    gx += copy[i + i2][j + j2].rgbtBlue * inputGx[i2 + 1][j2 + 1];
                    gy += copy[i + i2][j + j2].rgbtBlue * inputGy[i2 + 1][j2 + 1];
                }
            }
        }
    }
    return applySobelCalculation(gx, gy);
}

//gets the gx and gy input and applies sobel algo, returning the result capped at 255.
int applySobelCalculation(int gx, int gy)
{
    int result = round(sqrt(pow(gx, 2) + pow(gy, 2)));

    if (result > 255)
    {
        return 255;
    }

    else
    {
        return result;
    }
}

