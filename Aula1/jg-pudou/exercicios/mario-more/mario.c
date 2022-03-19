#include <cs50.h>
#include <stdio.h>

void print_left_spaces(int height, int row);
void print_grid(int height, int row);
void print_triangle(int height);


int main(void) {
  int height = get_int("Height: ");

  print_triangle(height);

  return 0;
}


// Utils
void print_triangle(int height) {
  printf("\n");

  for (int row = 1; row <= height; row++) { 
    print_left_spaces(height, row);
    print_grid(height, row);
    printf(" ");
    print_grid(height, row);
    printf("\n");
  }

  printf("\n");
}


void print_left_spaces(int height, int row) {
  int n_spaces = height - row;

  for (int s = 0; s < n_spaces; s++) {
    printf(" ");
  }
}


void print_grid(int height, int row) {
  for (int right_grid = 0; row > right_grid; right_grid++) {
    printf("#");
  }
}
