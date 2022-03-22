#include <cs50.h>
#include <stdio.h>
#include <math.h>

// Business Logic Funtions
int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);
// Additional business logic (bellow):
// - it will only consider last 2 digits for a given input
int adjust_cents_to_last_2_digits(int cents);

// Utils
int get_int_length(int integer);



int main(void) {
  // [cs50-comments] Ask how many cents the customer is owed
  int cents = get_cents();

  // [cs50-comments] Calculate the number of quarters to give the customer
  // [my-comment] Remove quarters value from remaining cents
  int quarters = calculate_quarters(cents);
  cents = cents - quarters * 25;

  // [my-comment] Same logic but for dimes
  int dimes = calculate_dimes(cents);
  cents = cents - dimes * 10;

  // [my-comment] Same logic but for nickels
  int nickels = calculate_nickels(cents);
  cents = cents - nickels * 5;

  // [my-comment] Same logic but for pennies
  int pennies = calculate_pennies(cents);
  cents = cents - pennies * 1;


  int coins = quarters + dimes + nickels + pennies;

  printf("%i\n", coins);
}


// Business Logic Functions
int get_cents(void) {
  int cents;
  do {
    cents = get_int("Change owed (cents): ");
  } while (cents < 0);

  cents = adjust_cents_to_last_2_digits(cents);

  return cents;
}


int adjust_cents_to_last_2_digits(int cents) {
  int cents_length = get_int_length(cents);
  
  if (cents_length <= 2) return cents;

  int denominator_to_remove_non_cents = pow(10, cents_length - 1);
  
  cents = cents % denominator_to_remove_non_cents;
  
  return adjust_cents_to_last_2_digits(cents);
}


int calculate_quarters(int cents) {
  return cents / 25; // int division
}

int calculate_dimes(int cents) {
  return cents / 10; // int division
}

int calculate_nickels(int cents) {
  return cents / 5; // int division
}

int calculate_pennies(int cents) {
  return cents / 1; // int division
}

// Utils
int get_int_length(int integer) {
  int length = 0;
  while (integer != 0) {
      integer = integer / 10; // int division
      length++;
  }

  return length;
}
