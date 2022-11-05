#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PAGE_ENTRY {
  size_t page;
  unsigned char age;
  char occupied;
} PAGE_ENTRY;

int main(int argc, char *argv[]) {
  int nframes;
  if (argc != 2 || sscanf(argv[1], "%d", &nframes) != 1) {
    printf("Expected a number of page frames as an argument!\n");
    return 1;
  }

  FILE *in = fopen("Lab 09 input.txt", "r");
  if (in == NULL) {
    printf("Could not open input file!\n");
    return 2;
  }

  PAGE_ENTRY *PAGE_TABLE = malloc(sizeof(PAGE_ENTRY) * nframes);
  for (int i = 0; i < nframes; i++) {
    PAGE_TABLE[i].page = 0;
    PAGE_TABLE[i].age = 0;
    PAGE_TABLE[i].occupied = 0;
  }

  int page_number = 0, misses = 0, hits = 0;

  while (fscanf(in, "%u", &page_number) == 1) {
    PAGE_ENTRY *referenced_page = NULL;

    for (int i = 0; i < nframes; i++) {
      if (PAGE_TABLE[i].occupied == 1 && PAGE_TABLE[i].page == page_number) {
        referenced_page = &PAGE_TABLE[i];
        break;
      }
    }

    // All comments left intentionally for debugging purposes
    if (referenced_page != NULL) {
      hits++;
    } else {
      misses++;

      for (int i = 0; i < nframes; i++) {
        if (PAGE_TABLE[i].occupied == 0) {
          PAGE_TABLE[i].page = page_number;
          PAGE_TABLE[i].age = 0;
          PAGE_TABLE[i].occupied = 1;

          referenced_page = &PAGE_TABLE[i];
          // printf("Page %u loaded into frame %d\n", page_number, i);
          break;
        }
      }

      if (referenced_page == NULL) {
        int min_age = 128 + 1;
        int min_age_index = 0;

        for (int i = 0; i < nframes; i++) {
          if (PAGE_TABLE[i].age < min_age) {
            min_age = PAGE_TABLE[i].age;
            min_age_index = i;
          }
        }

        // printf("Page %u loaded into frame %d, evicting page %u\n", page_number,
        //        min_age_index, PAGE_TABLE[min_age_index].page);

        referenced_page = &PAGE_TABLE[min_age_index];

        referenced_page->page = page_number;
        referenced_page->age = 0;
      }
    }

    for (int i = 0; i < nframes; i++) {
      if (PAGE_TABLE[i].occupied == 1) {
        PAGE_TABLE[i].age = PAGE_TABLE[i].age >> 1;
      }
    }

    referenced_page->age |= 1 << (sizeof(unsigned char) * 8 - 1);
    // for (int i = 0; i < nframes; i++) {
    //   printf("%u %d\n", PAGE_TABLE[i].page, PAGE_TABLE[i].age);
    // }
  }

  printf("Number of page frames: %d\n", nframes);
  printf("Hits: %d, Misses: %d, Hit/Miss ratio: %.2f\n", hits, misses, (double)hits / misses);

  free(PAGE_TABLE);
  return 0;
}
