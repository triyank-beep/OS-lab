#include <stdio.h>

struct Process {
    int pid, at, bt, pri, ct, tat, wt, done;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        printf("\nProcess ID: ");
        scanf("%d", &p[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Priority: ");
        scanf("%d", &p[i].pri);
        p[i].done = 0;
    }

    int time = 0, count = 0;

    while (count < n) {
        int sel = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].done) {
                if (sel == -1 || p[i].pri < p[sel].pri)
                    sel = i;
            }
        }

        if (sel == -1) {
            time++;
        } else {
            p[sel].ct  = time + p[sel].bt;
            p[sel].tat = p[sel].ct - p[sel].at;
            p[sel].wt  = p[sel].tat - p[sel].bt;
            time = p[sel].ct;
            p[sel].done = 1;
            count++;
        }
    }

    printf("\nPID  AT  BT  PRI  CT  TAT  WT\n");
    printf("-------------------------------\n");
    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        printf("%3d %3d %3d %4d %4d %4d %4d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pri, p[i].ct, p[i].tat, p[i].wt);
        avg_wt  += p[i].wt;
        avg_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);
    printf("Average Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}
