#include<stdio.h>

int main() {
  char buffer[256];

  printf("This program asks the user to enter a string until dot (.) character is entered and prints its reverse with double quotation.\nEnter the string:");

  int i = 0;
  char c;
  
  while(c = getchar(), c != '\n' && c != '.') {
    buffer[i] = c;
    ++i;
  }

  putchar('"');

  for (; i > 0; --i) {
    putchar(buffer[i - 1]);
  }

  printf("\"\n");

  return 0;
}
