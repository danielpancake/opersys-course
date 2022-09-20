#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char __IDCounter = 0;

struct Directory;
struct File;

struct File {
  unsigned char id;  // 0-255
  char name[64];
  long unsigned int size;
  char data[1024];

  // The parent directory
  struct Directory *directory;
};

struct Directory {
  struct File **files;
  struct Directory *directories[8];

  unsigned char nf;
  unsigned char nd;
  char path[2048];
};

typedef struct Directory Directory;
typedef struct File File;

/* Operations on files */
File *create_file(char *name);
void add_to_file(File *file, const char *content);
void append_to_file(File *file, const char *content);
void pwd_file(File *file);

/* Operations on directories */
Directory *create_directory(char *name);
void add_file(File *file, Directory *dir);
void add_dir(Directory *dir1, Directory *dir2);

/* Helper functions */
void show_dir(Directory *dir);
void show_file(File *file);
void show_file_detailed(File *file);

int main() {
  char bash_content[] = "Bourne Again Shell!";
  char ex3_1_content_1[] = "int printf(const char * format, ...);";
  char ex3_1_content_2[] = "int main(){printf('Hello World');}";
  char ex3_2_content[] = "//This is a comment in C language";

  Directory *home, *bin, *root;
  home = create_directory("home");
  bin = create_directory("bin");
  root = create_directory("");

  // Add subdirectories
  add_dir(home, root);
  add_dir(bin, root);

  File *bash, *ex3_1, *ex3_2;
  bash = create_file("bash");
  ex3_1 = create_file("ex3_1.c");
  ex3_2 = create_file("ex3_2.c");

  add_file(bash, bin);
  add_file(ex3_1, home);
  add_file(ex3_2, home);

  // Add content to files
  add_to_file(bash, bash_content);
  add_to_file(ex3_1, ex3_1_content_1);
  add_to_file(ex3_2, ex3_2_content);

  append_to_file(ex3_1, ex3_1_content_2);

  show_dir(root);
  show_file_detailed(bash);
  show_file_detailed(ex3_1);
  show_file_detailed(ex3_2);

  pwd_file(bash);
  pwd_file(ex3_1);
  pwd_file(ex3_2);

  return EXIT_SUCCESS;
}

// Implementation: Operations on files

// Creates a file with the given name
File *create_file(char *name) {
  File *file = (File *)malloc(sizeof(File));
  file->id = __IDCounter++;
  strcpy(file->name, name);
  file->size = 0;
  strcpy(file->data, "");
  file->directory = NULL;
  return file;
}

// Adds the content to the File file
void add_to_file(File *file, const char *content) {
  file->size = 1 + strlen(content) * sizeof(char);
  strcpy(file->data, content);
}

// Appends the content to the File file
void append_to_file(File *file, const char *content) {
  file->size += strlen(content) * sizeof(char);
  strcat(file->data, content);
}

// Prints the path of the File file
void pwd_file(File *file) {
  printf("The path for %s file is %s%s\n", file->name, file->directory->path, file->name);
}

// Implementation: Operations on directories
// Creates a directory with the given name
Directory *create_directory(char *name) {
  Directory *dir = (Directory *)malloc(sizeof(Directory));
  dir->files = (File **)malloc(sizeof(File *) * 8);
  dir->nf = 0;
  dir->nd = 0;
  strcpy(dir->path, "/");
  strcat(dir->path, name);
  return dir;
}

// Adds the File file to the Directory dir
void add_file(File *file, Directory *dir) {
  file->directory = dir;
  dir->files = realloc(dir->files, (dir->nf + 1) * sizeof(File *));
  dir->files[dir->nf] = file;
  dir->nf++;
}

// Adds the subdirectory dir1 to the directory dir2
void add_dir(Directory *dir1, Directory *dir2) {
  if (dir1 && dir2) {
    strcat(dir1->path, dir2->path);
    dir2->directories[dir2->nd] = dir1;
    dir2->nd++;
  }
}

// Helper functions
char *repeat(size_t n, char c) {
  char *result = malloc(n + 1);
  char *p = result;
  for (size_t i = 0; i < n; i++) {
    p += sprintf(p, "%c", c);
  }
  return result;
}

// Prints the content of the Directory dir with the given depth of indentation
void show_dir_helper(Directory *dir, unsigned int depth) {
  char *indent = repeat(depth, '\t');

  printf("%s%s", indent, dir->path);
  printf(" ----- (%d files, %d directories)\n", dir->nf, dir->nd);

  if (dir->nf > 0) {
    printf("%s   Files: [ ", indent);
    for (int i = 0; i < dir->nf; i++) {
      show_file(dir->files[i]);
    }
    printf("]\n");
  }

  if (dir->nd > 0) {
    printf("%s   Directories:\n", indent);
    for (int i = 0; i < dir->nd; i++) {
      show_dir_helper(dir->directories[i], depth + 1);
    }
    printf("\n");
  }

  free(indent);
}

// Displays the content of the Directory dir
void show_dir(Directory *dir) {
  show_dir_helper(dir, 0);
}

// Prints the name of the File file
void show_file(File *file) {
  printf("%s ", file->name);
}

// Shows details of the File file
void show_file_detailed(File *file) {
  printf("FILE ----- %s\n", file->name);
  printf("   ID: %d\n", file->id);
  printf("   Size: %ld bytes\n", file->size);
  printf("   Content: [ %s ]\n\n", file->data);
}
