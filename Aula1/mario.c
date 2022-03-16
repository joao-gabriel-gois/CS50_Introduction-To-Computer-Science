#include <stdio.h>
#include <cs50.h>


// (1) - Declaring Functions (as in headers - .h files)
void print_square(int square_size);


// (2) - Main Flow
int main(void) {
  int size = get_int("What is the size you want your square? ");
  print_square(size);
}


// (3) - Assigning functions
void print_square(int square_size)  {
  printf("\n");

  // i <=> row; j <=> column;
  for (int row = 0; row < square_size; row++) {
    for (int column = 0; column < square_size; column++) {
      printf("#");
    }

    // Everytime a row is printed, break a line once 
    // it reachs the square size (the 10th column) to
    // start all over again for next row
    printf("\n");
  }

  printf("\n");
}
