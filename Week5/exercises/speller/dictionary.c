#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node {
  char word[LENGTH + 1];
  struct node *next;
} node;
// Choose number of buckets in hash table
const unsigned int N = 40;
// Hash table
node *table[N];

// File line buffer
char line_buffer[LENGTH + 1];
// Utils
void free_linked_list(node *list);
void string_tolower(char *word);

// Returns true if word is in dictionary, else false
bool check(const char *word) {
    char lower_word[strlen(word)];
    strcpy(lower_word, word);
    for (int i = 0; lower_word[i] != '\0'; i++)
      lower_word[i] = tolower(lower_word[i]);

    int index = hash(word);
    node *current = table[index];
    while (current != NULL) {
      string_tolower(current->word);
      bool is_same = strcmp(current->word, lower_word) == 0;

      if (is_same) return true;
      current = current->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
  int char_code_sum = 0;
  int counter = 0;
  for (; word[counter] != '\0'; counter++) {
    int weight = counter + 1; // making char order relevant for diff hashes gen
    int current_char_code = tolower(word[counter]);
    char_code_sum += current_char_code * weight;
  }

  return (char_code_sum + counter + 1) % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
  // Not sure how to optmize this function, it is very slow right now
  for (int i = 0; i < N; i++)
    table[i] = NULL;

  FILE *infile = fopen(dictionary, "r");
  if (!infile) {
    printf("Error opening file!\n");
    return false;
  }

  while (fscanf(infile, "%s", line_buffer) == 1) {
    if (!check(line_buffer)) {
      int index = hash(line_buffer);
      node *word_node = malloc(sizeof(node));
      
      if (word_node != NULL) {
        strcpy(word_node->word, line_buffer);
        word_node->next = table[index];
        table[index] = word_node;
      }
    }
  }

  fclose(infile);
  return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
  int counter = 0;
  for (int i = 0; i < N; i++) {
    node *current = table[i];
    while (current != NULL) {
      counter++;
      current = current->next;
    }
  }

  return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
  for (int i = 0; i < N; i++) {
    node *list = table[i];
    free_linked_list(list);
  }

  return true;
}

// Utils
void free_linked_list(node *list) {
  if (list != NULL) {
    free_linked_list(list->next);
    free(list);
  }
}

void string_tolower(char *word) {
  for (int i = 0; word[i] != '\0'; i++)
    word[i] = tolower(word[i]); 
}
