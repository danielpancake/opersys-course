#include <stdlib.h>
#include <stdio.h>

int foo(int age) {
	return 2022 - age;
}

int main() {
  // Pointer q to a constant integer x whose constant value is 10
  const int x = 10;
  const int * q = &x;
  
  // Creating 5 contiguous memory cells of type constant integer,
  // referring to them by a constant pointer p, and filling these cells
  // with the value of x
  const int * const p = calloc(x, 5 * sizeof(int));
  int * const p2 = p;

  // Printing the memory addresses of these cells to stdout
  printf("The memory addresses of the allocated cells are:\n");
  for (int i = 0; i < 5; i++) {
    printf("%p\n", p + i);
  }

  // Reading the ages from stdin, and store them in these cells
  printf("\nPlease enter ages of 5 students:\n");
  for (int i = 0; i < 5; i++) {
    scanf("%d", p + i);
  }

  printf("\nTheir birth years are:\n");
  for (int i = 0; i < 5; i++) {
    *(p2 + i) = foo(*(p + i));
    printf("%d\n", *(p2 + i));
  }
  
  free(p2);

  return 0;
}
