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
node **create(int number);
void insert(node **list, int number);
node *find_first(node *list, int number);
bool delete(node **element);
bool delete_all(node *list, int number);
void destroy(node *list);
void print_list(node *list);

// DEMO
int main(void)
{
  // Creating
  node **list1 = create(18);
  node **list2 = create(10);

  // Filling
  for (int i = 0; i < 9; i++)
    insert(list1, i);
  for (int i = 18; i > 0; i -= 2)
    insert(list2, i);

  // Showing
  printf("\033[05;35m\nBefore changes: \033[m\n");
  printf("List 1");
  print_list(*list1);
  printf("List 2");
  print_list(*list2);

  // Modifying
  node *eight_found_1 = find_first(*list1, 8);
  node *one_found_1 = find_first(*list1, 2);
  node *not_found_92 = find_first(*list1, 92);

  bool removed11 = delete (&eight_found_1);
  bool removed12 = delete (&one_found_1);
  bool not_removed1 = delete (&not_found_92);

  printf("\033[33mList 1 modification status: \033[m");
  printf(
      "\033[03;30mNot removed (92): %s | Removed (8 and 1) %s and %s, respectively\033[m\n",
      bool_enum[not_removed1], bool_enum[removed11], bool_enum[removed12]);

  node *ten_found_2 = find_first(*list2, 10);
  node *fourteen_found_2 = find_first(*list2, 14);
  node *not_found_173 = find_first(*list2, 173);

  bool removed21 = delete (&ten_found_2);
  bool removed22 = delete (&fourteen_found_2);
  bool not_removed2 = delete (&not_found_173);

  printf("\033[33mList 2 modification status: \033[m");
  printf(
      "\033[03;30mNot removed (173): %s | Removed (10 and 14) %s and %s, respectively\033[m\n",
      bool_enum[not_removed2], bool_enum[removed21], bool_enum[removed22]);

  // Showing after changes
  printf("\033[05;36m\nAfter removing first matches for 8 and 1 in list1 and first matchs for 10 and 14 in list2: \033[m\n");
  printf("List 1");
  print_list(*list1);
  printf("List 2");
  print_list(*list2);

  // Searching
  char *found = "\033[01;32mfound!\033[m";
  char *not_found = "\033[01;31mnot found!\033[m";
  printf("- Searching 5 in list 1, and it was %s", find_first(*list1, 5) != NULL ? found : not_found);
  printf("\n- Searching 8 in list 1, and it was %s", find_first(*list1, 8) != NULL ? found : not_found);
  printf("\n- Searching 14 in list 2, and it was %s", find_first(*list2, 14) != NULL ? found : not_found);
  printf("\n- Searching 8 in list 2, and it was %s\n", find_first(*list2, 8) != NULL ? found : not_found);

  // (Showing - Modifying - showing) again
  printf("\033[05;35m\nBefore inserting: \033[m\n");
  printf("List 1");
  print_list(*list1);
  printf("List 2");
  print_list(*list2);

  insert(list1, 1);
  insert(list1, 1);
  insert(list2, 2);
  insert(list2, 2);

  printf("\033[05;34m\nAfter inserting/before removing: \033[m\n");
  printf("List 1");
  print_list(*list1);
  printf("List 2");
  print_list(*list2);

  // bool removed13 = delete_all(list1, 1);
  // bool not_removed3 = delete_all(list1, 92);
  // printf("\033[33mList 1 modification status: \033[m");
  // printf(
  //     "\033[03;30mNot removed (92): %s | Removed (1) %s\033[m\n",
  //     bool_enum[not_removed3], bool_enum[removed13]);

  // bool removed23 = delete_all(list2, 2);
  // bool not_removed4 = delete_all(list2, 173);
  // printf("\033[33mList 2 modification status: \033[m");
  // printf(
  //     "\033[03;30mNot removed (173): %s | Removed (2) %s\033[m\n",
  //     bool_enum[not_removed4], bool_enum[removed23]);

  // printf("\033[05;36m\nAfter removing all 1's in list1 and all 2's in list2: \033[m\n");
  // printf("List 1");
  // print_list(list1);
  // printf("List 2");
  // print_list(list2);

  // Destroying
  destroy(*list1);
  destroy(*list2);

  return 0;
}

// "METHODS" implementation
node **create(int number)
{
  node *list = malloc(sizeof(node));
  list->number = number;
  list->next = NULL;
  list->previous = NULL;

  node **list_address = &list;

  return list_address;
}

void insert(node **list, int number)
{
  node **new_item = create(number);

  (*list)->previous = *new_item;
  (*new_item)->next = *list;

  *list = *new_item;
}

node *find_first(node *list, int number)
{
  while (list != NULL)
  {
    if ((list)->number == number)
      return list;
    list = list->next;
  }

  return NULL;
}

bool delete(node **element)
{
  node *tmp = *element;
  if (tmp == NULL)
    return false;
  if (tmp->previous == NULL)
  {
    if (tmp->next != NULL)
    {
      *element = (*element)->next;
      free(tmp);
      (*element)->previous = NULL;
      return true;
    }

    *element = NULL;
    free(tmp);
    return true;
  }
  else
  {
    if ((*element)->next == NULL)
    {
      *element = (*element)->previous;
      free(tmp);
      (*element)->next = NULL;
      return true;
    }

    node *tmp = *element;
    (*element)->next->previous = tmp->previous;
    (*element)->previous->next = tmp->next;
    free(tmp);
    return true;
  }

  // if (*element == NULL)
  //   return false;
  // node *tmp = *element;
  // if (tmp->previous != NULL)
  // {
  //   (*element)->previous->next = tmp->next;
  //   if (tmp->next != NULL)
  //   {
  //     (*element)->next->previous = tmp->previous;
  //   }
  //   free(tmp);
  //   return true;
  // }
  // else
  // {
  //   if (tmp->next != NULL)
  //   {
  //     (*element)->next->previous = tmp->previous;
  //   }
  //   *element = tmp->next;
  //   free(tmp);
  //   return true;
  // }

  // if (tmp->next != NULL)
  // {
  //   (*element)->next->previous = tmp->previous;
  // }

  // // I prefered to keep it 4 ifs so we can first check on element before reassigning it
  // if (tmp->next == NULL)
  // {
  //   *element = NULL;
  // }
  // if (tmp->previous == NULL)
  // {
  //   *element = tmp->next;
  // }
}

bool delete_all(node *list, int number)
{
  node *remaining_element = find_first(list, number);
  bool removed = delete (&remaining_element);

  // printf(">>[%p] - Removed %s | Remaining? %s\n", list, bool_enum[removed], bool_enum[has_remaining_elements]);
  if (!removed)
    return false;
  else if (remaining_element == NULL)
    return true;

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
