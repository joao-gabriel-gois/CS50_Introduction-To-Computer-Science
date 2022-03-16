#include <stdio.h>
#include <cs50.h>

// Code for complete basic calculator using almost all examples
//   of this class (missing loops, but it will be in other projects)

float calculate(float x, float y, char operator) {
  if (operator == '+') return x + y;
  else if (operator == '-') return x - y;
  else if (operator == '*') return x * y;
  else if (operator == '/') return x / y;
  else {
    printf("\nPlease try again with a valid operator");
    printf("[only + - * / will be accepted]\n");
    printf("\nReturning the sum value (default)\n\n");
    return x + y;
  }
}

int main(void) {
  float x = get_float("x: ");
  float y = get_float("y: ");
  char operator = get_char("Operator: ");
  
  float result = calculate(x, y, operator);
  
  printf("\nYour result for %.2f %c %.2f is %.2f\n", x, operator, y, result);
}

