#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


string get_caesar_ciphertext(string plaintext, int key);
int convert_positive_num_string_to_int(string s);

// strlen("abcde...z");
const int N_OF_AVAILABLE_CHARS = 26;


int main(int argc, string argv[]) {
  if (argc != 2) {
    printf("\033[01;33mUsage\033[m:\033[32m ./caesar key\033[m\n");
    return 1;
  }

  int int_argv1 = convert_positive_num_string_to_int(argv[1]);
  if (int_argv1 <= 0) {
    printf("\033[01;33mUsage\033[m:\033[32m ./caesar key\033[m\n");
    return 1;
  }


  string plaintext = get_string("plaintext: ");
  string ciphertext = get_caesar_ciphertext(plaintext, int_argv1);

  printf("ciphertext: %s\n", ciphertext);

  return 0;
}



string get_caesar_ciphertext(string plaintext, int key) {
  int plaintext_length = strlen(plaintext);
  char cipher[plaintext_length];

  // begin - block to create cipher and storage it in cipher string
  int i = 0;
  while (plaintext[i] != '\0') {
    if (islower(plaintext[i])) {
      char cipher_char = (plaintext[i] + key - 'a') % N_OF_AVAILABLE_CHARS + 'a';

      cipher[i] = cipher_char;
    }
    else if (isupper(plaintext[i])) {
     char cipher_char = (plaintext[i] + key - 'A') % N_OF_AVAILABLE_CHARS + 'A';

      cipher[i] = cipher_char;
    }
    else {
      cipher[i] = plaintext[i];
    }
    i++;
  }
  cipher[i] = '\0';
  // end - needs to add last element manually on cipher array to indicate its end


  string cipher_to_return = cipher;

  return cipher_to_return;
}


// Utils
int convert_positive_num_string_to_int(string s) {
  int string_length = strlen(s);

  int nums[string_length];
  for (int i = 0; i < string_length; i++) {
    // converting each char to num and adding to array
    // if its possible. If 1 char from string is not
    // able to become a number, whole func will return -1
    if (s[i] - '0' < 0 || s[i] -'0' > 9) return -1;
    nums[i] = s[i] - '0';
  } // After this point nums is one int array with all chars converted

  // Lets transform it in one whole int
  int result = 0;
  for (int i = 0; i < string_length; i++) {
    // applying sum for each array element, but multiplied by powers to 10 based on it's position
    // so in first loop of a 3 numeral array { 2, 3, 1}, in order to become the int 231, it is necessary
    // to multiply 2 by 100, 3 by 10 and 1 by 1 and then sum them. So in nums[0] where 2 is positioned,
    // It is need to multiply it by 10 ** (string_length - 1), the same but -2 to nums[1], then - 3,
    // until "string_length - n * (-1)" become 0, in the end of the loop.
    // This is exactly what is happening in last lines of code of this for loop.
    int power_to_reach_current_numeral = string_length - 1 - i;

    result += nums[i] * pow(10, power_to_reach_current_numeral);
  }

  return result;
}
