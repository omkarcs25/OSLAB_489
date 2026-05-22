#include <stdio.h>

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rem_bt[n];
    int wt[n], tat[n], rt[n];
    int first_exec[n];

    printf("Enter Arrival Time and Burst Time:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d AT BT: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rem_bt[i] = bt[i];
        first_exec[i] = -1;  // for response time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;

    // Gantt chart storage
    int gantt[100], gtime[100], gindex = 0;

    while (completed < n) {
        int executed = 0;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rem_bt[i] > 0) {

                // First response time
                if (first_exec[i] == -1) {
                    first_exec[i] = time;
                    rt[i] = time - at[i];
                }

                executed = 1;

                gantt[gindex] = i;
                gtime[gindex] = time;
                gindex++;

                if (rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                } else {
                    time += rem_bt[i];
                    wt[i] = time - at[i] - bt[i];
                    rem_bt[i] = 0;
                    completed++;
                }
            }
        }

        // CPU idle case
        if (!executed) {
            time++;
        }
    }

    // Last time for Gantt
    gtime[gindex] = time;

    // Turnaround Time
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }

    // Display Gantt Chart
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gindex; i++) {
        printf(" P%d |", gantt[i] + 1);
    }

    printf("\n0");
    for (int i = 0; i < gindex; i++) {
        printf("   %d", gtime[i + 1]);
    }

    // Table Output
    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("\n\nProcess\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], wt[i], tat[i], rt[i]);

        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt[i];
    }

    printf("\nAverage WT = %.2f", total_wt / n);
    printf("\nAverage TAT = %.2f", total_tat / n);
    printf("\nAverage RT = %.2f\n", total_rt / n);

    return 0;
}
