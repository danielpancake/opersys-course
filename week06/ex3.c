#include <stdio.h>
#include <stdlib.h>

typedef struct Metrics {
  int completion_time;
  int turn_around_time;
  int waiting_time;
} Metrics;

typedef struct Process {
  int id;
  int arrival_time;
  int burst_time;
  int elapsed_time;
  Metrics metrics;
} Process;

typedef struct Queue {
  int *values;
  int size;
} Queue;

Queue *create_queue(int size) {
  Queue *queue = malloc(sizeof(Queue));
  queue->values = malloc(sizeof(int) * size);
  queue->size = 0;
  return queue;
}

void enqueue(Queue *queue, int value) {
  queue->values[queue->size++] = value;
}

int dequeue(Queue *queue) {
  int value = queue->values[0];
  for (int i = 0; i < queue->size - 1; i++) {
    queue->values[i] = queue->values[i + 1];
  }
  queue->size--;
  return value;
}

int main() {
  int n, quantum;
  printf("Enter the number of processes: ");
  scanf("%d", &n);
  printf("Enter the quantum: ");
  scanf("%d", &quantum);

  Process *processes = malloc(n * sizeof(Process));

  for (int i = 0; i < n; i++) {
    processes[i].id = i;
    processes[i].elapsed_time = -1;
    processes[i].metrics = (Metrics){0, 0, 0};

    printf("Enter the arrival time for process %d: ", i + 1);
    scanf("%d", &processes[i].arrival_time);
    printf("Enter the burst time for process %d: ", i + 1);
    scanf("%d", &processes[i].burst_time);
    putchar('\n');

    // Online sorting by arrival time
    for (int j = i; j > 0; j--) {
      if (processes[j].arrival_time < processes[j - 1].arrival_time) {
        Process temp = processes[j];
        processes[j] = processes[j - 1];
        processes[j - 1] = temp;
      }
    }
  }

  Queue *queue = create_queue(n);
  int current_time = 0, done_processes = 0, total_turn_around_time = 0, total_waiting_time = 0;
  int index = -1;

  while (done_processes < n) {
    // Add processes to the queue
    for (int i = 0; i < n; i++) {
      if (processes[i].arrival_time <= current_time && processes[i].elapsed_time == -1) {
        processes[i].elapsed_time = 0;
        enqueue(queue, i);
      }
    }

    if (index != -1) {
      enqueue(queue, index);
      index = -1;
    } else if (queue->size == 0) {
      ++current_time;
      continue;
    }

    // Execute the first process in the queue
    index = dequeue(queue);
    Process *p = &processes[index];

    p->elapsed_time += quantum;
    current_time += quantum;

    if (p->elapsed_time >= p->burst_time) {
      p->metrics.completion_time = current_time - (p->elapsed_time - p->burst_time);
      p->metrics.turn_around_time = p->metrics.completion_time - p->arrival_time;
      p->metrics.waiting_time = p->metrics.turn_around_time - p->burst_time;

      total_turn_around_time += p->metrics.turn_around_time;
      total_waiting_time += p->metrics.waiting_time;

      current_time = p->metrics.completion_time;

      ++done_processes;
      index = -1;
    }
  }

  printf("Job #\tAT\tBT\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++) {
    Process *p = &processes[i];
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", p->id + 1,
           p->arrival_time,
           p->burst_time,
           p->metrics.completion_time,
           p->metrics.turn_around_time,
           p->metrics.waiting_time);
  }

  putchar('\n');

  printf("Average Turnaround time: %f\n", (float)total_turn_around_time / n);
  printf("Average waiting time: %f\n", (float)total_waiting_time / n);

  return 0;
}
