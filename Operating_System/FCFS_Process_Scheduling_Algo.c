#include <stdio.h>

struct Process {
    int pid;       // Process ID
    int arrival;   // Arrival Time
    int burst;     // Burst Time
    int completion;
    int turnaround;
    int waiting;
};

int main() {
    int n, i, j;
    float avgTAT = 0, avgWT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter Arrival Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].arrival);
        printf("Enter Burst Time of P%d: ", p[i].pid);
        scanf("%d", &p[i].burst);
    }

    // Sort processes by Arrival Time (FCFS order)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int currentTime = 0;
    int start[n];   // start time of each process
    int end[n];     // completion time for Gantt chart

    // Calculate times
    for (i = 0; i < n; i++) {
        if (currentTime < p[i].arrival) {
            currentTime = p[i].arrival; // CPU idle till process arrives
        }
        start[i] = currentTime;
        currentTime += p[i].burst;
        end[i] = currentTime;

        p[i].completion = currentTime;
        p[i].turnaround = p[i].completion - p[i].arrival;   // TAT = CT - AT
        p[i].waiting = p[i].turnaround - p[i].burst;        // WT = TAT - BT

        avgTAT += p[i].turnaround;
        avgWT += p[i].waiting;
    }

    // Display Gantt chart
    printf("\nGantt Chart:\n");

    // Top bar
    printf(" ");
    for (i = 0; i < n; i++) {
        printf("-------");
    }
    printf("\n|");

    // Process IDs in middle
    for (i = 0; i < n; i++) {
        printf("  P%d  |", p[i].pid);
    }
    printf("\n ");

    // Bottom bar
    for (i = 0; i < n; i++) {
        printf("-------");
    }
    printf("\n");

    // Timeline
    printf("%d", start[0]);
    for (i = 0; i < n; i++) {
        printf("      %d", end[i]);
    }
    printf("\n");

    // Display table with formulas
    printf("\n%-8s %-5s %-5s %-5s %-15s %-15s\n", 
           "Process", "AT", "BT", "CT", "TAT(CT-AT)", "WT(TAT-BT)");

    for (i = 0; i < n; i++) {
        printf("P%-7d %-5d %-5d %-5d %-6d (%d-%d)     %-6d (%d-%d)\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion,
               p[i].turnaround, p[i].completion, p[i].arrival,
               p[i].waiting, p[i].turnaround, p[i].burst);
    }

    // Averages with formula
    printf("\nAverage Turnaround Time = sum of TAT / n = %.2f / %d = %.2f", avgTAT, n, avgTAT / n);
    printf("\nAverage Waiting Time    = sum of WT / n  = %.2f / %d = %.2f\n", avgWT, n, avgWT / n);

    return 0;
}
