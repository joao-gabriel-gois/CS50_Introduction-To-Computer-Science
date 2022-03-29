#include <cs50.h>
#include <stdio.h>

//void print_crescent_sort_args(int a, int b, int c);
bool is_valid_triangle(float a, float b, float c);


int main(void) {
  float sizes[3];
  for (int i = 0; i < 3; i++) {
    sizes[i] = get_float("\033[33;01mSize \033[36m%i\033[m: ", i + 1);
  }
  printf("\n");

  bool is_valid = is_valid_triangle(sizes[0], sizes[1], sizes[2]);

  printf(
    "\033[01mThese values are%s valid as triangle sides\033[m\n",
    is_valid ? "" : "\033[31m not\033[m\033[01m"
  );
}



bool is_valid_triangle(float a, float b, float c) {
  if (a < 0 || b < 0 || c < 0) return false;

  return a + b > c && a + c > b && b + c > a;
}


// void print_crescent_sort_args(int a, int b, int c) {
//   if (a < 0 || b < 0 || c < 0) return;
//   int small;
//   int middle;
//   int big;

//   small = a <= b && a <= c ? a : (b <= a && b <= c ? b : c);

//   if (small == a) {
//     middle = b <= c ? b : c;
//     big = c >= b ? c : b;
//   }
//   else if (small == b) {
//     middle = a <= c ? a : c;
//     big = c >= a ? c : a;
//   }
//   else if (small == c) {
//     middle = b <= a ? b : a;
//     big = a >= b ? a : b;
//   }

//   printf("\n[ %i, %i, %i ]\n", small, middle, big);
// }
