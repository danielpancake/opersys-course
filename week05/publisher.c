#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);

  printf("Publisher started!\n");
  printf("Hi! I'm the publisher. I will send messages to the subscriber\n");
  printf("Send /stop to stop the publisher\n");

  mkfifo("/tmp/ex1", 0666);
  int pipefd = open("/tmp/ex1", O_WRONLY);

  char buffer[1024];

  while (1) {
    fgets(buffer, 1024, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    for (int i = 0; i < n; i++) {
      write(pipefd, buffer, sizeof(buffer));
      sleep(1);
    }

    if (strcmp(buffer, "/stop") == 0) {
      printf("Stopping...\n");
      break;
    }
  }

  close(pipefd);
  unlink("/tmp/ex1");

  return 0;
}
