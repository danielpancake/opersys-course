#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main(int argc, char * argv[]) {
  if (argc != 2) {
    printf("Invalid number of arguments. Please enter a single number.\n");
    return 1;
  }

  int n = 0;
  if (sscanf(argv[1], "%d", &n) != 1) {
    printf("Invalid argument. Please enter a single number.\n");
    return 1;
  }

  for (int i = 0; i < n; ++i) {
    fork();
    sleep(5);
  }

	return EXIT_SUCCESS;
}
