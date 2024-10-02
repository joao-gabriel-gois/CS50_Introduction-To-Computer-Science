#include <stdio.h>
#include <stdlib.h>

// CUSTOM TYPES
typedef int bool;

const bool false = 0;
const bool true = 1;
const char *bool_enum[] = {"false", "true"};

typedef struct node
{
  int number;
  struct node *next;
  struct node *prev;
} node;

// "METHODS" headers
node *create(int number);
void insert(node **list, int number);

// We need to pass the list for mutable version, not elegant
bool delete_element(node **list, node *element);
// bool delete_all(node** list, int number);
node *find(node *list, int number);
void destroy(node *list);
void print_list(node *list);

int main(void)
{
  node *list1 = create(15);
  node *list2 = create(7);

  // Filling
  for (int i = 0; i < 9; i++)
  {
    insert(&list1, i);
  }
  for (int i = 18; i > 0; i -= 2)
  {
    insert(&list2, i);
  }

  // Showing
  printf("\033[05;35m\nBefore changes: \033[m\n");
  printf("List 1");
  print_list(list1);
  printf("List 2");
  print_list(list2);

  // Modifying

  // Modifying
  node *eight_to_delete = find(list1, 8);
  node *one_to_delete = find(list1, 1);
  node *not_found_93 = find(list1, 92);
  // printf("Founded-> %i | Address-> %p", one_to_delete->number,
  // one_to_delete); printf("NotFounde |Address-> %p", *not_found_93);

  bool removed11 = delete_element(&list1, eight_to_delete);
  bool removed12 = delete_element(&list1, one_to_delete);
  bool not_removed1 = delete_element(&list1, not_found_93);
  printf("\033[33mList 1 modification status: \033[m");
  printf("\033[03;30mNot removed (92): %s | Removed (8 & 1) %s && %s\033[m\n",
         bool_enum[not_removed1], bool_enum[removed12], bool_enum[removed12]);
  node *ten_to_delete = find(list2, 10);
  node *fourteen_to_delete = find(list2, 14);
  node *not_found_173 = find(list2, 173);

  bool removed21 = delete_element(&list2, ten_to_delete);
  bool removed22 = delete_element(&list2, fourteen_to_delete);
  bool not_removed2 = delete_element(&list2, not_found_173);

  printf("\033[33mList 2 modification status: \033[m");
  printf("\033[03;30mNot removed (173): %s | Removed (10) %s\033[m\n",
         bool_enum[not_removed2], bool_enum[removed21]);
  // Showing after changes
  printf("\033[05;36m\nAfter removing first matches for 8 and 1 in list1 and "
         "first matchs for 10 and 14 in list2: \033[m\n");
  printf("List 1");
  print_list(list1);
  printf("List 2");
  print_list(list2);

  // Searching
  char *found = "\033[01;32mfound!\033[m";
  char *not_found = "\033[01;31mnot found!\033[m";
  printf("- Searching 5 in list 1, and it was %s",
         find(list1, 5) != NULL ? found : not_found);
  printf("\n- Searching 8 in list 1, and it was %s",
         find(list1, 8) != NULL ? found : not_found);
  printf("\n- Searching 14 in list 2, and it was %s",
         find(list2, 14) != NULL ? found : not_found);
  printf("\n- Searching 8 in list 2, and it was %s\n",
         find(list2, 8) != NULL ? found : not_found);

  destroy(list1);
  destroy(list2);

  printf("\nEND\n");
  return 0;
}

node *create(int number)
{
  node *list = malloc(sizeof(node));
  list->number = number;
  list->next = NULL;
  list->prev = NULL;

  return list;
}

void insert(node **list, int number)
{
  node *new_element = create(number);

  (*list)->prev = new_element;
  new_element->next = *list;

  *list = new_element;
}

node *find(node *list, int number)
{
  node *tmp = list;
  while (tmp != NULL)
  {
    if (tmp->number == number)
    {
      return tmp;
    }
    tmp = tmp->next;
  }

  return NULL;
}

// I only could finish it by adding also a pointer to list to fix this for first element, for a mutable version
bool delete_element(node **list, node *element)
{
  if (element == NULL)
    return false;
  else if (element->prev == NULL && element->next == NULL)
  {
    free(element);
    return true;
  }

  if (element->next != NULL)
  {
    element->next->prev = element->prev;
  }
  if (element->prev != NULL)
  {
    element->prev->next = element->next;
  }
  else
  {
    *list = element->next;
  }

  free(element);
  return true;
}

bool delete_all(node **list, int number)
{
  node *found_element = find(*list, number);
  bool deleted = delete_element(list, found_element);
  found_element = find(*list, number);
  if (found_element != NULL)
    delete_all(list, number);
  return deleted;
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
    list = list->next;
    if (list != NULL)
      printf(",");
    printf(" ");
  }
  printf("]\033[m\n\n");
}
