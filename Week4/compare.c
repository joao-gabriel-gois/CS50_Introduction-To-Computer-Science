#include <stdio.h>
#include <cs50.h>

int get_str_length(char* str);
int my_strcmp(char* str1, char* str2);

int main(void) {
  int i = get_int("i: ");
  int j = get_int("j: ");

  if (i == j) {
    printf("IntValue -> Same\n");
  } else {
    printf("IntValue -> Different\n");
  }

  //CS50 use string as alias for char*
  // Like: typedef char* string
  string s = get_string("s: ");
  char* t = get_string("t: ");
  
  // comparing different pointer
  if (s == t) {
    printf("CharPointer -> Same\n");
  } else {
    printf("CharPointer -> Different\n");
  }

  int str_cmp = my_strcmp(s, t);
 
  if (str_cmp == 0) {
    printf("Deferred CharPointer Value -> Same\n");
  } else {
    printf("Deferred CharPointer Value -> Different, delta: %i\n", str_cmp);
  }
}

int my_strcmp(char* str1, char* str2) {
  int i = 0;
  bool remain_equal = true;
  int lengths_diff = get_str_length(str1) - get_str_length(str2);
  char* bigger = lengths_diff > 0 ? str1 : str2;

  while (remain_equal && *(bigger + i) != '\0') {
    remain_equal = remain_equal && (
      *(str1 + i) == *(str2 + i)
    );

    i++;
  }

  return remain_equal ? !remain_equal : 2 * (3 * lengths_diff - 2 * (get_str_length(bigger) - i)) / 3 - 1;
}

int get_str_length(char* str) { 
  int i = 0;
  while (*(str + i) != '\0') {
    i++;
  }
  return i;
}
