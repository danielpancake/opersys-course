#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
  clock_t start_time, end_time;
  pid_t child_a, child_b;

  child_a = fork();
  start_time = clock();

  if (child_a == 0) {
    sleep(3);
    
    end_time = clock();
    printf("Child A, iD: %d, parent ID: %d, elapsed time: %fms\n",
      getpid(), getppid(), (double)(1000 * (end_time - start_time)) / CLOCKS_PER_SEC);
  } else {
    child_b = fork();
    start_time = clock();

    if (child_b == 0) {
      sleep(5);
      
      end_time = clock();
      printf("Child B, iD: %d, parent ID: %d, elapsed time: %fms\n",
        getpid(), getppid(), (double)(1000 * (end_time - start_time)) / CLOCKS_PER_SEC);
    } else {
      // Waiting for child processes to finish
      waitpid(child_a, NULL, 0);
      waitpid(child_b, NULL, 0);

      end_time = clock();
      printf("Parent, iD: %d, parent ID: %d, elapsed time: %fms\n",
        getpid(), getppid(), (double)(1000 * (end_time - start_time)) / CLOCKS_PER_SEC);
    }
  }

  return 0;
}
