#include <stdio.h>

int main() {
    int n;
    printf("Enter total number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], wt[n], tat[n], rt[n];
    int type[n]; // 1 = System, 2 = User
    int completed[n];

    // Input
    for (int i = 0; i < n; i++) {
        printf("P%d AT BT Type(1-System,2-User): ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &type[i]);
        completed[i] = 0;
    }

    int time = 0, done = 0;

    // Gantt Chart arrays
    int gantt[100], gtime[100], gindex = 0;

    while (done < n) {
        int idx = -1;

        // Step 1: Find SYSTEM process (higher priority)
        for (int i = 0; i < n; i++) {
            if (completed[i] == 0 && at[i] <= time && type[i] == 1) {
                idx = i;
                break;
            }
        }

        // Step 2: If no system process, find USER process
        if (idx == -1) {
            for (int i = 0; i < n; i++) {
                if (completed[i] == 0 && at[i] <= time && type[i] == 2) {
                    idx = i;
                    break;
                }
            }
        }

        // Step 3: Execute process
        if (idx != -1) {

            // Gantt chart entry
            gantt[gindex] = idx;
            gtime[gindex] = time;
            gindex++;

            // Response Time (same as WT here)
            rt[idx] = time - at[idx];

            // Waiting Time
            wt[idx] = rt[idx];

            // Execute process
            time += bt[idx];

            // Turnaround Time
            tat[idx] = bt[idx] + wt[idx];

            completed[idx] = 1;
            done++;
        }
        else {
            time++; // CPU idle
        }
    }

    gtime[gindex] = time;

    // ===== Gantt Chart =====
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gindex; i++) {
        printf(" P%d |", gantt[i] + 1);
    }

    printf("\n0");
    for (int i = 0; i < gindex; i++) {
        printf("   %d", gtime[i + 1]);
    }

    // ===== Output =====
    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("\n\nProcess\tAT\tBT\tType\tWT\tTAT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%s\t%d\t%d\t%d\n",
               i + 1,
               at[i],
               bt[i],
               (type[i] == 1) ? "SYS" : "USR",
               wt[i],
               tat[i],

        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt[i];
    }

    printf("\nAverage WT = %.2f", total_wt / n);
    printf("\nAverage TAT = %.2f", total_tat / n);
    printf("\nAverage RT = %.2f\n", total_rt / n);

    return 0;
}
