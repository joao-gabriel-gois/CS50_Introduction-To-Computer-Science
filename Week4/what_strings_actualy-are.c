#include <cs50.h>
#include <stdio.h>

typedef char* string;

/*
  Strings actually are an Array. But the var who stores it, is actually
  storing pointers to the first char of the string; When we use "", compiler
  knows you're creating an array, so it  automatically adds \0 (null char) as
  last character of this char array called string, and return the value of the
  adress of the first char. When you add 1 to a pointer of an array element,
  compiler knows you want to add the size of one element data type (char) to
  the current address, to end up pointing to next one (the [i + 1]).

  That's why you can not assign to a new variable a previous declared string.
  Cause it will stores not the value itself, but the very same address of the
  same first array's element. 
*/

int main(void) {
  char* string1 = "Hi!";
  string string2 = "Hi!";

  printf(
    "\n%s, from string1 of\n"
  );

  printf(
    "\n%s, from string2 of\n"
  );

}
