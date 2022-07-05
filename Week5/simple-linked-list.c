#include <stdio.h>
#include <stdlib.h>

// CUSTOM TYPES
typedef int bool;

const int false = 0;
const int true = 1;
const char* bool_enum[] = { "false", "true" };

typedef struct node {
  int number;
  struct node* next;
} node;

// "METHODS" headers
node* create(int number);
bool find(node* list, int number);
node* insert(node* list, int number);
bool removeFirst(node** list, int number);
void destroy(node* list);
void print_list(node* list);

// DEMO
int main(void) {
  // Creating
  node* list1 = create(1);
  node* list2 = create(10);

  // Filling
  for (int i = 0; i < 9; i++) list1 = insert(list1, i);
  for (int i = 18; i > 0; i -= 2) list2 = insert(list2, i);

  // Showing
  printf("\033[05;35m\nBefore changes: \033[m\n");
  printf("List 1");
  print_list(list1);
  printf("List 2");
  print_list(list2);

  // Modifying
  bool removed11 = removeFirst(&list1, 8);
  bool removed12 = removeFirst(&list1, 1);
  bool not_removed1 = removeFirst(&list1, 92);
  printf("\033[34mList 1 modification status: \033[m");
  printf(
    "\033[03;30mNot removed (92): %s | Removed (8) %s\033[m\n",
    bool_enum[not_removed1], bool_enum[removed11]
  );
  
  bool removed21 = removeFirst(&list2, 10);
  bool removed22 = removeFirst(&list2, 14);
  bool not_removed2 = removeFirst(&list2, 173);
  printf("\033[34mList 2 modification status: \033[m");
  printf(
    "\033[03;30mNot removed (173): %s | Removed (10) %s\033[m\n",
    bool_enum[not_removed2], bool_enum[removed21]
  );

  // Showing after changes
  printf("\033[05;36m\nAfter changes: \033[m\n");
  printf("List 1");
  print_list(list1);
  printf("List 2");
  print_list(list2);

  // Searching
  char* found = "\033[01;32mfound!\033[m";
  char* not_found = "\033[01;31mnot found!\033[m";  
  printf("\n- Searching 5 in list 1, and it was %s", find(list1, 5) ? found : not_found);
  printf("\n- Searching 8 in list 1, and it was %s", find(list1, 8) ? found : not_found);
  printf("\n- Searching 14 in list 2, and it was %s", find(list2, 14) ? found : not_found);
  printf("\n- Searching 8 in list 2, and it was %s\n", find(list2, 8) ? found : not_found);

  //Destroying
  destroy(list1);
  destroy(list2);

  return 0;
}

// "METHODS" implementation
node* create(int number) {
  node* list = malloc(sizeof(node));
  list->number = number;
  list->next = NULL;

  return list;
}

bool find(node* list, int number) {
  while (list->next != NULL) {
    if (list->number == number) return true;
    list = list->next;
  }
  return false;
}

node* insert(node* list, int number) {
  node* new_item = malloc(sizeof(node));
  new_item->number = number;
  new_item->next = list;

  return new_item;
}

bool removeFirst(node** list, int number) {
  if (*list != NULL && (*list)->number == number) {
    node* tmp = *list;
    *list = tmp->next;
    free(tmp);
  
    return true;
  }
  else if ((*list)->next != NULL && (*list)->next->number == number) {
    node* tmp = (*list)->next;
    (*list)->next = tmp->next;
    free(tmp);
    return true;
  }
  else if ((*list)->next == NULL) return false;

  removeFirst(&(*list)->next, number);
}

void destroy(node* list) {
  if (list->next != NULL) return;
  destroy(list->next);
  //printf("free(&temp), where *temp = %i\n", list->number);
  free(list);
}

void print_list(node* list) {
  node* last_item = list; 
  printf("\n\033[01m [ ");
  while (last_item != NULL) {
    printf("%i", last_item->number);
    last_item = last_item->next;
    if (last_item != NULL) printf(",");
    printf(" ");
  }
  printf("]\033[m\n\n");
}
