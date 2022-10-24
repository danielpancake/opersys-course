/*
#include <stdio.h>

int main() {
  char **s;
  char foo[] = "Hello World";
  *s = foo;

  printf("s is %s\n", s);

  s[0] = foo;

  printf("s [0] is %s\n", s[0]);

  return 0;
}
*/

#include <stdio.h>

int main() {
  char **s;
  char *foo = "Hello World"; // changed char foo[] to char *foo
  s = &foo;                  // changed *s = foo to s = &foo

  printf("s is %s\n", *s);   // changed s to *s
  s[0] = foo;

  printf("s [0] is %s\n", s[0]);

  return 0;
}
