#include <stdio.h>

struct Process {
    int id;
    int burst;
    int period;
    int remaining;
    int next_deadline;
};

int main() {
    int n, i, time, hyperperiod = 20;

    struct Process p[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for(i = 0; i < n; i++) {

        p[i].id = i + 1;

        printf("\nProcess P%d\n", i + 1);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].burst);

        printf("Enter Period/Deadline: ");
        scanf("%d", &p[i].period);

        p[i].remaining = 0;
        p[i].next_deadline = p[i].period;
    }

    printf("\nEDF Scheduling Execution:\n\n");

    // Gantt Chart
    printf("Gantt Chart:\n|");

    // Simulate EDF scheduling
    for(time = 0; time < hyperperiod; time++) {

        // Release tasks periodically
        for(i = 0; i < n; i++) {

            if(time % p[i].period == 0) {
                p[i].remaining = p[i].burst;
                p[i].next_deadline = time + p[i].period;
            }
        }

        int selected = -1;
        int earliest = 9999;

        // Select process with earliest deadline
        for(i = 0; i < n; i++) {

            if(p[i].remaining > 0 &&
               p[i].next_deadline < earliest) {

                earliest = p[i].next_deadline;
                selected = i;
            }
        }

        // Execute selected process
        if(selected != -1) {

            printf(" P%d |", p[selected].id);

            p[selected].remaining--;
        }
        else {
            printf(" Idle |");
        }
    }

    // Time line
    printf("\n0");

    for(time = 1; time <= hyperperiod; time++) {
        printf("    %d", time);
    }

    printf("\n");

    return 0;
}
