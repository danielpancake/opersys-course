#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>

#define MAX_LINE 80 /* The maximum length of a command */

int main() {
  char command[MAX_LINE];
  char *args[MAX_LINE];

  char background = 0; // 1 if the command is followed by &, 0 otherwise

  while (1) {
    printf("Enter command: ");
    background = 0;

    fgets(command, MAX_LINE, stdin);
    command[strlen(command) - 1] = '\0';
    
    if (strcmp(command, "exit") == 0) {
      break;
    }

    // Parsing arguments
    int i = 0;
    args[i] = strtok(command, " ");
    while (args[i] != NULL) {
      args[++i] = strtok(NULL, " ");
    }

    if (i > 1) {
      // Checking if the command is followed by &
      if (strcmp(args[i - 1], "&") == 0) {
        background = 1;
        args[i - 1] = NULL;
      }
    }

    // Forking a child process
    pid_t pid = fork();
    if (pid == 0) {
      execvp(args[0], args);
      break;
    } else if (background == 0) {
      waitpid(pid, NULL, 0);
    }
  }
  
  return 0;
}
