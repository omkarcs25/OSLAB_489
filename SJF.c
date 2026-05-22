#include<stdio.h>

int main()
{
    int n,i,choice;
    int at[20],bt[20],ct[20]={0},tat[20],wt[20],rt[20];
    int rt_rem[20];
    int time,completed,min,index;
    float avgwt=0,avgtat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("Enter AT and BT for P%d: ",i+1);
        scanf("%d%d",&at[i],&bt[i]);
        rt_rem[i]=bt[i];
    }

    printf("\n1. SJF Non Preemptive");
    printf("\n2. SJF Preemptive");
    printf("\nEnter choice: ");
    scanf("%d",&choice);

    switch(choice)
    {

    // NON PREEMPTIVE SJF
    case 1:

        completed=0;
        time=0;

        while(completed<n)
        {
            min=9999;
            index=-1;

            for(i=0;i<n;i++)
            {
                if(at[i]<=time && ct[i]==0 && bt[i]<min)
                {
                    min=bt[i];
                    index=i;
                }
            }

            if(index!=-1)
            {
                time+=bt[index];
                ct[index]=time;

                tat[index]=ct[index]-at[index];
                wt[index]=tat[index]-bt[index];
                rt[index]=wt[index];

                avgwt+=wt[index];
                avgtat+=tat[index];

                completed++;
            }
            else
            {
                time++;
            }
        }

        break;


    // PREEMPTIVE SJF (SRTF)
    case 2:

        completed=0;
        time=0;

        int started[20]={0};

        while(completed<n)
        {
            min=9999;
            index=-1;

            for(i=0;i<n;i++)
            {
                if(at[i]<=time && rt_rem[i]>0 && rt_rem[i]<min)
                {
                    min=rt_rem[i];
                    index=i;
                }
            }

            if(index!=-1)
            {
                if(started[index]==0)
                {
                    rt[index]=time-at[index];
                    started[index]=1;
                }

                rt_rem[index]--;
                time++;

                if(rt_rem[index]==0)
                {
                    ct[index]=time;

                    tat[index]=ct[index]-at[index];
                    wt[index]=tat[index]-bt[index];

                    avgwt+=wt[index];
                    avgtat+=tat[index];

                    completed++;
                }
            }
            else
            {
                time++;
            }
        }

        break;

    default:
        printf("Invalid Choice");
        return 0;
    }

    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],ct[i],tat[i],wt[i],rt[i]);
    }

    printf("\nAverage WT = %.2f",avgwt/n);
    printf("\nAverage TAT = %.2f\n",avgtat/n);

    return 0;
}
