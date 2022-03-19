#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Utils
int get_first_2_digits(long int credit_card_number);
int get_last_digit(int luhn_step_two_result);
// string return_bool_as_string(bool boolean);
int get_long_length(long int number);
string convert_long_to_string(long int long_int);

// Business logic functions
bool check_with_algorithm_of_luhn(long int credit_card_number);
string get_credit_card_brand(long int credit_card_number);
int luhn_calculate(long int credit_card_number);
int check_numeral_size_and_adjust(int value);



void main(void) {
  long int credit_card_number = get_long("Insert your credit card number: "); 
  bool is_credit_card_valid = check_with_algorithm_of_luhn(credit_card_number);

  printf("Number: %li\n", credit_card_number);
  
  if (!is_credit_card_valid) {
    printf("INVALID\n");
    return;
  }

  string credit_card_brand = get_credit_card_brand(credit_card_number);
  
  printf("%s", credit_card_brand);
}



// Business Logic Functions
string get_credit_card_brand(long int credit_card_number) {
  int first_2_digits = get_first_2_digits(credit_card_number);
  string str_first_2_digits = convert_long_to_string(first_2_digits);

  if (first_2_digits == 34 || first_2_digits == 37) return "AMEX\n";
  
  else if (
    first_2_digits == 51 || first_2_digits == 52
    || first_2_digits == 53 ||
    first_2_digits == 54 || first_2_digits == 55
  ) return "MASTERCARD\n";

  else if (str_first_2_digits[0] == '4') return "VISA\n";

  return "\033[01;31mERROR: \033[00;33mSomehow you have a valid card but it is not AMEX, MASTERCARD or VISA\n\033[m";
}


bool check_with_algorithm_of_luhn(long int credit_card_number) {
  int luhn_result = luhn_calculate(credit_card_number);
  int last_digit = get_last_digit(luhn_result);

  return last_digit == 0;
}


int luhn_calculate(long int credit_card_number) {
  string str_credit_card_number = convert_long_to_string(credit_card_number);

  int result1 = 0;
  int result2 = 0;

  int credit_card_number_length = strlen(str_credit_card_number);
  for (int i = 0; i < credit_card_number_length; i++) {
    if (i % 2 == 0) {
      int current = str_credit_card_number[i] - '0';

      int doubled_current = current * 2;

      doubled_current = check_numeral_size_and_adjust(doubled_current);
      
      result1 = result1 + doubled_current;
    }
    else {
      int current = str_credit_card_number[i] - '0';

      current = check_numeral_size_and_adjust(current);
      
      result2 = result2 + current;
    }
  }

  return result1 + result2;
}


int check_numeral_size_and_adjust(int value) {
  int result;

  int value_int_div = value / 10;
  int value_int_mod = value % 10;

  result = value_int_div >= 1 ? value_int_div + value_int_mod : value;

  return result;
}


// Utils
int get_first_2_digits(long int credit_card_number) {
  int credit_card_number_length = get_long_length(credit_card_number);
  int power_to_10_to_remain_2_digs = credit_card_number_length - 2;
  long int denominator_to_remain_2_digs = pow(10, power_to_10_to_remain_2_digs);

  return  credit_card_number / denominator_to_remain_2_digs; // int division
}


int get_last_digit(int luhn_step_two_result) {
  return luhn_step_two_result % 10;
}


int get_long_length(long int number) {
  int length = 0;
  long int long_int_remaining_number = number;

  while (long_int_remaining_number != 0) {
    long_int_remaining_number = long_int_remaining_number / 10;
    length++;
  } 

  return length;
}


string convert_long_to_string(long int long_int) {
  int credit_card_number_length = get_long_length(long_int);

  char *str_to_ret = malloc (sizeof (char) * credit_card_number_length);

  char str[credit_card_number_length];
  sprintf(str, "%li", long_int);
  
  str_to_ret = str;

  return str_to_ret;
}


// string return_bool_as_string(bool boolean) {
//   if (boolean == 0) {
//     return "false";
//   }

//   return "true";
// }
