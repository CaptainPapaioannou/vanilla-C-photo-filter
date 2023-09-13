#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //iritate over pixels vertically
    for (int i = 0; i < height; i++)
    {
        //iritate over pixels horizontally
        for (int j = 0; j < width; j++)
        {
            //for grayscale we need to set all 3 colors to the average of the 3
            //we use 3.0 because its good practice to do float division and then use the round function
            //divide with ints can have round of errors
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //declare temp variable for swap
    RGBTRIPLE temp;

    //iritate over pixels vertically
    for (int i = 0; i < height; i++)
    {
        //we use %2 because if the number of width pixels is even the divsion with is fine
        // but if it is one we need to subtruct 1 as you can see bellow
        if (width % 2 == 0)
        {
            //iritate over pixels horizontally but only half way through
            for (int j = 0; j < width / 2 ; j++)
            {
                //we need to rearange the pixels to the equal opposite side horizontally
                temp = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = temp;
            }
        }
        else
        {
            //this is in case the width number of pixels is odd
            for (int j = 0; j < (width - 1) / 2 ; j++)
            {
                //we need to rearange the pixels to the equal opposite side horizontally
                temp = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = temp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //we need a new temporary image to copy the  avg values otherwise the change of values will affect the avg values of neighbor pixels
    //temporary image declaration
    RGBTRIPLE tempimage[height][width];

    //iritate over pixels vertically
    for (int i = 0; i < height; i++)
    {
        //iritate over pixels horizontally
        for (int j = 0; j < width ; j++)
        {

            //declare variables for the sum of each color
            float blurRed = 0;
            float blurGreen = 0;
            float blurBlue = 0;
            float counter = 0;


            //loop for 3x3 box
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    //this checks for pixels that are in the corners or edges vertically
                    if (i + x < 0 || i + x > height - 1)
                    {
                        continue;
                    }
                    //this checks for pixels that are in the corners or edges horizontally

                    if (j + y < 0 || j + y > width - 1)
                    {
                        continue;
                    }

                    //sum the 3x3 box
                    blurRed = blurRed + image[i + x][j + y].rgbtRed;
                    blurGreen = blurGreen + image[i + x][j + y].rgbtGreen;
                    blurBlue = blurBlue + image[i + x][j + y].rgbtBlue;
                    counter++;
                }

            }

            //storing values to the temporary image
            // divide sums with the counter (it cant be 9 because if we are at a corner/edge we dont have 9elements
            // we can have 6 etc so we use a counter wich is a float so we can divide perfectly)
            tempimage[i][j].rgbtRed = round((blurRed / counter));
            tempimage[i][j].rgbtGreen = round((blurGreen / counter));
            tempimage[i][j].rgbtBlue = round((blurBlue / counter));


        }
    }



    //now that we are finished, we copy the values back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tempimage[i][j].rgbtRed;
            image[i][j].rgbtGreen = tempimage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tempimage[i][j].rgbtBlue;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    //we need the Gx and Gy kernels for the computation of each color value
    //we will create the 2 kerners Gx and Gy as 2d arrays to use them later
    int Gx [3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy [3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};


    //we need a new temporary image to copy the  new values otherwise the change of values will affect the  values of neighbor pixels
    //temporary image declaration
    RGBTRIPLE tempimage[height][width];

    //iritate over pixels vertically
    for (int i = 0; i < height; i++)
    {
        //iritate over pixels horizontally
        for (int j = 0; j < width ; j++)
        {

            //declare variables for the sum of each multiplied color
            int GxRed = 0;
            int GxGreen = 0;
            int GxBlue = 0;
            int GyRed = 0;
            int GyGreen = 0;
            int GyBlue = 0;

            //3x3 box loop
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {

                    //check for corners or edges vertically
                    if (i + x < 0 || i + x > height - 1)
                    {
                        continue;
                    }

                    //check for corners or edges horizontally
                    if (j + y < 0 || j + y > width - 1)
                    {
                        continue;
                    }

                    //we sum the values multiplied by the corresponding number in the kernels we created
                    GxRed += image[i + x][j + y].rgbtRed * Gx[x + 1][y + 1];
                    GyRed += image[i + x][j + y].rgbtRed * Gy[x + 1][y + 1];
                    GxGreen += image[i + x][j + y].rgbtGreen * Gx[x + 1][y + 1];
                    GyGreen += image[i + x][j + y].rgbtGreen * Gy[x + 1][y + 1];
                    GxBlue += image[i + x][j + y].rgbtBlue * Gx[x + 1][y + 1];
                    GyBlue += image[i + x][j + y].rgbtBlue * Gy[x + 1][y + 1];
                }
            }

            //we store the square root of the sum of Gx and Gy values for each color
            //to the second power as per the specification
            int Red = round(sqrt(GxRed * GxRed + GyRed * GyRed));
            int Green = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            int Blue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));


            //we assign them to the temp image after we make sure we cap them at max 255
            tempimage[i][j].rgbtRed = (Red > 255) ? 255 : Red;
            tempimage[i][j].rgbtGreen = (Green > 255) ? 255 : Green;
            tempimage[i][j].rgbtBlue = (Blue > 255) ? 255 : Blue;

        }
    }

    //now that we are finished, we copy the values back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tempimage[i][j].rgbtRed;
            image[i][j].rgbtGreen = tempimage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tempimage[i][j].rgbtBlue;
        }
    }


    return;
}
