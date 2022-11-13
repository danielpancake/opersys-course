#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct file {
  char *name;
  unsigned long int inode;
};

int main() {
  DIR *dir = opendir("./tmp");

  if (!dir) {                            // If tmp does not exist
    int tmp_dir = mkdir("./tmp", 0700);  // Create tmp directory
    if (tmp_dir == -1) {
      perror("mkdir");
      exit(1);
    } else {
      dir = opendir("./tmp");
    }
  }

  // Creating two empty files
  FILE *file1 = fopen("./tmp/file1", "w");
  FILE *file2 = fopen("./tmp/file2", "w");

  // Creating a hard link named link1 to file1
  int link1 = link("./tmp/file1", "./tmp/link1");

  struct dirent *entry;
  struct stat fileStat;

  int files_count = 0;
  int max_files = 1;
  struct file *files = malloc(max_files * sizeof(struct file));

  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    char *path = malloc(strlen(entry->d_name) + 6);
    strcpy(path, "./tmp/");
    strcat(path, entry->d_name);

    if (stat(path, &fileStat) < 0) {
      perror("stat");
      exit(1);
    }

    if (fileStat.st_nlink >= 2) {
      if (files_count == max_files) {
        max_files *= 2;
        files = realloc(files, max_files * sizeof(struct file));
      }

      files[files_count].name = malloc(strlen(entry->d_name) + 1);
      strcpy(files[files_count].name, entry->d_name);
      files[files_count].inode = fileStat.st_ino;
      files_count++;
    }

    free(path);
  }

  // Print the names of the files and their hard links
  printf("File\t-----\tHard Links\n");

  for (int i = 0; i < files_count; i++) {
    printf("%s\t-----\t", files[i].name);

    for (int j = 0; j < files_count; j++) {
      if (files[i].inode == files[j].inode) {
        printf("%s", files[j].name);

        if (j != files_count - 1) {
          printf(", ");
        }
      }
    }
    printf("\n");
  }

  fclose(file1);
  fclose(file2);
  closedir(dir);

  return 0;
}
