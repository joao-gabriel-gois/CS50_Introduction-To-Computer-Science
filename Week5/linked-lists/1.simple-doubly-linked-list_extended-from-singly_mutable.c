// Before taking the doubly-linked list class
// I've tried to create one and it worked, but this
// data structure still pointless once it has the
// same workaround for removing as singly-linked lists
// and still handling everything only in one direction

// It is an extension of the mutable singled link list
// Doesn't uses the previous reference but correctly assignes it
// (Uncomment excerpt inside print_list to check both next and previous counters)

// There is only mutable version for it
#include <stdio.h>
#include <stdlib.h>

// CUSTOM TYPES
typedef int bool;

#define false 0
#define true !false
const char *bool_enum[] = {"false", "true"};

typedef struct node
{
  int number;
  struct node *next;
  struct node *previous;
} node;

// "METHODS" headers
node *create(int number);
void insert(node **list, int number);
int remove_first(node **list, int number);
// remove_last pending
// remove_all breaking after changes for doobly linked lists
int remove_all(node **list, int number);
bool find(node *list, int number);
void destroy(node *list);
void print_list(node *list);

// DEMO
int main(void)
{
  // Creating
  node *list1 = create(1);
  node *list2 = create(10);

  // Filling
  for (int i = 0; i < 9; i++)
    insert(&list1, i);
  for (int i = 18; i > 0; i -= 2)
    insert(&list2, i);

  // Showing
  printf("\033[05;35m\nBefore changes: \033[m\n");
  printf("List 1");
  print_list(list1);
  printf("List 2");
  print_list(list2);

  // Modifying
  bool removed11 = remove_first(&list1, 8);
  bool removed12 = remove_first(&list1, 1);
  bool not_removed1 = remove_first(&list1, 92);
  printf("\033[33mList 1 modification status: \033[m");
  printf(
      "\033[03;30mNot removed (92): %s | Removed (8) %s\033[m\n",
      bool_enum[not_removed1], bool_enum[removed11]);

  bool removed21 = remove_first(&list2, 10);
  bool removed22 = remove_first(&list2, 14);
  bool not_removed2 = remove_first(&list2, 173);
  printf("\033[33mList 2 modification status: \033[m");
  printf(
      "\033[03;30mNot removed (173): %s | Removed (10) %s\033[m\n",
      bool_enum[not_removed2], bool_enum[removed21]);

  // Showing after changes
  printf("\033[05;36m\nAfter removing first matches for 8 and 1 in list1 and first matchs for 10 and 14 in list2: \033[m\n");
  printf("List 1");
  print_list(list1);
  printf("List 2");
  print_list(list2);

  // Searching
  char *found = "\033[01;32mfound!\033[m";
  char *not_found = "\033[01;31mnot found!\033[m";
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

  insert(&list1, 1);
  insert(&list1, 1);
  insert(&list2, 2);
  insert(&list2, 2);

  printf("\033[05;34m\nAfter inserting/before removing: \033[m\n");
  printf("List 1");
  print_list(list1);
  printf("List 2");
  print_list(list2);

  bool removed13 = remove_all(&list1, 1);
  bool not_removed3 = remove_all(&list1, 92);
  printf("\033[33mList 1 modification status: \033[m");
  printf(
      "\033[03;30mNot removed (92): %s | Removed (1) %s\033[m\n",
      bool_enum[not_removed3], bool_enum[removed13]);

  bool removed23 = remove_all(&list2, 2);
  ;
  bool not_removed4 = remove_all(&list2, 173);
  printf("\033[33mList 2 modification status: \033[m");
  printf(
      "\033[03;30mNot removed (173): %s | Removed (2) %s\033[m\n",
      bool_enum[not_removed4], bool_enum[removed23]);

  printf("\033[05;36m\nAfter removing all 1's in list1 and all 2's in list2: \033[m\n");
  printf("List 1");
  print_list(list1);
  printf("List 2");
  print_list(list2);

  // Destroying
  destroy(list1);
  destroy(list2);

  return 0;
}

// "METHODS" implementation
node *create(int number)
{
  node *list = malloc(sizeof(node));
  list->number = number;
  list->next = NULL;
  list->previous = NULL;

  return list;
}

bool find(node *list, int number)
{
  while (list != NULL)
  {
    if (list->number == number)
      return true;
    list = list->next;
  }

  return false;
}

void insert(node **list, int number)
{
  node *new_item = create(number);

  (*list)->previous = new_item;
  new_item->next = *list;

  *list = new_item;
}

bool remove_first(node **list, int number)
{
  if (*list == NULL)
    return false; // with semicolon it breaks with " ‘else’ without a previous ‘if’"
  else if ((*list)->number == number)
  {
    // getting node* *list value, that is, the address stored in it pointing to a node
    node *tmp = *list;

    // assigning it new value that is a pointer to next node, but
    //   it still having same address itself where it will store
    //   this new pointer value, so node before it still correctly set

    if (tmp->next != NULL)
      tmp->next->previous = tmp->previous;
    *list = tmp->next;

    // cleaning removed node memory
    free(tmp);

    return true;
  }
  // else check next
  remove_first(&(*list)->next, number);
}

// Criar função remove_last, checando se a volta está ok para exemplos mais pertinentes a doubly linked list

// Consertar a função abaixo que está com falha de segmentação

bool remove_all(node **list, int number)
{
  bool removed = remove_first(list, number);
  bool has_remaining_elements = find(*list, number);
  // printf(">>[%p] - Removed %s | Remaining? %s\n", list, bool_enum[removed], bool_enum[has_remaining_elements]);
  if (!removed && !has_remaining_elements)
    return false;
  else if (!has_remaining_elements)
    return true;

  remove_all(list, number);
}

void destroy(node *list)
{
  if (list->next == NULL)
    return;
  destroy(list->next);
  // printf("free(&temp), where *temp = %i\n", list->number);
  free(list);
}

void print_list(node *list)
{
  printf("\n\033[01m [ ");
  while (list != NULL)
  {
    printf("%i", list->number);
    // (*) Uncomment code bellow to check correct double pointers
    // if (list->previous != NULL)
    //   printf(" (p>%i)", list->previous->number);
    // if (list->next != NULL)
    //   printf(" (n>%i)", list->next->number);

    list = list->next;
    if (list != NULL)
      printf(",");
    printf(" ");
  }
  printf("]\033[m\n\n");
}
