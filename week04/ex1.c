#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
  clock_t elapsed_time;
  pid_t child_a, child_b;

  child_a = fork();
  elapsed_time = clock();

  if (child_a == 0) {
    for (long long int i = 0; i < 1000000000; i++) {
      // Do nothing
    }
    
    elapsed_time = clock() - elapsed_time;
    printf("Child A, iD: %d, parent ID: %d, elapsed time: %fms\n",
      getpid(), getppid(), (double)(1000 * elapsed_time) / CLOCKS_PER_SEC);
  } else {
    child_b = fork();

    if (child_b == 0) {
      elapsed_time = clock();

      for (long long int i = 0; i < 1000000000; i++) {
        // Do nothing
      }

      elapsed_time = clock() - elapsed_time;
      printf("Child B, iD: %d, parent ID: %d, elapsed time: %fms\n",
        getpid(), getppid(), (double)(1000 * elapsed_time) / CLOCKS_PER_SEC);
    } else {
      // Waiting for child processes to finish
      waitpid(child_a, NULL, 0);
      waitpid(child_b, NULL, 0);

      elapsed_time = clock() - elapsed_time;
      // This time does not account for the time spent waiting for child processes
      // See NOTES section of https://man7.org/linux/man-pages/man3/clock.3.html

      printf("Parent, iD: %d, parent ID: %d, elapsed time: %fms\n",
        getpid(), getppid(), (double)(1000 * elapsed_time) / CLOCKS_PER_SEC);
    }
  }

  return 0;
}
