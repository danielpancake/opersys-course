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
  char done;
  Metrics metrics;
} Process;

int main() {
  int n;
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  Process processes[n];

  for (int i = 0; i < n; i++) {
    processes[i].id = i;
    processes[i].done = 0;

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

  int current_time = 0, done_processes = 0, total_turn_around_time = 0, total_waiting_time = 0;

  while (done_processes < n) {
    int min = __INT_MAX__, min_index = -1;

    for (int i = 0; i < n; i++) {
      if (processes[i].arrival_time <= current_time && !processes[i].done) {
        if (processes[i].burst_time < min) {
          min = processes[i].burst_time;
          min_index = i;
        }
      }
    }

    if (min_index != -1) {
      Process *p = &processes[min_index];
      p->done = 1;

      p->metrics.completion_time = current_time + p->burst_time;
      p->metrics.turn_around_time = p->metrics.completion_time - p->arrival_time;
      p->metrics.waiting_time = p->metrics.turn_around_time - p->burst_time;

      total_turn_around_time += p->metrics.turn_around_time;
      total_waiting_time += p->metrics.waiting_time;

      current_time = p->metrics.completion_time;

      ++done_processes;
    } else {
      current_time = processes[done_processes].arrival_time;
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
