#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct Interval {
  int start;
  int end;
} Interval;

int is_prime(int n) {
  if (n < 2) return 0;

  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) return 0;
  }

  return 1;
}

int count_primes(int start, int end) {
  int count = 0;
  for (int i = start; i < end; ++i) {
    count += is_prime(i);
  }
  return count;
}

void *prime_counter(void *arg) {
  Interval *interval = (Interval *)arg;
  int *count = malloc(sizeof(int));
  *count = count_primes(interval->start, interval->end);
  pthread_exit(count);
}

int main(int argc, char *argv[]) {
  int n = atoi(argv[1]); // range [0, n)
  int m = atoi(argv[2]); // m is the number of threads

  int step = n / m + (n % m != 0);

  pthread_t *threads = malloc(m * sizeof(pthread_t));
  Interval *intervals = malloc(m * sizeof(Interval));

  void **retvals = malloc(m * sizeof(void *));

  for (int i = 0; i < m; ++i) {
    intervals[i].start = i * step;
    intervals[i].end = (i + 1) * step;
    pthread_create(&threads[i], NULL, prime_counter, &intervals[i]);
  }

  for (int i = 0; i < m; ++i) {
    pthread_join(threads[i], &retvals[i]);
  }

  // Printing the result
  int total = 0;
  for (int i = 0; i < m; ++i) {
    total += *(int *)retvals[i];
  }

  printf("Total number of primes: %d\n", total);

  free(threads);
  free(intervals);
  free(retvals);

  return 0;
}
