#include <stdio.h>
#include <unistd.h>

int main() {
  int pipefd[2];
  pipe(pipefd);

  pid_t cpid = fork();

  if (cpid == 0) {  // Subscriber
    close(pipefd[1]);

    while (1) {
      char buffer[1024] = "";
      read(pipefd[0], buffer, 1024);
      write(STDOUT_FILENO, buffer, 1024);
    }
  } else {  // Publisher
    close(pipefd[0]);

    while (1) {
      char buffer[1024] = "";
      fgets(buffer, 1024, stdin);
      write(pipefd[1], buffer, 1024);
    }
  }

  return 0;
}
