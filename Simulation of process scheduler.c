#include <stdio.h>

// Function to calculate waiting time and turnaround time
void findAverageTime(int processes[], int n, int burst_time[]);

// Function to swap two processes
void swap(int *xp, int *yp);

// Function to implement SJF scheduling
void sjf(int processes[], int n, int burst_time[]);

// Function to implement Priority Scheduling
void priorityScheduling(int processes[], int n, int burst_time[]);

// Function to implement SRTF scheduling
void srtf(int processes[], int n, int burst_time[]);

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int burst_time[n];
    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }
    int processes[n];
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
    }
    findAverageTime(processes, n, burst_time);

    // SJF Scheduling
    sjf(processes, n, burst_time);
    printf("\nSJF Scheduling:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: %d\n", processes[i], burst_time[i]);
    }

    // Priority Scheduling
    priorityScheduling(processes, n, burst_time);

    // SRTF Scheduling
    srtf(processes, n, burst_time);

    return 0;
}

// Function to calculate average time
void findAverageTime(int processes[], int n, int burst_time[]) {
    int wt[n], tat[n];
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = burst_time[i - 1] + wt[i - 1];
    }
    for (int i = 0; i < n; i++) {
        tat[i] = burst_time[i] + wt[i];
    }
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
}

// Function to swap two processes
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to implement SJF scheduling
void sjf(int processes[], int n, int burst_time[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (burst_time[j] > burst_time[j + 1]) {
                swap(&burst_time[j], &burst_time[j + 1]);
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

// Function to implement Priority Scheduling
void priorityScheduling(int processes[], int n, int burst_time[]) {
    int priority[n];
    printf("Enter priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &priority[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (priority[j] < priority[j + 1]) {
                swap(&burst_time[j], &burst_time[j + 1]);
                swap(&processes[j], &processes[j + 1]);
                swap(&priority[j], &priority[j + 1]);
            }
        }
    }
    printf("\nPriority Scheduling:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: %d\n", processes[i], burst_time[i]);
    }
}

// Function to implement SRTF scheduling
void srtf(int processes[], int n, int burst_time[]) {
    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }
    int time = 0;
    while (1) {
        int shortest = -1;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0 && (shortest == -1 || remaining_time[i] < remaining_time[shortest])) {
                shortest = i;
            }
        }
        if (shortest == -1) {
            break;
        }
        printf("Process %d executed for 1 unit.\n", processes[shortest]);
        remaining_time[shortest]--;
        time++;
    }
}
