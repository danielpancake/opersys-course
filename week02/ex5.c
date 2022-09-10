#include<stdio.h>

typedef unsigned long long int ulli;

ulli tribonacci(unsigned int n) {
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 0;
  } else if (n == 2) {
    return 1;
  }

  ulli a = 0, b = 0, c = 1, d = 0;
  unsigned int i = 3;

  for (; i <= n; ++i) {
    d = a + b + c;
    a = b;
    b = c;
    c = d;
  }

  return d;
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    unsigned int n = 0;
    sscanf(argv[1], "%d", &n);
    printf("Tribonacci %u term: %llu", n, tribonacci(n));
  } else {
    printf("One argument expected, %d given!", argc);
  }

  putchar('\n');

  return 0;
}