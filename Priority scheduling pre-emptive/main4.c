#include <stdio.h>

int main()
{
    int n,i,time=0,completed=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int at[n],bt[n],pr[n],rt[n];
    int ct[n],tat[n],wt[n];

    printf("\nEnter AT BT Priority for each process\n");

    for(i=0;i<n;i++)
    {
        printf("P%d: ",i+1);
        scanf("%d %d %d",&at[i],&bt[i],&pr[i]);
        rt[i]=bt[i];
    }

    float total_wt=0,total_tat=0;

    while(completed<n)
    {
        int sel=-1;
        int hp=9999;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && rt[i]>0)
            {
                if(pr[i]<hp)
                {
                    hp=pr[i];
                    sel=i;
                }
            }
        }

        if(sel==-1)
        {
            time++;
            continue;
        }

        rt[sel]--;
        time++;

        if(rt[sel]==0)
        {
            ct[sel]=time;
            tat[sel]=ct[sel]-at[sel];
            wt[sel]=tat[sel]-bt[sel];

            total_wt+=wt[sel];
            total_tat+=tat[sel];
            completed++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],pr[i],ct[i],tat[i],wt[i]);
    }

    printf("\nAverage TAT = %.2f",total_tat/n);
    printf("\nAverage WT = %.2f\n",total_wt/n);

    return 0;
}
