#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int is_prime(int n) {
  if (n < 2) return 0;

  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) return 0;
  }

  return 1;
}

int K = 0, C = 0, n;

pthread_mutex_t k_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t c_mutex = PTHREAD_MUTEX_INITIALIZER;

int read_and_increment_k() {
  pthread_mutex_lock(&k_mutex);
  int k_copy = K;
  ++K;
  pthread_mutex_unlock(&k_mutex);
  return k_copy;
}

void increment_c() {
  pthread_mutex_lock(&c_mutex);
  ++C;
  pthread_mutex_unlock(&c_mutex);
}

void *prime_counter(void *arg) {
  int k_copy = read_and_increment_k();
  while (k_copy < n) {
    if (is_prime(k_copy)) {
      increment_c();
    }
    k_copy = read_and_increment_k();
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  int m;
  if (argc != 3 || sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2], "%d", &m) != 1) {
    fprintf(stderr, "Usage: %s <n> <m>\nwhere n is the range [0, n) and m is the number of threads\n", argv[0]);
    return 1;
  }

  pthread_t *threads = malloc(m * sizeof(pthread_t));

  for (int i = 0; i < m; ++i) {
    pthread_create(&threads[i], NULL, prime_counter, NULL);
  }

  for (int i = 0; i < m; ++i) {
    pthread_join(threads[i], NULL);
  }

  printf("There are %d primes in the interval [0, %d)\n", C, n);

  free(threads);
  return 0;
}
