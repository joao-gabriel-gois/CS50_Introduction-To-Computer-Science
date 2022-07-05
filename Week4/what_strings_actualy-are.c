#include <cs50.h>
#include <stdio.h>

typedef char* string;

/*
  Strings actually an Array. But the var who stores it, actually stores
  pointers to first char of the string; When we use "", compiler knows
  you're creating an array, adds \0 (null char) as last character you're
  automatically and returns as value the adress of first element. When you
  add 1 to a pointer of an array element, compiler knows you want to add the
  size of one element data type to previous address and return new address
  (the one with value equal [i + 1]).

  That's why you can not assign to a new variable a previous string.
  Cause it will stores not the value itself, but the very same address
  of the same first array element. That's why 
*/

int main(void) {
  char* string1 = "Hi!";
  string string2 = "Hi!";

  printf(
    "{\n%s:}, Value of\n"
  );

}
