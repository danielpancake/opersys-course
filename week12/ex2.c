#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);

  if (fd == -1) {
    return EXIT_FAILURE;
  }

  FILE *output = fopen("ex2.txt", "w");

  while (1) {
    struct input_event ie;
    read(fd, &ie, sizeof(ie));

    if (ie.type == EV_KEY) {
      if (ie.value == 1) {
        fprintf(output, "PRESSED 0x%04x (%d)\n", ie.code, ie.code);
      } else if (ie.value == 0) {
        fprintf(output, "RELEASED 0x%04x (%d)\n", ie.code, ie.code);
      }
    }

    fflush(output);
  }

  fclose(output);
  close(fd);

  return EXIT_SUCCESS;
}
