#include<stdio.h>

typedef long long int lli;

/*
 * This function converts a positive integer number from base 10 to any other base in range of [2,10]
 * The result is returned as a long long integer value
 * 
 * Function does not check for invalid inputs
 * 
 * Known issues:
 * - If while conversion the result exceeds the capacity of long long integer, the result will be incorrect
 */
lli convert_to_dec(lli number, int base) {
  lli result = 0;
  lli multiplier = 1;

  while (number > 0) {
    result += (number % 10) * multiplier;
    multiplier *= base;
    number /= 10;
  }

  return result;
}

/*
 * This function converts a positive integer number from any base in range of [2,10] to any other base in the same range
 * The result is returned as a long long integer value
 *
 * Function does not check for invalid inputs
 * 
 * Known issues:
 * - If while conversion the result exceeds the capacity of long long integer, the result will be incorrect
 */
lli convert(lli number, int base_from, int base_to) {
  lli result = 0;
  lli remainder = 0;
  lli position = 1;

  if (base_from != 10) {
    number = convert_to_dec(number, base_from);
  }

  while (number > 0) {
    remainder = number % base_to;
    result += remainder * position;
    position *= 10;
    number /= base_to;
  }

  return result;
}

int error(char *message) {
  printf("%s\n", message);
  return 33;
}

int main() {
  lli number;
  int base_from, base_to;

  char buffer[20];

  printf("Enter a number: ");
  fgets(buffer, 20, stdin);
  sscanf(buffer, "%llu", &number);

  // Check whether number is positive
  if (number < 0) {
    return error("Cannot convert!");
  }

  printf("Enter the base of the number: ");
  fgets(buffer, 20, stdin);
  sscanf(buffer, "%d", &base_from);

  // Check whether base is valid
  if (base_from < 2 || base_from > 10) {
    return error("Cannot convert!");
  }

  // Check if the number is valid for the base
  lli _temp = number;
  while (_temp != 0) {
    // ..every digit must be less than the base
    if (_temp % 10 >= base_from) {
      return error("Cannot convert!");
    }

    _temp /= 10;
  }

  printf("Enter the base to convert to: ");
  fgets(buffer, 20, stdin);
  sscanf(buffer, "%d", &base_to);

  // Check whether base is valid
  if (base_to < 2 || base_to > 10) {
    return error("Cannot convert!");
  }

  printf("The converted number is: %lld", convert(number, base_from, base_to));
  putchar('\n');

  return 0;
}
