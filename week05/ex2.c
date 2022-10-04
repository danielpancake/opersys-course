#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

struct Thread {
  int i;
  pthread_t id;
  char message[256];
};

void *thread_function(void *arg) {
  struct Thread *thread = (struct Thread *)arg;
  printf("Thread %d, id: %lu, message: %s\n", thread->i, thread->id, thread->message);
  putchar('\n');
  pthread_exit(NULL);
}

int main() {
  int n;
  printf("Enter the number of threads: ");
  scanf("%d", &n);

  struct Thread threads[n];

  for (int i = 0; i < n; ++i) {
    threads[i].i = i;
    sprintf(threads[i].message, "Hello from thread %d", i);
    pthread_create(&threads[i].id, NULL, thread_function, &threads[i]);
    printf("Thread %d is created\n", i);
    usleep(1);
  }

  for (int i = 0; i < n; ++i) {
    pthread_join(threads[i].id, NULL);
  }

  return 0;
}
