#include <stdio.h>

struct Process
{
    int pid;            // Process ID
    int arrivalTime;    // Arrival Time
    int burstTime;      // Burst Time
    int completionTime; // Completion Time
    int turnaroundTime; // Turnaround Time
    int waitingTime;    // Waiting Time
    int isCompleted;    // Status flag
};

// Helper function to print number centered in a 7-char wide field
void printCentered(int num)
{
    char buffer[10];
    int len = sprintf(buffer, "%d", num);
    int padding = (7 - len) / 2;
    for (int i = 0; i < padding; i++)
        printf(" ");
    printf("%d", num);
    for (int i = 0; i < 7 - len - padding; i++)
        printf(" ");
}

int main()
{
    int n;
    struct Process p[100];
    float totalTurnaroundTime = 0, totalWaitingTime = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter arrival time of process %d: ", p[i].pid);
        scanf("%d", &p[i].arrivalTime);
        printf("Enter burst time of process %d: ", p[i].pid);
        scanf("%d", &p[i].burstTime);
        p[i].isCompleted = 0;
    }

    int completed = 0, currentTime = 0;

    int ganttProcesses[100];
    int ganttStartTimes[100];
    int ganttIndex = 0;

    while (completed != n)
    {
        int idx = -1;
        int minBT = 1e9;

        for (int i = 0; i < n; i++)
        {
            if (p[i].arrivalTime <= currentTime && p[i].isCompleted == 0)
            {
                if (p[i].burstTime < minBT)
                {
                    minBT = p[i].burstTime;
                    idx = i;
                }
                else if (p[i].burstTime == minBT)
                {
                    if (p[i].arrivalTime < p[idx].arrivalTime)
                        idx = i;
                }
            }
        }

        if (idx != -1)
        {
            ganttProcesses[ganttIndex] = p[idx].pid;
            ganttStartTimes[ganttIndex] = currentTime;
            ganttIndex++;

            p[idx].completionTime = currentTime + p[idx].burstTime;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;

            totalTurnaroundTime += p[idx].turnaroundTime;
            totalWaitingTime += p[idx].waitingTime;

            p[idx].isCompleted = 1;
            completed++;
            currentTime = p[idx].completionTime;
        }
        else
        {
            currentTime++;
        }
    }

    // Gantt Chart
    printf("\nGantt Chart:\n");

    // Top border
    for (int i = 0; i < ganttIndex; i++)
    {
        printf("+");
        for (int j = 0; j < 7; j++)
            printf("-");
    }
    printf("+\n");

    // Process boxes
    for (int i = 0; i < ganttIndex; i++)
    {
        printf("| P%d", ganttProcesses[i]);
        int len = 1;
        int pid = ganttProcesses[i];
        while (pid > 0)
        {
            len++;
            pid /= 10;
        }
        for (int j = 0; j < 7 - 1 - len; j++)
            printf(" ");
    }
    printf("|\n");

    // Bottom border
    for (int i = 0; i < ganttIndex; i++)
    {
        printf("+");
        for (int j = 0; j < 7; j++)
            printf("-");
    }
    printf("+\n");

    // Start times
    for (int i = 0; i < ganttIndex; i++)
        printCentered(ganttStartTimes[i]);
    printCentered(p[ganttProcesses[ganttIndex - 1] - 1].completionTime);
    printf("\n");

    printf("\nProcess\tAT\tBT\tCT\tTAT=CT-AT\tWT=TAT-BT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d(=%d-%d)\t%d(=%d-%d)\n",
               p[i].pid,
               p[i].arrivalTime,
               p[i].burstTime,
               p[i].completionTime,
               p[i].turnaroundTime, p[i].completionTime, p[i].arrivalTime, // TAT = CT-AT
               p[i].waitingTime, p[i].turnaroundTime, p[i].burstTime);     // WT = TAT-BT
    }

    // Average TAT and WT with formulas
    printf("\nAverage Turnaround Time = Sum(TAT)/n = (%.0f/%d) = %.2f", totalTurnaroundTime, n, totalTurnaroundTime / n);
    printf("\nAverage Waiting Time = Sum(WT)/n = (%.0f/%d) = %.2f\n", totalWaitingTime, n, totalWaitingTime / n);

    return 0;
}
