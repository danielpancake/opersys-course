#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sum_of_array(char *array, int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += array[i];
  }
  return sum;
}

int main() {
  int fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);

  if (fd == -1) {
    return EXIT_FAILURE;
  }

  FILE *output = fopen("ex3.txt", "w");

  char keyboard[256] = {0};

  while (1) {
    struct input_event ie;
    read(fd, &ie, sizeof(ie));

    if (ie.type == EV_KEY) {
      keyboard[ie.code] = ie.value > 0 ? 1 : 0;

      // CAP shortcut
      if (keyboard[KEY_C] && keyboard[KEY_A] && keyboard[KEY_P] &&
          sum_of_array(keyboard, 256) == 3) {
        fprintf(output, "Get some cappuccino!\n");
      }

      // PE shortcut
      if (keyboard[KEY_P] && keyboard[KEY_E] &&
          sum_of_array(keyboard, 256) == 2) {
        fprintf(output, "I passed the Exam!\n");
      }

      // Linux shortcut
      if (keyboard[KEY_L] && keyboard[KEY_I] && keyboard[KEY_N] && keyboard[KEY_U] && keyboard[KEY_X] &&
          sum_of_array(keyboard, 256) == 5) {
        fprintf(output, "I love Linux!\n");
      }

      // ESC shortcut
      if (keyboard[KEY_ESC] && sum_of_array(keyboard, 256) == 1) {
        fprintf(output, "Bye!\n");
        break;
      }

      fflush(stdout);
    }
  }

  fclose(output);
  close(fd);

  return EXIT_SUCCESS;
}
