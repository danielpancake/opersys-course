#include <stdio.h>

int compare_strings(char *str1, char *str2) {
  int i = 0;
  while (str1[i] != '\0' && str2[i] != '\0') {
    if (str1[i] != str2[i]) {
      return 0;
    }
    i++;
  }
  return 1;
}

void triangle(int n) {
  for (int i = 0; i < n; i++){
    for (int j = 0; j < i + 1; j++){
      printf("*");
    }
    printf("\n");
  }
}

void reverse_triangle(int n) {
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n - i; j++){
      printf("*");
    }
    printf("\n");
  }
}

void pyramid(int n) {
  triangle((n - n%2) / 2 + n%2);
  reverse_triangle((n - n%2) / 2);
}

void rectangle(int n, int m) {
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      printf("*");
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("This program prints a shape based on the input parameters.\n\n\
      triangle <n> - prints a triangle with n rows\n\
      reverse_triangle <n> - prints a reverse triangle with n rows\n\
      pyramid <n> - prints a pyramid with n rows\n\
      rectangle <n> <m> - prints a rectangle with n rows and m columns\n");
  } else {
    int a = 0, b = 0;

    if (compare_strings(argv[1], "triangle")) {
      if (argc == 3) {
        if (sscanf(argv[2], "%d", &a)) {
          triangle(a);
        } else {
          printf("Invalid input!\n");
        }
      } else {
        printf("Invalid number of arguments for triangle.\nExpected 2 arguments, got %d.\n", argc - 1);
      }
    } else if (compare_strings(argv[1], "reverse_triangle")) {
      if (argc == 3) {
        if (sscanf(argv[2], "%d", &a)) {
          reverse_triangle(a);
        } else {
          printf("Invalid input!\n");
        }
      } else {
        printf("Invalid number of arguments for reverse_triangle.\nExpected 2 arguments, got %d.\n", argc - 1);
      }
    } else if (compare_strings(argv[1], "pyramid")) {
      if (argc == 3) {
        if (sscanf(argv[2], "%d", &a)) {
          pyramid(a);
        } else {
          printf("Invalid input!\n");
        }
      } else {
        printf("Invalid number of arguments for pyramid.\nExpected 2 arguments, got %d.\n", argc - 1);
      }
    } else if (compare_strings(argv[1], "rectangle")) {
      if (argc == 4) {
        if (sscanf(argv[2], "%d", &a) && sscanf(argv[3], "%d", &b)) {
          rectangle(a, b);
        } else {
          printf("Invalid input!\n");
        }
      } else {
        printf("Invalid number of arguments for rectangle.\nExpected 3 arguments, got %d.\n", argc - 1);
      }
    } else {
      printf("Invalid command\n");
    }
  }

  return 0;
}
