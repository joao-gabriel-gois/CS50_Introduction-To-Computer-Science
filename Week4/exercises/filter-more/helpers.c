#include <math.h>
#include "helpers.h"


const float RGBT_BYTES_SIZE = 3.0;
const int PIXEL_BLUR_RANGE = 9;

BYTE convert_result(float result);

// Utils for blur and edges
int fix_r(int index, int height);
int fix_c(int index, int width);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
  // looping through every pixel
  for (int column = 0; column < width; column++) {
    for (int row = 0; row < height; row++) {
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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
  // looping through every pixel
  for (int column = 0; column < width / 2; column++) {
    for (int row = 0; row < height; row++) {
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
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  int h, w;
  w = width; h = height;

  RGBTRIPLE img_copy[height][width];

  for (int c = 0; c < width; c++) {
    for (int r = 0; r < height; r++)
      img_copy[r][c] = image[r][c];
  }

  // looping through every pixel
  for (int c = 0; c < width; c++) {
    for (int r = 0; r < height; r++) {
      // linearized matrix for pixels arround, with values for both row and column indexes
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
      for (int i = 0; i < PIXEL_BLUR_RANGE; i++) {
        curr_row_around = fix_r(pixels_indexes_around[i][0], h);
        curr_column_around = fix_c(pixels_indexes_around[i][1], w);

        // if we are in valid pixel (inside image area, sum it and count the valid pixel)
        if (curr_column_around != -1 && curr_row_around != -1) {
          sum_result[0] += img_copy[curr_row_around][curr_column_around].rgbtBlue;
          sum_result[1] += img_copy[curr_row_around][curr_column_around].rgbtGreen;
          sum_result[2] += img_copy[curr_row_around][curr_column_around].rgbtRed;

          counter++;
        }
      }

      // getting average of valid pixels around and assigning it to current pixel in real image
      image[r][c].rgbtBlue = (BYTE) round((float) sum_result[0] / (float) counter);
      image[r][c].rgbtGreen = (BYTE) round((float) sum_result[1] / (float) counter);
      image[r][c].rgbtRed = (BYTE) round((float) sum_result[2] / (float) counter);
    }
  }

  return;
}

// Detect edges - instead of sepia from filter-less
void edges(int height, int width, RGBTRIPLE image[height][width]) {
  int h, w;
  w = width; h = height;

  // linearized matrix for horizontal and vertical components of filter
  const int gx_kernel[] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
  const int gy_kernel[] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

  RGBTRIPLE img_copy[height][width];

  for (int c = 0; c < width; c++) {
      for (int r = 0; r < height; r++)
          img_copy[r][c] = image[r][c];
  }

  // looping through every pixel
  for (int c = 0; c < width; c++) {
    for (int r = 0; r < height; r++) {   
      // linearized matrix for pixels arround, with values for both row and column indexes
      int pixels_indexes_around[][2] =
      {
        {fix_r(r - 1, h), fix_c(c - 1, w)}, {fix_r(r - 1, h), fix_c(c, w)}, {fix_r(r - 1, h), fix_c(c + 1, w)},
        {fix_r(r, h), fix_c(c - 1, w)},     {fix_r(r, h),fix_c(c, w)},      {fix_r(r, h), fix_c(c + 1, w)},
        {fix_r(r + 1, h), fix_c(c - 1, w)}, {fix_r(r + 1, h), fix_c(c, w)}, {fix_r(r + 1, h),fix_c(c + 1, w)}
      };

      int curr_column_around, curr_row_around;
      //int counter = 0;

      /* bellow there is an array for the sum for each color
                             B  G  R */
      int gx_sum_result[] = {0, 0, 0};
      int gy_sum_result[] = {0, 0, 0};

      // looping through every round pixel (3x3 box with current pixel in the center)
      for (int i = 0; i < PIXEL_BLUR_RANGE; i++) {
        curr_row_around = fix_r(pixels_indexes_around[i][0], h);
        curr_column_around = fix_c(pixels_indexes_around[i][1], w);

        // if we are in valid pixel (inside image area, sum it and count the valid pixel)
        if (curr_column_around != -1 && curr_row_around != -1) {
          // casting is required in this case! otherwise we can not use values bigger than 255 (specially in *2 or *-2 or *-1 mult.)
          gx_sum_result[0] += gx_kernel[i] * (int) img_copy[curr_row_around][curr_column_around].rgbtBlue;
          gx_sum_result[1] += gx_kernel[i] * (int) img_copy[curr_row_around][curr_column_around].rgbtGreen;
          gx_sum_result[2] += gx_kernel[i] * (int) img_copy[curr_row_around][curr_column_around].rgbtRed;

          gy_sum_result[0] += gy_kernel[i] * (int) img_copy[curr_row_around][curr_column_around].rgbtBlue;
          gy_sum_result[1] += gy_kernel[i] * (int) img_copy[curr_row_around][curr_column_around].rgbtGreen;
          gy_sum_result[2] += gy_kernel[i] * (int) img_copy[curr_row_around][curr_column_around].rgbtRed;
        }
      }

      // getting √(Gx² + Gy²) for each color channel
      float final_blue = sqrt(pow(gx_sum_result[0], 2) + pow(gy_sum_result[0], 2));
      float final_green = sqrt(pow(gx_sum_result[1], 2) + pow(gy_sum_result[1], 2));
      float final_red = sqrt(pow(gx_sum_result[2], 2) + pow(gy_sum_result[2], 2));

      // assigning it to current pixel in real image
      image[r][c].rgbtBlue = convert_result(final_blue);
      image[r][c].rgbtGreen = convert_result(final_green);
      image[r][c].rgbtRed =  convert_result(final_red);
    } 
  }

  return;
}

// Util for edges
BYTE convert_result(float result) {
  int rounded_result = round(result);
  return rounded_result > 255 ? 255 : (BYTE) rounded_result;
}

// Utils for blur and edges
int fix_r(int index, int height) {
  return (
    index < 0 || index > height - 1
      ? -1
      : index
  );
}

int fix_c(int index, int width) {
  return (
    index < 0 || index > width - 1
      ? -1
      : index
  );
}
