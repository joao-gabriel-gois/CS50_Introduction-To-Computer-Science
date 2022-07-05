#include <stdio.h>
#include <stdlib.h>

int get_str_length(char* str);
void my_strcpy(char* str1, char* str2);
void my_toupper(char* str);


int main(void) {
  // string s actually saves the
  // first char index, so both
  // printfs bellow will show
  // same pointer address
  char* s = "Hi, babe, what's up?!";
  int i[] = {3, 2, 1};
  char* p = &s[0];

  int* pi = &i[0];
  char* sCpy = malloc((get_str_length(s) + 1) * sizeof(char));

  my_strcpy(sCpy, s);

  my_toupper(sCpy);

  printf("\nstrcpy and toupper tests\ns: %s | sCpy: %s\n", s, sCpy);
  free(sCpy);

  printf("\nBoth s and p adresses (the same):\n");
  printf("%p\n", p);
  printf("%p\n", s);

  // using * as deference opereator to
  // get value inside pointer
  printf("\nGetting value deferrnig from s pointer (char*), first 3 elements:\n");
  printf("%c", *s);
  // we can add and compiler knows
  // the type size to get right value
  printf("%c", *(s + 1));
  printf("%c\n", *(p + 2));

  printf("\nDeferring int array values from pointer of first element\n");
  printf("%i", *pi);
  printf("%i", *(pi + 1));
  printf("%i\n", *(pi + 2));

  printf("\nDefferring int array values from array itself (which returns first element like a string):\n");
  printf("%i", *i);
  printf("%i", *(i + 1));
  printf("%i\n", *(i + 2));
  printf("\n");
  return 0;
}

void my_strcpy(char* str1, char* str2) {
  int i = 0;
  while (*(str2 + i) != '\0') {
    str1[i] = *(str2 + i);
    i++;
  }
  str1[i] = '\0';
}

void my_toupper(char* str) {
  int i = 0;
  while (*(str + i) != '\0') {
    if ((int) str[i] > 96 && (int) str[i] < 123) {
      char c = *(str + i) - 32;
      // above line is same as bellow
      //char c = str[i] - 32;
      str[i] = c;
    }
    i++;
  }
}

int get_str_length(char* str) { 
  int i = 0;
  while (*(str + i) != '\0') {
    i++;
  }
  return i;
}
