#include <stdio.h>

int main() {
    int n = 3;

    int arrival[3] = {0, 0, 0};
    int burst[3]   = {3, 2, 2};
    int deadline[3]= {7, 4, 8};
    int period[3]  = {20, 5, 10};

    int remaining[3];
    for (int i = 0; i < n; i++)
        remaining[i] = burst[i];

    printf("PID\tBurst\tDeadline\tPeriod\n");
    printf("2\t2\t4\t\t5\n");
    printf("1\t3\t7\t\t20\n");
    printf("3\t2\t8\t\t10\n");

    int hyperperiod = 20;
    printf("Scheduling occurs for %d ms\n\n", hyperperiod);

    for (int time = 0; time < hyperperiod; time++) {

        for (int i = 0; i < n; i++) {
            if (time % period[i] == 0) {
                remaining[i] = burst[i];
            }
        }

        int min_deadline = 100000;
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining[i] > 0) {
                if (deadline[i] < min_deadline) {
                    min_deadline = deadline[i];
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            printf("%dms : CPU is idle.\n", time);
        } else {
            printf("%dms : Task %d is running.\n", time, selected + 1);
            remaining[selected]--;
        }
    }

    return 0;
}
