#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { false,
               true } bool;

int max(int a, int b) {
  return a > b ? a : b;
}

typedef struct matrix {
  int* data;
  int rows;
  int cols;
} matrix;

matrix* matrix_create(int rows, int cols) {
  matrix* m = malloc(sizeof(matrix));
  m->data = calloc(rows * cols, sizeof(int));
  m->rows = rows;
  m->cols = cols;
  return m;
}

void free_matrix(matrix* m) {
  free(m->data);
  free(m);
}

void matrix_add(matrix* m, int row, int col, int value) {
  if (row < 0 || col < 0) {
    printf("Invalid row or column number!\n");
    return;
  }

  if (row >= m->rows || col >= m->cols) {
    int new_rows = max(row + 1, m->rows);
    int new_cols = max(col + 1, m->cols);
    matrix* temp = matrix_create(new_rows, new_cols);
    for (int i = 0; i < m->rows; i++) {
      for (int j = 0; j < m->cols; j++) {
        temp->data[i * temp->cols + j] = m->data[i * m->cols + j];
      }
    }

    temp->data[row * temp->cols + col] = value;
    free(m->data);

    m->data = temp->data;
    m->rows = temp->rows;
    m->cols = temp->cols;
    free(temp);
  } else {
    m->data[row * m->cols + col] = value;
  }
}

int matrix_get_with_default(matrix* m, int row, int col, int default_value) {
  if (row < 0 || col < 0 || row >= m->rows || col >= m->cols) {
    return default_value;
  }
  return m->data[row * m->cols + col];
}

void print_matrix(matrix* m) {
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      printf("%d ", m->data[i * m->cols + j]);
    }
    printf("\n");
  }
}

matrix* line_to_numbers(char* line) {
  matrix* arr = matrix_create(0, 0);

  char* token = strtok(line, " ");
  while (token != NULL) {
    char* endptr = NULL;
    int num = strtol(token, &endptr, 10);

    if (token != endptr) {
      matrix_add(arr, 0, arr->cols, num);
    }

    token = strtok(NULL, " ");
  }

  return arr;
}

typedef struct {
  matrix** data;
  int size;
  int capacity;
} matrix_array;

matrix_array* create_matrix_array() {
  matrix_array* arr = malloc(sizeof(matrix_array));
  arr->data = malloc(sizeof(matrix*));
  arr->size = 0;
  arr->capacity = 1;
  return arr;
}

void free_matrix_array(matrix_array* arr) {
  for (int i = 0; i < arr->size; i++) {
    free_matrix(arr->data[i]);
  }
  free(arr->data);
  free(arr);
}

matrix_array* parse_file(char* filename) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  matrix_array* arr = create_matrix_array();
  char* line = NULL;
  bool separator = 0;  // whether separator was found
  size_t current = 0;

  ssize_t read;
  size_t len = 0;

  /* Reading numbers line by line. Consequent lines of number will be merged into a single matrix */
  while ((read = getline(&line, &len, fp)) != -1) {
    matrix* m = line_to_numbers(line);

    // If non-empty line was read, add it
    if (m->rows > 0 && m->cols > 0) {
      if (separator == true) {
        arr->size++;

        if (arr->size == arr->capacity) {
          arr->capacity *= 2;
          arr->data = realloc(arr->data, arr->capacity * sizeof(matrix*));
        }

        separator = false;
      }

      if (arr->data[arr->size] == NULL) {
        arr->data[arr->size] = matrix_create(0, 0);
      }

      int old_rows = arr->data[arr->size]->rows;
      for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
          matrix_add(arr->data[arr->size], old_rows + i, j, m->data[i * m->cols + j]);
        }
      }
    } else {
      separator = true;
    }

    free(m->data);
    free(m);
  }

  // Add last matrix
  if (arr->data[arr->size] != NULL) {
    arr->size++;
  }

  if (line) {
    free(line);
  }
  fclose(fp);

  return arr;
}

int main() {
  matrix_array* in = parse_file("input.txt");

  if (in->size == 0) {
    printf("No matrices found!\n");
    free_matrix_array(in);
    return 0;
  }

  if (in->size != 4) {
    printf("Invalid number of matrices in the input file! Expected 4, got %d\n", in->size);
    free_matrix_array(in);
    return 0;
  }

  matrix* E = in->data[0];  // Existing resources
  matrix* A = in->data[1];  // Available resources
  matrix* C = in->data[2];  // Current allocation
  matrix* R = in->data[3];  // Request

  // Check all matrices for negative elements
  for (int i = 0; i < in->size; i++) {
    matrix* m = in->data[i];
    for (int j = 0; j < m->rows * m->cols; j++) {
      if (m->data[j] < 0) {
        printf("Negative element %d found in matrix %d!\n", m->data[j], i);
        free_matrix_array(in);
        return 0;
      }
    }
  }

  // Check if matrices are valid
  for (int j = 0; j < C->cols; j++) {
    // If dimensions are not equal, assuming zero
    int exists = matrix_get_with_default(E, 0, j, 0);
    int available = matrix_get_with_default(A, 0, j, 0);
    int allocated = 0;

    for (int i = 0; i < C->rows; i++) {
      allocated += C->data[i * C->cols + j];
    }

    if (allocated > exists) {
      printf("Invalid input! Current allocation for resources of class %d exceeds the existing amount.\nAllocated: %d, exists: %d.\n",
             j, allocated, exists);
      free_matrix_array(in);
      return 0;
    } else if (allocated + available != exists) {
      printf(
          "Invalid input! Current allocation for resources of class %d is not valid.\nAllocated: %d, exists: %d, however, %d available.\n",
          j, allocated, exists, available);
      free_matrix_array(in);
      return 0;
    }
  }

  bool* done_processes = calloc(C->rows, sizeof(bool));
  int still_running = C->rows;

  bool deadlock = false;

  while (still_running > 0) {
    deadlock = true;

    for (int i = 0; i < C->rows; i++) {
      if (done_processes[i] == 1) {
        continue;
      }

      bool can_finish = true;
      for (int j = 0; j < R->cols; j++) {
        if (R->data[i * R->cols + j] > A->data[j]) {
          can_finish = false;
          break;
        }
      }

      if (can_finish) {
        for (int j = 0; j < R->cols; j++) {
          A->data[j] += C->data[i * C->cols + j];
        }
        done_processes[i] = true;
        deadlock = false;
        still_running--;
      }
    }

    if (deadlock) {
      printf("Deadlock state of %d processes detected:\n", still_running);

      // Print processes that are still running
      int printed = 0;
      for (int i = 0; i < C->rows; i++) {
        if (done_processes[i] == 0) {
          printf("P%d", i);
          printed++;
          if (printed < still_running) {
            printf(", ");
          }
        }
      }
      printf("\n");
      break;
    }
  }

  if (!deadlock) {
    printf("No deadlock is detected!\n");
  }

  free_matrix_array(in);
  free(done_processes);

  return 0;
}
