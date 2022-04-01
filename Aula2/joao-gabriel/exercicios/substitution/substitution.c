#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


void transform_plaintext_into_cipher(string plaintext, string key);
char get_char_cipher(char c, string key);
bool validate_key(string key);
bool is_letter(char c);


const int N_OF_AVAILABLE_CHARS = 26;


int main(int argc, string argv[]) {
  if (argc != 2) {
    printf("\033[01;33mUsage\033[m:\033[32m ./substitution key\033[m\n");
    return 1;
  }
  
  else if (strlen(argv[1]) != N_OF_AVAILABLE_CHARS) {
    printf("\033[01;33mKey must contain 26 characters.\033[m\n");
    return 1;
  }

  else if (!validate_key(argv[1])) {
    printf("\033[01;33mKey must contain only letters.\033[m\n");
    return 1;
  }

  string plaintext = get_string("plaintext:  ");

  transform_plaintext_into_cipher(plaintext, argv[1]);

  printf("ciphertext: %s\n", plaintext);

  return 0;
}

bool validate_key(string key) {
  int i = 0;
  int j = 0;
  while (key[i] != '\0') {
    j = 0;
    // checking one by one to see if it is a letter
    if (!is_letter(key[i])) return false;
    while (key[j] != '\0') {
      //checking each char against the whole string to
      //see if same char appears elsewhere in the string
      //(if there is any char in a diff pos, it will return false)
      if (key[i] == key[j] && i != j) return false;
      j++;
    }
    i++;
  }

  return true;
}

void transform_plaintext_into_cipher(string plaintext, string key) {
  int plaintext_length = strlen(plaintext);
  char ciphertext_tmp[plaintext_length];

  int i = 0;
  while (plaintext[i] != '\0') {
    ciphertext_tmp[i] = get_char_cipher(plaintext[i], key);
    i++;
  }
  ciphertext_tmp[i] = '\0';

  strcpy(plaintext, ciphertext_tmp);
}


char get_char_cipher(char c, string key) {
  bool is_char_lower = islower(c);
  int delta_to_index = is_char_lower ? 'a' : 'A';
  
  int char_index_in_key_string = is_letter(c) ? c - delta_to_index : -1;

  if (char_index_in_key_string == -1) return c;

  char returned_char = key[char_index_in_key_string];

  return (
    is_char_lower ?
      tolower(returned_char)
      : toupper(returned_char)
  );
}


bool is_letter(char c) {
  char c_lower = tolower(c);

  return islower(c_lower);
}
