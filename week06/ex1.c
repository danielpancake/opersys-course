#include <stdio.h>
#include <stdlib.h>

typedef struct Metrics {
  int id;
  int arrival_time;
  int burst_time;
  int completion_time;
  int turn_around_time;
  int waiting_time;
} Metrics;

int main() {
  int n;
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  Metrics metrics[n];

  for (int i = 0; i < n; i++) {
    metrics[i].id = i;

    printf("Enter the arrival time for process %d: ", i + 1);
    scanf("%d", &metrics[i].arrival_time);
    printf("Enter the burst time for process %d: ", i + 1);
    scanf("%d", &metrics[i].burst_time);
    putchar('\n');

    // Online sorting by arrival time
    for (int j = i; j > 0; j--) {
      if (metrics[j].arrival_time < metrics[j - 1].arrival_time) {
        Metrics temp = metrics[j];
        metrics[j] = metrics[j - 1];
        metrics[j - 1] = temp;
      }
    }
  }

  int current_time = 0, total_turn_around_time = 0, total_waiting_time = 0;

  for (int i = 0; i < n; i++) {
    Metrics *m = &metrics[i];

    m->completion_time = current_time + m->burst_time;
    m->turn_around_time = m->completion_time - m->arrival_time;
    m->waiting_time = m->turn_around_time - m->burst_time;

    current_time = m->completion_time;

    total_turn_around_time += m->turn_around_time;
    total_waiting_time += m->waiting_time;
  }

  printf("Job #\tAT\tBT\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++) {
    Metrics *m = &metrics[i];
    
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", m->id + 1,
           m->arrival_time,
           m->burst_time,
           m->completion_time,
           m->turn_around_time,
           m->waiting_time);
  }

  putchar('\n');

  printf("Average Turnaround time: %f\n", (float)total_turn_around_time / n);
  printf("Average waiting time: %f\n", (float)total_waiting_time / n);

  return 0;
}
