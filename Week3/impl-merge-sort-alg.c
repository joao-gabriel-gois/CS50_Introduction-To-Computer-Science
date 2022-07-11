#include <stdio.h>
/*
  Implementing mutable merge sort 
*/
typedef struct {
  int low;           /*
  private */int mid; // if possible, I would turn mid private
  int high;
  int* initial_array;
} params;            /*

- Algorithm:
public */void merge_sort(params parameters, int array[parameters.high - parameters.low + 1]); /*
private */void merge(params parameters); /* if possible, I would turn merge private
- Utils:
public */params set_params(int length, int array[length]); /*
public */void print_array(int length, int array[length]);


int main(void) {
  int merge_array_to_sort[] = { 3, 99, 0, 33, 1, 9, 75, 11, 6, 211, 7, 16, 1000, -3 };
  
  printf("\n\033[01;33mBefore Sort:");
  printf("\n\033[00;03m-> List: \033[03;34m");
  print_array(14, merge_array_to_sort);

  params info = set_params(14, merge_array_to_sort);

  merge_sort(info, merge_array_to_sort);

  printf("\n\033[01;32mAfter Merge Sort:");
  printf("\n\033[00;03m-> Sorted List: \033[03;34m");
  print_array(14, merge_array_to_sort);
  printf("\033[m\n");
} /*


- Algorithm:

public*/ void merge_sort(params parameters, int array[parameters.high - parameters.low + 1]) {
  int low = parameters.low;
  int high = parameters.high;
  
  if (low == high) return;

  int current_length = high - low + 1;
  int mid = (low + high) / 2;
  int left_half[mid + 1];
  int right_half[high - mid + 1];

  for (int i = 0; i < current_length; i++) {
    if (i <= mid) {
      left_half[i] = array[i];
    }
    else right_half[i] = array[i];
  }

  params left_params = parameters;
  params right_params = parameters;
  params merge_params = parameters;
  // left half should have mid as its higher index
  left_params.high = mid;
  // right half should have mid + 1 as its lowest index
  right_params.low = mid + 1;
  // merge func does not deduce mid, so we pass to it
  merge_params.mid = mid;

  merge_sort(left_params, left_half);
  merge_sort(right_params, right_half);
  merge(merge_params);
}                                                               /*
  If it would be possible, I would turn merge to private
    if both merge and parameters.mid was private, whoever
    uses merge_sort could not set mid, cause it is not needed

private */void merge(params parameters) {
  int low = parameters.low;
  int mid = parameters.mid;
  int high = parameters.high;
  int* array = parameters.initial_array;

  int tmp[high + 1];
  int i = low, j = mid + 1, k = low;

  while ((i <= mid) && (j <= high)) {
    if (array[i] <= array[j]) tmp[k++] = array[i++];
    else tmp[k++] = array[j++];
  }

  while (i <= mid) tmp[k++] = array[i++];
  while (j <= high) tmp[k++] = array[j++];
  
  for (i = low; i <= high; i++) array[i] = tmp[i];
} /*

- Utils:

public */params set_params(int length, int array[length]) {
  params parameters;
  parameters.low = 0;
  parameters.high = length - 1;
  parameters.initial_array = array;

  return parameters;
} /*

public */void print_array(int array_length, int array[array_length]) {
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
