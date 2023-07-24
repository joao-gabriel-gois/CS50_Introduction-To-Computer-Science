#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false !true

typedef struct DoubleLinkedList {
  char value[20];
  struct DoubleLinkedList* next;
  struct DoubleLinkedList* prev;
} DoubleLinkedList;

#define HASH_MAX 10
typedef DoubleLinkedList* HashTable[HASH_MAX];


unsigned int hash(char* str);

HashTable* create();
int append(HashTable hash_table, char *str); // insert in the end of the hashed index
int head(HashTable hash_table, char *str); // insert in the beggining of the hashed index
DoubleLinkedList* find(HashTable hash_table, char* str);
bool remove_node(HashTable hash_table, char *str);
void print_hash_table(HashTable hash_table);
bool destroy(HashTable* hash_table);


int main() {
  printf("\033[01;02mHash Table before:\033[m ");
  HashTable* ht = create();
  print_hash_table(*ht);

  printf(
      "\n\n\033[01;32mAppending in the hashed list:\033[02m\n\tWissen (%i), Schaft (%i), 2x Teste 9 (%i),",
      hash("Wissen"), hash("Schaft"), hash("Teste 9")
  );
  printf(
      "Teste 12 (%i), Vai Corinthians (%i), Testy (%i), Wissen (%i) and, finally, Test (%i).\033[m\n",
      hash("Teste 12"), hash("Vai Corinthians"), hash("Testy"), hash("Wissen"), hash("Test")
  );

  char* values_append[] = {
    "Wissen",  "Schaft","Teste 9",
    "Teste 9","Teste 12","Vai Corinthians", 
    "Testy", "Wissen", "Test"
  };
  for (int i = 0; i < 9; i++) append(*ht, values_append[i]);
  
  printf("\033[01;32mAfter appending: \033[m");
  print_hash_table(*ht);


  printf("\n\n\033[01;31mRemoving:\033[02m\n\tTeste 9, Teste 12, Testy e Test!\033[m\n");
  remove_node(*ht, "Teste 9");
  remove_node(*ht, "Teste 12");
  bool check = remove_node(*ht, "Testy");
  bool check2 = remove_node(*ht, "Test");
  // printf(
  //   "\n\nWas Testy removed? %s | Was Test removed? %s\n",
  //   check == 1 ? "\033[32mYes!\033[m" : "\033[31mNo!\033[m",
  //   check2 == 1 ? "\033[32mYes!\033[m" : "\033[32mNo!\033[m"
  // );
  printf("\033[01;31mAfter removing: \033[m");
  print_hash_table(*ht);

  
  printf("\n\n\033[01;33mAdding in the hashed list head:\033[02m\n\t");
  printf(
    "Testy (%i), Test (%i), Talk is cheap (%i), Show me the code (%i).\033[m\n",
    hash("Testy"), hash("Test"), hash("Talk is cheap"), hash("Show me the code")
  );

  char* values_head[] = {
    "Testy", "Test",
    "Talk is cheap", "Show me the code"
  };
  for (int i = 0; i < 4; i++) head(*ht, values_head[i]);
  
  printf("\033[01;33mAfter adding in the head of the hashed index: \033[m");
  print_hash_table(*ht);


  destroy(ht);
  return 0;
}

// Hash Table "methods"
unsigned int hash(char *str) {
  int char_code_sum = 0;
  int counter = 0;
  for (; str[counter] != '\0'; counter++) {
    // int weight = counter + 1; // making char order relevant for diff hash
    char_code_sum = str[counter]; // * weight; // It was removed in order to keep better add/remove example
  }

  return (char_code_sum + counter + 1) % HASH_MAX; // making string lenght relevant for diff hash
}

HashTable* create() {
  HashTable* ht = malloc(HASH_MAX * sizeof(DoubleLinkedList*));
  for (int i = 0; i < HASH_MAX; i++)  *ht[i] = NULL;
  return ht;
}

int append(HashTable hash_table, char *str) {
  int index = hash(str);
  DoubleLinkedList *element = malloc(sizeof(DoubleLinkedList));
  strcpy(element->value, str);
  element->next = NULL;
  element->prev = NULL;

  DoubleLinkedList *current = hash_table[index];
  if (current == NULL)
    hash_table[index] = element;
  else {
    while (current->next != NULL) {
      current = current->next;
    }
    element->prev = current;
    current->next = element;
  }

  return index;
}

// If addition order doesn't matters, we can use only head with a singly linked lists
int head(HashTable hash_table, char *str) {
  int index = hash(str);
  DoubleLinkedList* element = malloc(sizeof(DoubleLinkedList));
  strcpy(element->value, str);
  element->prev = NULL;

  DoubleLinkedList* list_head = hash_table[index];
  if (list_head != NULL)
    list_head->prev = element;
  element->next = list_head;

  hash_table[index] = element;
  
  return index;
}

DoubleLinkedList* find(HashTable hash_table, char* str) {
  int index = hash(str);
  DoubleLinkedList* found = hash_table[index];

  while (found != NULL) {
    if (strcmp(found->value, str) == 0) 
      return found;
    found = found->next;
  }
  return NULL;
}

bool remove_node(HashTable hash_table, char* str) {
  DoubleLinkedList* found = find(hash_table, str);
  if (found == NULL)
    return false;
  // DoubleLinkedList *tmp = found;
  if (found->next != NULL)
    found->next->prev = found->prev;
  if (found->prev != NULL)
    found->prev->next = found->next;
  else
    hash_table[hash(str)] = found->next;

  free(found);
  return true;
}

void print_hash_table(HashTable hash_table) {
  printf("[\n");
  for (int i = 0; i < HASH_MAX; i++) {
    printf("\t");
    if (hash_table[i] == NULL) printf("\033[03m\033[02;34mNULL\033[m,\n");
    else {
      DoubleLinkedList *current = hash_table[i];
      while (current != NULL) {
        printf("%s", current->value);
        current = current->next;
        if (current == NULL) printf(",\n");
        else printf(" <-> ");
      }
    }
  }
  printf("];\n");
}

bool destroy(HashTable* hash_table) {
  for (int i = 0; i < HASH_MAX; i++) {
    DoubleLinkedList* current = (*hash_table)[i];
    DoubleLinkedList* tmp = current;
    while (current != NULL) {
      free(current->prev);
      tmp = current; // tmp stores possible lost prev for last iteration
      current = tmp->next;
    }
    free(tmp);
  }
  free(hash_table);
}
