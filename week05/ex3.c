#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

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
  int n, m;  // range [0, n) and m is the number of threads
  if (argc != 3 || sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2], "%d", &m) != 1) {
    fprintf(stderr, "Usage: %s <n> <m>\nwhere n is the range [0, n) and m is the number of threads\n", argv[0]);
    return 1;
  }

  int remainder = n % m;
  int step = (n - remainder) / m;

  pthread_t *threads = malloc(m * sizeof(pthread_t));
  Interval *intervals = malloc(m * sizeof(Interval));

  void **retvals = malloc(m * sizeof(void *));

  for (int start = 0, end = step, i = 0; i < m; ++i, start = end, end += step) {
    if (remainder) {
      --remainder;
      ++end;
    }
    intervals[i] = (Interval){start, end};
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

  printf("There are %d primes in the interval [0, %d)\n", total, n);

  free(threads);
  free(intervals);
  free(retvals);

  return 0;
}
