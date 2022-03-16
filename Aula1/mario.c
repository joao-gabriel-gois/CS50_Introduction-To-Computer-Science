#include <stdio.h>
#include <cs50.h>

// (1) - Declaring Functions (as in headers - .h files)
void print_square(int square_size);
  // (1.b) - 3 diff ways to get user input
int get_size_from_user_do_while(void);
int get_size_from_user_while_true(void);
int get_size_from_user_recursion(int size);


// (2) - Main Flow
int main(void) {
  // (2.a) - Switch among different implementations,
    // using only one of them per compilation,
    // otherwise the last one called will overwrite
    // the others above it or throw errors:
  
  int size = get_size_from_user_do_while();
  // int size = get_size_from_user_while_true();
  // int size = get_size_from_user_recursion(0);

  print_square(size);
}


// (3) - Assigning functions:
  // (3.a) - Main logic, representing 2 dimensions with a nested loop
void print_square(int square_size)  {
  printf("\n");
  // i <=> row; j <=> column;
  for (int row = 0; row < square_size; row++) {

    for (int column = 0; column < square_size; column++) {
      printf("#");
    }
    // Everytime a row is printed, break a line once it reaches
      // the square size (the 10th column if size = 10) to start
      // all over again for next row
    printf("\n");
  }

  printf("\n");
}

  // (3.b) - 3 ways of performing the same thing:
int get_size_from_user_do_while() {
  int size;
  do {
    size = get_int("What is the size you want your square? ");
  } while (size <= 0);

  return size;
}


int get_size_from_user_while_true() {
  int size;
  while (true) {
    size = get_int("What is the size you want your square? ");
    
    if (size > 0) break;
  }

  return size;
}


int get_size_from_user_recursion(int size) {
  if (size > 0) return size;
    
  size = get_int("What is the size you want your square? ");
  return get_size_from_user_recursion(size);
}
