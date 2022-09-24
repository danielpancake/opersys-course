#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>

#define MAX_LINE 80 /* The maximum length of a command */

int main() {
  char command[MAX_LINE];
  char *args[MAX_LINE];

  while (1) {
    printf("Enter command: ");
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

    // Forking a child process
    pid_t pid = fork();
    if (pid == 0) {
      execvp(args[0], args);
      break;
    } else {
      waitpid(pid, NULL, 0);
    }
  }
  
  return 0;
}
