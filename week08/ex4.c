#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* my_realloc(void* ptr, size_t size) {
  if (ptr == NULL) {
    return malloc(size);
  }

  if (size == 0) {
    free(ptr);
    return NULL;
  }

  void* new_ptr = malloc(size);
  if (new_ptr == NULL) {
    return NULL;
  }

  size_t old_size = malloc_usable_size(ptr);
  size_t min_size = old_size < size ? old_size : size;

  memcpy(new_ptr, ptr, min_size);
  free(ptr);

  return new_ptr;
}

int main() {
  int i;

  // Allows user to specify the original array size, stored in variable n1.
  printf("Enter original array size: ");

  int n1 = 0;
  scanf("%d", &n1);

  // Create a new array of n1 ints
  int* arr = malloc(n1 * sizeof(int));

  for (i = 0; i < n1; ++i) {
    // Set each value in arr to 100
    arr[i] = 100;

    // Print each element out (to make sure things look right)
    printf("%d ", arr[i]);
  }

  // User specifies the new array size, stored in variable n2.
  printf("\nEnter new array size: ");

  int n2 = 0;
  scanf("%d", &n2);

  // Dynamically change the array to size n2 with own realloc implementation
  arr = my_realloc(arr, n2 * sizeof(int));

  // If the new array is a larger size, set all new members to 0. Reason: dont want to use uninitialized variables.
  for (i = n1; i < n2; ++i) {
    arr[i] = 0;
  }

  // Print each element out (to make sure things look right)
  for (i = 0; i < n2; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  // Done with array now, done with program :D
  free(arr);

  return 0;
}
