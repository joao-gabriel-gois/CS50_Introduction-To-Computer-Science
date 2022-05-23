#include <cs50.h>
#include <stdio.h>

int collatz(int n);


int main(void) {
  int number_to_test = get_int("Insert a number to calculate collatz steps: ");
  int steps = collatz(number_to_test);

  printf("%i\n", steps);
}

int collatz(int n) {
  if (n == 1)
    return 0;
  
  if (n % 2 == 0)
    return 1 + collatz(n / 2);
  else
    return 1 + collatz(3 * n + 1);
}

