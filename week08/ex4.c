#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>

int main() {
  int i;
  void *p[10];

  for (i = 0; i < 10; i++) {
    *(p+i) = malloc(10 * 1024 * 1024);

    // Filling the allocated memory with zeros
    if (*(p+i) != NULL) {
      memset(*(p+i), 0, 10 * 1024 * 1024);
    }

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    printf("Memory usage: %ldKB\n", usage.ru_maxrss);

    sleep(1);
  }

  for (i = 0; i < 10; i++) {
    free(*(p+i));
  }

  return 0;
}
