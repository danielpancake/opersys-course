#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
  int i;
  void *p[10];

  for (i = 0; i < 10; i++) {
    *(p+i) = malloc(1024 * 1024 * 1024);
    // Filling the allocated memory with zeros
    // As allocated memory approaches the limit of the available physical memory,
    // some memory gets dumped to the disc.

    // While using top, we can see that the memory usage is increasing.
    // When the physical memory is full, the memory usage of the swap stars increasing.
    if (*(p+i) != NULL) {
      memset(*(p+i), 0, 1024 * 1024 * 1024);
    } else {
      printf("Memory allocation failed\n");
    }
    sleep(1);
  }

  for (i = 0; i < 10; i++) {
    free(*(p+i));
  }

  return 0;
}
