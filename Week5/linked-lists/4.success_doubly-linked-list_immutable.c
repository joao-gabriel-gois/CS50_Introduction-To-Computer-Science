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
node *insert(node *list, int number);

// We need to pass the list for mutable version, not elegant
node *delete_element(node *element);
node *delete_all(node *list, int number);
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
    list1 = insert(list1, i);
  }
  for (int i = 18; i > 0; i -= 2)
  {
    list2 = insert(list2, i);
  }

  // Showing
  printf("\033[05;35m\nBefore changes: \033[m\n");
  printf("List 1");
  print_list(list1);
  printf("List 2");
  print_list(list2);

  // Modifying

  // Modifying (right approach - check delete_element declaration)
  node *eight_to_delete = find(list1, 8);
  if (eight_to_delete != NULL)
  {
    list1 = delete_element(eight_to_delete);
  }
  node *one_to_delete = find(list1, 1);
  if (one_to_delete != NULL)
  {
    list1 = delete_element(one_to_delete);
  }
  node *not_found_93 = find(list1, 93);
  if (not_found_93 != NULL)
  {
    list1 = delete_element(not_found_93);
  }

  node *ten_to_delete = find(list2, 10);
  if (ten_to_delete != NULL)
  {
    list2 = delete_element(ten_to_delete);
  }
  node *fourteen_to_delete = find(list2, 14);
  if (fourteen_to_delete != NULL)
  {
    list2 = delete_element(fourteen_to_delete);
  }
  node *not_found_173 = find(list2, 173);
  if (not_found_173 != NULL)
  {
    list2 = delete_element(not_found_173);
  }

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

node *insert(node *list, int number)
{
  node *new_element = create(number);
  if (list != NULL)
  {
    list->prev = new_element;
  }
  new_element->next = list;

  return new_element;
}

node *find(node *list, int number)
{
  while (list != NULL)
  {
    if (list->number == number)
    {
      return list;
    }
    list = list->next;
  }

  return NULL;
}

node *find_head(node *element)
{
  if (element == NULL || element->prev == NULL)
    return element;
  find_head(element->prev);
}

node *delete_element(node *element)
{
  /**
    I prefered to not check on NULL otherwisenit would lose the
      reference of current list head. For a immutable solution,
      it should only return NULL if it really deleted last element
      and list element head is now really NULL, otherwise it should
      return an error. For this immutable approach, delete_element
      does not return if it was delete or not, but the list_head
      after element was deleted.
  */
  if (element->prev == NULL && element->next == NULL)
  {
    free(element);
    return NULL;
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
    node *list_head = element->next;
    free(element);
    return list_head;
  }

  node *list_head = find_head(element);
  free(element);
  return list_head;
}

node *delete_all(node *list, int number)
{
  node *found_element = find(list, number);
  if (found_element == NULL)
    return list;

  list = delete_element(found_element);
  delete_all(list, number);
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
