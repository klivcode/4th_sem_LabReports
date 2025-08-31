#include <stdio.h>

#define MAX 100

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

// Ready Queue
struct Queue {
    int items[MAX];
    int front, rear;
};

void enqueue(struct Queue *q, int pid) {
    if (q->rear == MAX - 1) return; // overflow check
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->items[q->rear] = pid;
}

int dequeue(struct Queue *q) {
    if (q->front == -1) return -1; // empty
    int pid = q->items[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front++;
    return pid;
}

int isEmpty(struct Queue *q) {
    return q->front == -1;
}

void printReadyQueue(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Ready Queue: [Empty]\n");
        return;
    }
    printf("Ready Queue: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("P%d ", q->items[i] + 1);
    }
    printf("\n");
}

int main() {
    int n, timeQuantum;
    struct Process p[MAX];
    struct Queue readyQueue;
    readyQueue.front = readyQueue.rear = -1;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i;
        printf("Enter arrival time of process P%d: ", i + 1);
        scanf("%d", &p[i].arrivalTime);
        printf("Enter burst time of process P%d: ", i + 1);
        scanf("%d", &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    int currentTime = 0, completed = 0;
    int inQueue[MAX] = {0};

    // Initially enqueue processes that have arrived at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].arrivalTime <= currentTime) {
            enqueue(&readyQueue, i);
            inQueue[i] = 1;
        }
    }

    printf("\n--- Round Robin Execution ---\n");
    while (completed < n) {
        if (isEmpty(&readyQueue)) {
            printf("Time %d: CPU idle\n", currentTime);
            currentTime++;
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && p[i].arrivalTime <= currentTime) {
                    enqueue(&readyQueue, i);
                    inQueue[i] = 1;
                }
            }
            continue;
        }

        int idx = dequeue(&readyQueue);
        printf("Time %d: P%d is executing\n", currentTime, idx + 1);

        if (p[idx].remainingTime > timeQuantum) {
            currentTime += timeQuantum;
            p[idx].remainingTime -= timeQuantum;
        } else {
            currentTime += p[idx].remainingTime;
            p[idx].remainingTime = 0;
            p[idx].completionTime = currentTime;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
            completed++;
        }

        // Enqueue newly arrived processes
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && p[i].arrivalTime <= currentTime) {
                enqueue(&readyQueue, i);
                inQueue[i] = 1;
            }
        }

        // Re-enqueue process if not finished
        if (p[idx].remainingTime > 0) {
            enqueue(&readyQueue, idx);
        }

        printReadyQueue(&readyQueue);
    }

    // Print process table with formulas
    printf("\nProcess\tAT\tBT\tCT\tTAT=CT-AT\tWT=TAT-BT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d(=%d-%d)\t%d(=%d-%d)\n",
               p[i].pid + 1,
               p[i].arrivalTime,
               p[i].burstTime,
               p[i].completionTime,
               p[i].turnaroundTime, p[i].completionTime, p[i].arrivalTime, // TAT = CT-AT
               p[i].waitingTime, p[i].turnaroundTime, p[i].burstTime);    // WT = TAT-BT
    }

    // Calculate and show average with formula
    float totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        totalTAT += p[i].turnaroundTime;
        totalWT += p[i].waitingTime;
    }

    printf("\nAverage Turnaround Time = Sum(TAT)/n = (%.0f/%d) = %.2f\n", totalTAT, n, totalTAT / n);
    printf("Average Waiting Time = Sum(WT)/n = (%.0f/%d) = %.2f\n", totalWT, n, totalWT / n);

    return 0;
}
