#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Utils
int get_first_2_digits(long int credit_card_number);
int get_long_length(long int number);
string convert_long_to_string(long int long_int);
int get_last_digit_from_luhn_result(int luhn_result);
// Business logic functions
bool check_with_algorithm_of_luhn(long int credit_card_number);
string get_credit_card_brand(long int credit_card_number);
int luhn_calculate(long int credit_card_number);
int check_numeral_size_and_adjust(int value);



int main(void)
{
    long int credit_card_number = get_long("Insert your credit card number: ");

    string credit_card_brand = get_credit_card_brand(credit_card_number);

    printf("%s", credit_card_brand);

    return 0;
}



// Business Logic Functions
string get_credit_card_brand(long int credit_card_number) // [style50], JUST STOP, PEOPLE WILL START TO ADD ";" HERE!!!!
{
    bool is_credit_card_valid = check_with_algorithm_of_luhn(credit_card_number);
    if (!is_credit_card_valid)
    {
        return "INVALID\n";
    }

    int first_2_digits = get_first_2_digits(credit_card_number);
    int first_digit = first_2_digits / 10; // int division
    int credit_card_length = get_long_length(credit_card_number);

    bool digits_check_for_amex = first_2_digits == 34 || first_2_digits == 37;
    bool amex_condition = digits_check_for_amex && credit_card_length == 15;

    bool digits_check_for_mastercard = first_2_digits == 51 || first_2_digits == 52 || first_2_digits == 53
                                       || first_2_digits == 54 || first_2_digits == 55; // [style50] WTF!!?!??!
    bool mastercard_condition = digits_check_for_mastercard && credit_card_length == 16;

    bool digits_check_for_visa = first_digit == 4;
    bool visa_condition = digits_check_for_visa && (credit_card_length == 13 || credit_card_length == 16);

    if (amex_condition) // [style50], JUST STOP, PEOPLE WILL START TO ADD ";" HERE!!!!
    {
        return "AMEX\n";
    }
    else if (visa_condition) // [style50], JUST STOP, PEOPLE WILL START TO ADD ";" HERE!!!!
    {
        return "VISA\n";
    }
    else if (mastercard_condition) // [style50], JUST STOP, PEOPLE WILL START TO ADD ";" HERE!!!!
    {
        return "MASTERCARD\n";
    }

    // else
    return "INVALID\n";
}


bool check_with_algorithm_of_luhn(long int credit_card_number) // [style50],  JUST STOP, PEOPLE WILL START TO ADD ";" HERE!!!!
{
    int luhn_result = luhn_calculate(credit_card_number);
    int last_digit = get_last_digit_from_luhn_result(luhn_result);

    return last_digit == 0;
}


int luhn_calculate(long int credit_card_number)
{
    string str_credit_card_number = convert_long_to_string(credit_card_number);
    int result1 = 0;
    int result2 = 0;
    int credit_card_number_length = get_long_length(credit_card_number);
    bool is_credit_card_length_even = (credit_card_number_length) % 2 == 0;

    // printf("\tString converted card number: %s\n", str_credit_card_number);

    for (int i = 0; i < credit_card_number_length; i++)
    {
        // If credit card number lenght is even, so second to last
        //   index will be always even as well.  The same happens
        //   for odd credit card number cases.
        bool needs_to_double = ((i % 2 == 0) && is_credit_card_length_even) || ((i % 2 != 0) && !is_credit_card_length_even);

        int current = str_credit_card_number[i] - '0';
        // printf("\tCurrent char (iteration): %i\n", current);

        if (needs_to_double)
        {
            int doubled_current = current * 2;
            // If some how by multiplying by 2 some number somehow gets bigger
            //   than 10, it will sum both numerals instead of using directly the number
            doubled_current = check_numeral_size_and_adjust(doubled_current);
            result1 = result1 + doubled_current;
        }
        else
        {
            // If it is not doubling, no need to check numeral size
            result2 = result2 + current;
        }
    }

    free(str_credit_card_number);

    return result1 + result2;
}


int check_numeral_size_and_adjust(int value)
{
    int result;

    int value_int_div = value / 10;
    int value_int_mod = value % 10;

    result = value_int_div >= 1 ? value_int_div + value_int_mod : value;

    return result;
}


// Utils
int get_first_2_digits(long int credit_card_number)
{
    int credit_card_number_length = get_long_length(credit_card_number);
    int power_to_10_to_remain_2_digs = credit_card_number_length - 2;
    long int denominator_to_remain_2_digs = pow(10, power_to_10_to_remain_2_digs);

    return  credit_card_number / denominator_to_remain_2_digs; // int division
}


int get_last_digit_from_luhn_result(int luhn_result)
{
    return luhn_result % 10;
}


string convert_long_to_string(long int long_int) 
{
    int credit_card_number_length = get_long_length(long_int);
    string string_to_return = malloc(sizeof(char) * credit_card_number_length);
    sprintf(string_to_return, "%li", long_int);

    return string_to_return;
}


int get_long_length(long int number)
{
    int length = 0;
    long int long_int_remaining_number = number;

    while (long_int_remaining_number != 0)
    {
        long_int_remaining_number = long_int_remaining_number / 10;
        length++;
    }

    return length;
}
