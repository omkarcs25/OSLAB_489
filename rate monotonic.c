#include <stdio.h>

struct Process {
    int id;
    int burst;
    int period;
    int remaining;
};

int main() {

    int n, i, time;
    int hyperperiod = 20;

    struct Process p[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for(i = 0; i < n; i++) {

        p[i].id = i + 1;

        printf("\nProcess P%d\n", i + 1);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].burst);

        printf("Enter Period: ");
        scanf("%d", &p[i].period);

        p[i].remaining = 0;
    }

    printf("\nRate Monotonic Scheduling Execution:\n");

    printf("\nGantt Chart:\n|");

    // Simulation
    for(time = 0; time < hyperperiod; time++) {

        // Release periodic tasks
        for(i = 0; i < n; i++) {

            if(time % p[i].period == 0) {
                p[i].remaining = p[i].burst;
            }
        }

        int selected = -1;
        int highest_priority = 9999;

        // RMS: smaller period = higher priority
        for(i = 0; i < n; i++) {

            if(p[i].remaining > 0 &&
               p[i].period < highest_priority) {

                highest_priority = p[i].period;
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

    // Timeline
    printf("\n0");

    for(time = 1; time <= hyperperiod; time++) {
        printf("    %d", time);
    }

    printf("\n");

    return 0;
}
