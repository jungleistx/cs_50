#include "helpers.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    int     i;
    int     j;
    int     new_blue;
    int     new_red;
    int     new_green;

    srand(time(NULL));      // seed the rand-function
    new_green = rand() % 255;   // random number 0-255
    new_blue = rand() % 255;
    new_red = rand() % 255;
    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            if (image[i][j].rgbtBlue == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtRed == 0)        // all black
            {
                image[i][j].rgbtBlue = new_blue;
                image[i][j].rgbtRed = new_red;
                image[i][j].rgbtGreen = new_green;
            }
            j++;
        }
        i++;
    }
}
