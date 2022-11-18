#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

// List all the files in the current directory
int main(int argc, char *argv[]) {
  DIR *dir = opendir(".");
  struct dirent *entry;
  
  if (dir == NULL) {
    perror("opendir");
    exit(1);
  }
  
  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_name[0] != '.') {
      printf("%s\n", entry->d_name);
    }
  }
  
  closedir(dir);
  return 0;
}
