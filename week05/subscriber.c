#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  char buffer[1024];
  int pipefd = open("/tmp/ex1", O_RDONLY);

  while (1) {
    read(pipefd, buffer, 1024);
    printf("Received: %s\n", buffer);

    if (strcmp(buffer, "/stop") == 0) {
      printf("Stopping\n");
      break;
    }
  }

  close(pipefd);

  return 0;
}
