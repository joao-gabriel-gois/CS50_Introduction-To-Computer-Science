def main():
    number = input('Number: ')
    brand = get_credit_card_brand(number)
    print(brand)


def check_numeral_size_and_adjust(value):
    value_int_div = value // 10
    value_int_mod = value % 10

    return (value_int_div + value_int_mod) if value_int_div >= 1 else value


def calculate_luhn_and_check(credit_card):
    is_credit_card_length_even = len(credit_card) % 2 == 0
    result1 = 0
    result2 = 0
    for i, number_str in enumerate(credit_card):
        current = int(number_str)
        needs_to_double = (
            i % 2 == 0 and is_credit_card_length_even
          ) or (
            i % 2 != 0 and not is_credit_card_length_even
        )

        if (needs_to_double):
            doubled_current = current * 2
            result1 += check_numeral_size_and_adjust(doubled_current)
        else:
            result2 += current

    str_result = str(result1 + result2)
    last_digit = int(str_result[len(str_result) - 1])

    return last_digit == 0


def get_credit_card_brand(credit_card):
    # f2d stands for Frist 2 Digits
    f2d = str(credit_card)[:2]
    is_mastercard = (
        f2d == '51' or f2d == '52' or f2d == '53'
        or f2d == '54' or f2d == '55'
    ) and len(str(credit_card)) == 16

    is_amex = len(str(credit_card)) == 15 and (f2d == '34' or f2d == '37')

    is_visa = f2d[0] == '4' and (len(str(credit_card)) == 13 or len(str(credit_card)) == 16)

    if not calculate_luhn_and_check(credit_card):
        return 'INVALID'
    elif is_amex:
        return 'AMEX'
    elif is_mastercard:
        return 'MASTERCARD'
    elif is_visa:
        return 'VISA'

    return 'INVALID'


main()
