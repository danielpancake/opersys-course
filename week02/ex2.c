#include<stdio.h>

int main() {
  char buffer[256];

  int i = 0;
  char c;
  
  while(c = getchar(), c != '\n' && c != '.') {
    buffer[i] = c;
    ++i;
  }

  for (; i > 0; --i) {
    putchar(buffer[i - 1]);
  }

  putchar('\n');

  return 0;
}
