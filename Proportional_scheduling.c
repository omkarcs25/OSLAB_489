#include <stdio.h>

struct Process {
    int pid;
    int burst;
    int deadline;
};

int main() {
    int n, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n], temp;

    // Input
    for(i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("\nEnter Burst Time for P%d: ", i + 1);
        scanf("%d", &p[i].burst);

        printf("Enter Deadline for P%d: ", i + 1);
        scanf("%d", &p[i].deadline);
    }

    // EDF Scheduling (sort by deadline)
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {

            if(p[i].deadline > p[j].deadline) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time = 0;

    printf("\nProcess\tBurst\tDeadline\tCompletion\n");

    for(i = 0; i < n; i++) {
        time += p[i].burst;

        printf("P%d\t%d\t%d\t\t%d\n",
               p[i].pid,
               p[i].burst,
               p[i].deadline,
               time);
    }

    // Gantt Chart
    printf("\nGantt Chart:\n");

    time = 0;

    printf("0");

    for(i = 0; i < n; i++) {
        time += p[i].burst;

        printf(" ---P%d--- %d", p[i].pid, time);
    }

    return 0;
}
