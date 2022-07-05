#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Business Logic Functions
int calculate_coleman_liau_grade(string text);
void validate_and_handle_output(int grade);
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
// Utils
bool is_letter(char c);


int main(void) {
  string text = get_string("Text: ");
  int grade = calculate_coleman_liau_grade(text);

  validate_and_handle_output(grade);
}



int calculate_coleman_liau_grade(string text) {
  int words_length = count_words(text);

  float L = (float) count_letters(text) / words_length * 100;
  float S = (float) count_sentences(text) / words_length * 100;

  float index = 0.0588 * L - 0.296 * S - 15.8;

  return round(index);
}


void validate_and_handle_output(int grade)
{
    if (grade < 1) printf("Before Grade 1\n");
    else if (grade > 16) printf("Grade 16+\n");
    else printf("Grade %i\n", grade);
}


int count_letters(string text) {
  int counter = 0;
  int text_length = strlen(text);

  for (int i = 0; i < text_length; i++) {
    if (is_letter(text[i])) counter++;
  }

  return counter;
}


int count_words(string text) {
  int text_length = strlen(text);
  int counter = 0;

  for (int i = 0; i < text_length; i++) {
    bool is_previous_a_space = i > 0 && text[i - 1] == ' ';
    bool is_next_a_letter = i < text_length - 1 && is_letter(text[i + 1]);
    bool is_current_not_a_space = text[i] != ' ';

    if (is_letter(text[i]) && is_previous_a_space) counter++;
    else if (
      is_previous_a_space && is_current_not_a_space
      && !is_letter(text[i]) && is_next_a_letter 
    ) counter++; 
  
  }

  return counter + 1; // first word will be ignored because it will not have a space before it
}


int count_sentences(string text) {
  int counter = 0;
  int text_length = strlen(text);
  
  for (int i = 0; i < text_length; i++) {   
    bool is_sentence_end_marker = (
      text[i] == '!' || text[i] == '?' || text[i] == '.'
    ) ? 1 : 0;

    bool is_previous_char_letter = i > 0 && is_letter(text[i - 1]);

    if (
      is_sentence_end_marker && is_previous_char_letter
    ) counter++;

  }
    
  return counter;
}

// Utils
bool is_letter(char c) {   
  char c_lower = tolower(c);

  return islower(c_lower);
}
