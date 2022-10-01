#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

// Calculates the dot product of the vectors u and v from the component [start] till the component [end] exclusively.
int dot_product(int u[], int v[], int start, int end) {
  int result = 0;
  for (int i = start; i < end; ++i) {
    result += u[i] * v[i];
  }
  return result;
}

int main() {
  // Creating two vectors u and v using arrays of 120 elements
  int u[120], v[120];

  // Setting the seed for the random number generator
  srand(clock());

  // Filling the vectors with random numbers
  for (int i = 0; i < 120; i++) {
    u[i] = rand() % 100;
    v[i] = rand() % 100;
  }

  // Create a pool/array of n processes where n is an input number from stdin
  int n;
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  if (n <= 0 || n > 10 || n&1) {
    printf("Invalid number of processes. Please enter an even number between 1 and 10.\n");
    return 1;
  }

  pid_t pids[n];

  FILE * in_file, * out_file;
  in_file = fopen("temp.txt", "r");
  out_file = fopen("temp.txt", "w");

  int m = 120 / n;
  // Create n processes
  for (int i = 0; i < n; i++) {
    pid_t child = fork();

    if (child == 0) {
      fprintf(out_file, "%d\n", dot_product(u, v, i*m, (i+1)*m));
      exit(0); // Terminate the child process
    } else {
      pids[i] = child;
    }
  }

  for (int i = 0; i < n; i++) {
    waitpid(pids[i], NULL, 0);
  }

  // Aggregate the results from the child processes
  int result = 0, temp;
  for (int i = 0; i < n; i++) {
    fscanf(in_file, "%d", &temp);
    result += temp;
  }

  printf("The dot product of the vectors u and v is: %d\n", result);

  fclose(out_file);
  fclose(in_file);
  return 0;
}
