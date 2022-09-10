#include <limits.h>
#include <float.h>

#include <stdio.h>

int main() {

  // Declaring some primitive types
  int int_value;
  unsigned short int unsigned_short_int_value;
  float float_value;
  double double_value;

  // Assigning maximum values to these variables
  int_value = INT_MAX;
  unsigned_short_int_value = USHRT_MAX;
  float_value = FLT_MAX;
  double_value = DBL_MAX;

  // Printing the sizes and values
  printf("Size of int: %ld bytes", sizeof(int_value));
  printf("\nMax value of int: %d", int_value);
  
  printf("\n\nSize of unsigned short int: %ld bytes", sizeof(unsigned_short_int_value));
  printf("\nMax value of unsigned short int: %d", unsigned_short_int_value);
  
  printf("\n\nSize of float: %ld bytes", sizeof(float_value));
  printf("\nMax value of float: %f", float_value);

  printf("\n\nSize of double: %ld bytes", sizeof(double_value));
  printf("\nMax value of double: %f", double_value);

  printf("\n"); 
  
  return 0;
}
