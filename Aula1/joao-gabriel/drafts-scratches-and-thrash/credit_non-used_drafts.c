int power_pudou(int base, int power) {
  int value = base;
  for (int i = 0; i < power; i++) {
    value = value * value;
  }

  return base;
}


bool algorithm_of_luhn(long int credit_card_number, int showing_digits) {
  // for static credit card number
  int power = CREDIT_CARD_LENGTH - showing_digits;
  double result = pow(10, power);
  
  //printf("Power: %f\n", power);
  long int digits = (float) credit_card_number / pow(10, power);
  printf("%li\n", digits);
  return true;
}