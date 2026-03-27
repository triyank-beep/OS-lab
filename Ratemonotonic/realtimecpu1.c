#include <stdio.h>
#include <math.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    int n;
    printf("Enter the number of processes:");
    scanf("%d", &n);

    int C[n], P[n];

    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &C[i]);
    }

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &P[i]);
    }

    int hyper = P[0];
    for (int i = 1; i < n; i++) {
        hyper = lcm(hyper, P[i]);
    }

    printf("LCM=%d\n\n", hyper);

    printf("Rate Monotone Scheduling:\n");
    printf("PID\tBurst\tPeriod\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", i + 1, C[i], P[i]);
    }

    float utilization = 0;
    for (int i = 0; i < n; i++) {
        utilization += (float)C[i] / P[i];
    }

    float bound;
    if (n == 2)
        bound = 0.828427;
    else
        bound = n * (pow(2, 1.0/n) - 1);

    printf("\n%f <= %f =>%s\n", utilization, bound,
           (utilization <= bound) ? "true" : "false");

    printf("Scheduling occurs for %d ms\n\n", hyper);

    int time = 0;
    int remaining[n];

    for (int i = 0; i < n; i++)
        remaining[i] = 0;

    while (time < hyper) {
        for (int i = 0; i < n; i++) {
            if (time % P[i] == 0) {
                remaining[i] = C[i];
            }
        }

        int selected = -1;
        int minP = 100000;

        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0 && P[i] < minP) {
                minP = P[i];
                selected = i;
            }
        }

        if (selected != -1) {
            printf("%dms onwards: Process %d running\n", time, selected + 1);
            int run = remaining[selected];
            remaining[selected] = 0;
            time += run;
        } else {
            printf("%dms onwards: CPU is idle\n", time);
            time++;
        }
    }

    return 0;
}
