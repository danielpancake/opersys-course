#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void* aggregate(void* base, size_t size, int n, void* initial_value, void* (*opr)(const void*, const void*)) {
  void* result;

  if (size == sizeof(int)) {
    result = (int*)malloc(sizeof(int));
    *(int*)result = *(int*)initial_value;
  } else if (size == sizeof(double)) {
    result = (double*)malloc(sizeof(double));
    *(double*)result = *(double*)initial_value;
  }

  for (int i = 0; i < n; i++) {
    result = opr(result, base + i * size);
  }

  return result;
}

int* add_to_int(const int* a, const int* b) {
  int *t = a;
  *t = *a + *b;
  return a;
}

double* add_to_double(const double* a, const double* b) {
  double *t = a;
  *t = *a + *b;
  return a;
}

int* multiply_by_int(const int* a, const int* b) {
  int *t = a;
  *t = *a * *b;
  return a;
}

double* multiply_by_double(const double* a, const double* b) {
  double *t = a;
  *t = *a * *b;
  return a;
}

int* mean_of_int(const int* a, const int* b) {
  int *t = a;
  *t = (*a + *b) / 2;
  return a;
}

double* mean_of_double(const double* a, const double* b) {
  double *t = a;
  *t = (*a + *b) / 2;
  return a;
}

int main() {
  int* ints = malloc(sizeof(int)*5);
  double* doubles = malloc(sizeof(double)*5);

  for (int i = 0; i < 5; i++) {
    ints[i] = i + 10;
    doubles[i] = pow(3.14, i);
  }

  printf("Array of ints: ");
  for (int i = 0; i < 5; i++) {
    printf("%d ", ints[i]);
  }
  printf("\n");

  printf("Array of doubles: ");
  for (int i = 0; i < 5; i++) {
    printf("%f ", doubles[i]);
  }
  printf("\n");

  int initial_int = 0;
  double initial_double = 0.0;

  int* sum_int = aggregate(ints, sizeof(int), 5, &initial_int, &add_to_int);
  double* sum_double = aggregate(doubles, sizeof(double), 5, &initial_double, &add_to_double);

  printf("Sum of ints: %d\n", *sum_int);
  printf("Sum of doubles: %f\n", *sum_double);

  initial_int = 1;
  initial_double = 1.0;
  int* product_int = aggregate(ints, sizeof(int), 5, &initial_int, &multiply_by_int);
  double* product_double = aggregate(doubles, sizeof(double), 5, &initial_double, &multiply_by_double);

  printf("Product of ints: %d\n", *product_int);
  printf("Product of doubles: %f\n", *product_double);

  initial_int = 0;
  initial_double = 0.0;
  int* mean_int = aggregate(ints, sizeof(int), 5, &initial_int, &mean_of_int);
  double* mean_double = aggregate(doubles, sizeof(double), 5, &initial_double, &mean_of_double);

  printf("Mean of ints: %d\n", *mean_int);
  printf("Mean of doubles: %f\n", *mean_double);

  return 0;
}
