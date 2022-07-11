#include <stdio.h>
#include <stdlib.h>

// CUSTOM TYPES
typedef int bool;
#define false 0;
#define true !false;

typedef struct node {
  int number;
  struct node* next;
} node;

// "METHODS" headers
node* create(int number);
node* insert(node* list, int number);
node* remove_first(node* list, int number);
node* remove_all(node* list, int number);
bool find(node* list, int number);
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
  list1 = remove_all(list1, 8);
  list1 = remove_all(list1, 1);
  list1 = remove_all(list1, 1123);
  
  list2 = remove_all(list2, 10);
  list2 = remove_all(list2, 14);
  list2 = remove_all(list2, 173);

  // Showing after changes
  printf("\033[05;36m\nAfter removing all 8's and 1's in list1 and 10's and 14's in list2: \033[m\n");
  printf("List 1");
  print_list(list1);
  printf("List 2");
  print_list(list2);

  // Searching
  char* found = "\033[01;32mfound!\033[m";
  char* not_found = "\033[01;31mnot found!\033[m";  
  printf("- Searching 5 in list 1, and it was %s", find(list1, 5) ? found : not_found);
  printf("\n- Searching 8 in list 1, and it was %s", find(list1, 8) ? found : not_found);
  printf("\n- Searching 14 in list 2, and it was %s", find(list2, 14) ? found : not_found);
  printf("\n- Searching 8 in list 2, and it was %s\n", find(list2, 8) ? found : not_found);

  // (Showing - Modifying - showing) again
  printf("\033[05;35m\nBefore inserting: \033[m\n");
  printf("List 1");
  print_list(list1);
  printf("List 2");
  print_list(list2);

  list1 = insert(list1, 12);
  list1 = insert(list1, 18);
  list1 = insert(list1, 31);
  list2 = insert(list2, 13);
  list2 = insert(list2, 16);
  list2 = insert(list2, 69);

  printf("\033[05;34m\nAfter inserting/before removing: \033[m\n");
  printf("List 1");
  print_list(list1);
  printf("List 2");
  print_list(list2);

  list1 = remove_first(list1, 31);
  list1 = remove_first(list1, 0);
  list1 = remove_first(list1, 1123);
  
  list2 = remove_first(list2, 16);
  list2 = remove_first(list2, 2);
  list2 = remove_first(list2, 173);

  printf("\033[05;36m\nAfter removing first and last elements of list1 and first match for 2 and 16 in list2: \033[m\n");
  printf("List 1");
  print_list(list1);
  printf("List 2");
  print_list(list2);


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
  while (list != NULL) {
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


node* remove_all(node* list, int number) {
  node* list_head = list;
  node* new_list = malloc(sizeof(node));
  node* new_list_head = new_list;
  
  while (list != NULL) {
    if (list->number != number) {
      bool should_not_alloc_for_next = list->next != NULL
        ? list->next->number == number && list->next->next == NULL
        : true;

      new_list->number = list->number;
      new_list->next = should_not_alloc_for_next ? NULL : malloc(sizeof(node));
      
      new_list = new_list->next;
    }
    
    list = list->next;
  }
  
  destroy(list_head);

  return new_list_head;
}


node* remove_first(node* list, int number) {
  node* list_head = list;
  node* new_list = malloc(sizeof(node));
  node* new_list_head = new_list;
  bool skipped = false;
  
  while (list != NULL) {
    if (list->number != number || skipped) {
      bool should_not_alloc_for_next = list->next != NULL
        ? list->next->number == number && list->next->next == NULL
        : true;

      new_list->number = list->number;
      new_list->next = should_not_alloc_for_next ? NULL : malloc(sizeof(node));
      
      new_list = new_list->next;
    }
    else skipped = true;
    
    list = list->next;
  }
  
  destroy(list_head);

  return new_list_head;
}



void destroy(node* list) {
  if (list->next == NULL) return;
  destroy(list->next);
  //printf("free(&temp), where *temp = %i\n", list->number);
  free(list);
}


void print_list(node* list) {
  printf("\n\033[01m [ ");
  while (list != NULL) {
    printf("%i", list->number);
    list = list->next;
    if (list != NULL) printf(",");
    printf(" ");
  }
  printf("]\033[m\n\n");
}
