#include<stdio.h>

char to_lowercase(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c + 32;
  }
  return c;
}

unsigned int count(char * const string, char c) {
  unsigned int result = 0;

  c = to_lowercase(c);

  char *current_char = string;
  while (*current_char != '\0' && *current_char != '\n') {
    if (to_lowercase(*current_char) == c) {
      result++;
    }
    ++current_char;
  }

  return result;
}

void count_all(char * const string) {
  char *current_char = string;
  while (*current_char != '\0' && *current_char != '\n') {
    printf("%c: %d", to_lowercase(*current_char), count(string, *current_char));
    ++current_char;

    if (*current_char != '\0' && *current_char != '\n') {
      printf(", ");
    }
  }
  printf("\n");
}

int main() {
  char buffer[256];
  printf("This program prints number of occurrences of each character in the input string.\nInput: ");

  fgets(buffer, 256, stdin);

  count_all(buffer);

  return 0;
}
