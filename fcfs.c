#include <stdio.h>

int main() {
    int n, i;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], wt[n], tat[n], ct[n];

    for(i = 0; i < n; i++) {
        printf("\nEnter Arrival Time for P%d: ", i + 1);
        scanf("%d", &at[i]);

        printf("Enter Burst Time for P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Completion Time
    ct[0] = at[0] + bt[0];

    for(i = 1; i < n; i++) {

        if(ct[i-1] < at[i])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i-1] + bt[i];
    }

    // WT and TAT
    for(i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    // Table
    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    // Gantt Chart
    printf("\nGantt Chart:\n");

    printf("%d", at[0]);

    for(i = 0; i < n; i++) {
        printf(" ---P%d--- %d", i + 1, ct[i]);
    }

    return 0;
}
