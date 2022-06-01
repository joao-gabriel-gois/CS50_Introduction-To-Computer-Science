#include <math.h>
#include <stdio.h>
#include "helpers.h"

const float RGBT_BYTES_SIZE = 3.0;
const int PIXEL_BLUR_RANGE = 9;

// Util for sepia
BYTE convert_result_and_validate_byte(float byte);

// Utils for blur
int fix_r(int index, int height);
int fix_c(int index, int width);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // looping through every pixel
    for (int column = 0; column < width; column++)
    {
        for (int row = 0; row < height; row++)
        {
            BYTE c_pixel_gray_level = round((float)(
                image[row][column].rgbtBlue
                + image[row][column].rgbtGreen
                + image[row][column].rgbtRed
            ) / RGBT_BYTES_SIZE);

            image[row][column].rgbtBlue = c_pixel_gray_level;
            image[row][column].rgbtGreen = c_pixel_gray_level;
            image[row][column].rgbtRed = c_pixel_gray_level;
        }

    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // looping through every pixel
    for (int column = 0; column < width; column++)
    {
        for (int row = 0; row < height; row++)
        {
            int c_blue = image[row][column].rgbtBlue;
            int c_green = image[row][column].rgbtGreen;
            int c_red = image[row][column].rgbtRed;

            BYTE new_blue_value = convert_result_and_validate_byte(0.131 * c_blue + 0.534 * c_green + 0.272 * c_red);
            BYTE new_green_value = convert_result_and_validate_byte(0.168 * c_blue + 0.686 * c_green + 0.349 * c_red);
            BYTE new_red_value = convert_result_and_validate_byte(0.189 * c_blue + 0.769 * c_green + 0.393 * c_red);

            image[row][column].rgbtBlue = new_blue_value;
            image[row][column].rgbtGreen = new_green_value;
            image[row][column].rgbtRed = new_red_value;
        }

    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // looping through every pixel
    for (int column = 0; column < width / 2; column++)
    {
        for (int row = 0; row < height; row++)
        {
            RGBTRIPLE tmp = image[row][column];
            //current = opposite
            image[row][column] = image[row][width - 1 - column];
            //opposite = tmp (current's value before updating above)
            image[row][width - 1 - column] = tmp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int h, w;
    w = width; h = height;

    RGBTRIPLE image_copy[height][width];

    for (int c = 0; c < width; c++)
    {
        for (int r = 0; r < height; r++)
            image_copy[r][c] = image[r][c];
    }

    // looping through every pixel
    for (int c = 0; c < width; c++)
    {
        for (int r = 0; r < height; r++)
        {
            int pixels_indexes_around[][2] =
            {
                {fix_r(r - 1, h), fix_c(c - 1, w)}, {fix_r(r - 1, h), fix_c(c, w)}, {fix_r(r - 1, h), fix_c(c + 1, w)},
                {fix_r(r, h), fix_c(c - 1, w)},     {fix_r(r, h),fix_c(c, w)},      {fix_r(r, h), fix_c(c + 1, w)},
                {fix_r(r + 1, h), fix_c(c - 1, w)}, {fix_r(r + 1, h), fix_c(c, w)}, {fix_r(r + 1, h),fix_c(c + 1, w)}
            };

            int curr_column_around, curr_row_around;
            int counter = 0;
            
            /* bellow there is an array for the sum for each color
                                B  G  R */
            int sum_result[] = {0, 0, 0};

            // looping through every round pixel (3x3 box with current pixel in the center)
            for (int i = 0; i < PIXEL_BLUR_RANGE; i++)
            {
                curr_row_around = fix_r(pixels_indexes_around[i][0], h);
                curr_column_around = fix_c(pixels_indexes_around[i][1], w);

                // if we are in valid pixel (inside image area, sum it and count the valid pixel)
                if (curr_column_around != -1 && curr_row_around != -1)
                {
                    sum_result[0] += (int) image_copy[curr_row_around][curr_column_around].rgbtBlue;
                    sum_result[1] += (int) image_copy[curr_row_around][curr_column_around].rgbtGreen;
                    sum_result[2] += (int) image_copy[curr_row_around][curr_column_around].rgbtRed;

                    counter++;
                }
            }

            // getting average of valid pixels around
            int final_rgbtBlue = round((float) sum_result[0] / (float) counter);
            int final_rgbtGreen = round((float) sum_result[1] / (float) counter);
            int final_rgbtRed = round((float) sum_result[2] / (float) counter);

            // assigning it to current pixel in real image
            image[r][c].rgbtBlue = (BYTE) final_rgbtBlue;
            image[r][c].rgbtGreen = (BYTE) final_rgbtGreen;
            image[r][c].rgbtRed = (BYTE) final_rgbtRed;
        }
    }

    return;
}

// Util for sepia
BYTE convert_result_and_validate_byte(float result)
{
    int byte_result = round(result);
    return (
        byte_result > 255 // if
        ? 255             // do eval
        : byte_result < 0 // else if
            ? 0           // do eval
            : (BYTE) byte_result // else do eval
    );
}

// Utils for blur
int fix_r(int index, int height)
{
    return (
        index < 0 || index > height - 1
            ? -1
            : index
    );
}

int fix_c(int index, int width)
{
    return (
        index < 0 || index > width - 1
            ? -1
            : index
    );
}
