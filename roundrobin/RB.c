#include <stdio.h>

int main() {
    printf("Name : UPPALURI BALAJI REDDY\nUSN : 1BF24CS323\n\n");
    int n, tq;
    int at[100], bt[100], rt[100];
    int wt[100], tat[100], ct[100];
    int queue[100], front = 0, rear = 0;
    int visited[100] = {0};
    int time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    printf("Enter Arrival time and Burst time of processes  (AT BT) \n ");
    for(int j=0;j<n;j++){
            printf("Process %d \n",j+1);
        scanf("%d%d",&at[j],&bt[j]);
        rt[j]=bt[j];
    }

    for(int i = 0; i < n; i++) {
        if(at[i] <= time && visited[i] == 0) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while(completed < n) {

        if(front == rear) {
            time++;
            for(int i = 0; i < n; i++) {
                if(at[i] <= time && visited[i] == 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int p = queue[front++];

        if(rt[p] > tq) {
            time += tq;
            rt[p] -= tq;
        } else {
            time += rt[p];
            rt[p] = 0;

            ct[p] = time;
            tat[p] = ct[p] - at[p];
            wt[p] = tat[p] - bt[p];

            completed++;
        }

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && visited[i] == 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if(rt[p] > 0) {
            queue[rear++] = p;
        }
    }

    float avg_wt = 0, avg_tat = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}
