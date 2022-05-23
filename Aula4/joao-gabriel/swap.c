#include <stdio.h>

void swap_wrong(int a, int b);
void swap(int* a, int* b);
int main(void) {
  int x = 1;
  int y = 2;

  printf("\n\033[01m[main-before]\033[m x is %i, y is %i\n", x, y);
  
  swap_wrong(x, y);
  printf("\t[main-after_wrong_swap] x is %i, y is %i\n", x, y);

  swap(&x, &y);
  printf("\n\033[01m[main-after_correct_swap]\033[m x is %i, y is %i\n\n", x, y);

}

void swap_wrong(int a, int b) {
  // a and b are copies of the value of x and y
  printf("\n\t\t[wrong_swap-local] a is %i, b is %i\n", a, b);
  int tmp = a;
  a = b;
  b = tmp;
  printf("\t\t[wrong_swap-local] a is %i, b is %i\n\n", a, b);
}


void swap(int* a, int* b) {
  // a and b are copies that stores the addresses of x and y
  // *a and *b defer values that a and b points to
  int tmp = *a;
  *a = *b;
  *b = tmp;
}