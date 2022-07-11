#include <stdio.h>


void merge_sort(int low, int high);
void merge(int low, int mid, int high);
void print_array(int array_length, int array[array_length]);

#define MAX 8

int arr[MAX];

void main() {
  int i;
  printf("\033[01;38mInsert each element of the numbers set you want:\033[m\n");
  for (i = 0; i < MAX; i++) {
    printf("\033[02;36mPos %i)\033[m ", i + 1);
    printf("\033[03;34m");
    scanf("%d", &arr[i]);
  }
  printf("______\n");
  printf("\n\033[01;33mBefore Sort:");
  printf("\n\033[00;03m-> List: \033[03;34m");
  print_array(MAX, arr);

  merge_sort(0, MAX - 1);
  
  printf("\n\033[01;32mAfter Merge Sort:");
  printf("\n\033[00;03m-> Sorted List: \033[03;34m");
  print_array(MAX, arr);
  printf("\033[m\n");
}

void merge_sort(int low, int high) {
  if (low != high) {
    int mid = (low + high) / 2;
    merge_sort(low, mid);
    merge_sort(mid + 1, high);
    merge(low, mid, high);
  }
}

void merge(int low, int mid, int high) {
  int tmp[MAX];
  int i = low, k = low, j = mid + 1;

  while ((i <= mid) && (j <= high)) {
    if (arr[i] <= arr[j]) tmp[k++] = arr[i++];
    else tmp[k++] = arr[j++];
  }

  while (i <= mid) tmp[k++] = arr[i++];
  while (j <= high) tmp[k++] = arr[j++];

  for (i = low; i <= high; i++) arr[i] = tmp[i];
}


void print_array(int array_length, int array[array_length]) {
  printf("[ ");
  for (int i = 0; i < array_length; i++) {
    printf(
      "%i%s",
      array[i],
      i != array_length - 1 ? ", " : " "
    );
  }
  printf("];\n");
  return;
}