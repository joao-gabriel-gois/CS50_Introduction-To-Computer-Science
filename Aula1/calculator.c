#include <stdio.h>
#include <cs50.h>

// Code for complete basic calculator using almost all examples
//   of this class (missing loops, but it will be in other projects)

// Declaring Functions
float calculate(int x, int y, char operator);
void print_line(string before_message);
char fix_if_unvalid_operator(char operator);
void print_result(int x, char operator, int y, float result);


int main(void) {
  int i = get_int("How many calculations you'll do? ");
  print_line("\n");

  while (i > 0) {
    int x = get_int("\033[01mx: \033[m");
    char operator = get_char("\033[01mOperator: \033[m");
    int y = get_int("\033[01my: \033[m");
    float result = calculate(x, y, operator);

    operator = fix_if_unvalid_operator(operator);
  
    print_result(x, operator, y, result);
    
    i--;

    if (i == 0) printf("\n");
  }
}


// Assigning functions
float calculate(int x, int y, char operator)  {
  if (operator == '+') return x + y;
  else if (operator == '-') return x - y;
  else if (operator == '*') return x * y;
  else if (operator == '/') return (float) x / (float) y; // casting float
  else {
    printf("\n\t\033[01;31mSorry, but '%c' is not a valid input", operator);
    printf("\n  [only '+', '-', '*' or '/' chars are valid operators]");
    printf("\n\t\tPlease try again\n\033[m");
    printf("\n\033[01;33mReturning the sum value \033[01;37m(default)\033[m");
    return x + y;
  }
}


void print_line(string before_message) {
  printf("%s", before_message);
  for (int c = 0; c < 30; c++) printf("-");
  printf("\n");
}

void print_result(int x, char operator, int y, float result) {
  printf(
    "\n%sResult:%s %s%i%s %c %s%i%s = %s%.4f%s\n",
    "\033[36m",
    "\033[m",
    "\033[01m",
    x,
    "\033[m",
    operator,
    "\033[01m",
    y,
    "\033[m",
    "\033[32;01m",
    result,
    "\033[m"
  );
  
  print_line("");
}

char fix_if_unvalid_operator(char operator) {
  return (
    operator == '+' || operator == '-' || operator == '*' || operator == '/'
  ) ? operator : '+';
}
