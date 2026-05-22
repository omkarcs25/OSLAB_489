#include<stdio.h>

int main()
{
    int n,i,time=0,completed=0;
    int at[20],bt[20],pr[20];
    int ct[20]={0},tat[20],wt[20],rt[20];
    int min,index;
    float avgwt=0,avgtat=0;

    int gantt_p[50],gantt_t[50],g=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("Enter AT, BT and Priority for P%d: ",i+1);
        scanf("%d%d%d",&at[i],&bt[i],&pr[i]);
    }

    while(completed<n)
    {
        min=9999;
        index=-1;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && ct[i]==0 && pr[i]<min)
            {
                min=pr[i];
                index=i;
            }
        }

        if(index!=-1)
        {
            gantt_p[g]=index+1;
            gantt_t[g]=time;
            g++;

            rt[index]=time-at[index];

            time+=bt[index];

            ct[index]=time;

            tat[index]=ct[index]-at[index];

            wt[index]=tat[index]-bt[index];

            avgwt+=wt[index];
            avgtat+=tat[index];

            completed++;
        }
        else
        {
            time++;
        }
    }

    gantt_t[g]=time;

    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],pr[i],ct[i],tat[i],wt[i],rt[i]);
    }

    printf("\nAverage WT = %.2f",avgwt/n);
    printf("\nAverage TAT = %.2f\n",avgtat/n);

    printf("\nGantt Chart:\n|");

    for(i=0;i<g;i++)
        printf(" P%d |",gantt_p[i]);

    printf("\n%d",gantt_t[0]);

    for(i=1;i<=g;i++)
        printf("    %d",gantt_t[i]);

    printf("\n");

    return 0;
}
