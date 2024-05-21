//cs158
#include <stdio.h>

void findCompletionTime(int processes[], int n, int bt[], int at[], int wt[], int tat[], int ct[]) {
    int currentTime = 0;
    int completion[n];
    float avgTAT = 0.0;
    float avgWT = 0.0;

    for (int i = 0; i < n; i++)
        completion[i] = -1;

    for (int i = 0; i < n; i++) {
        int minIndex = -1, minTime = 999999;

        for (int j = 0; j < n; j++) {
            if (at[j] < minTime && completion[j] == -1) {
                minIndex = j;
                minTime = at[j];
            }
        }

        currentTime = (currentTime > at[minIndex]) ? currentTime : at[minIndex];

        completion[minIndex] = currentTime + bt[minIndex];

        wt[minIndex] = currentTime - at[minIndex];
        tat[minIndex] = wt[minIndex] + bt[minIndex];
        avgTAT += tat[minIndex];
        avgWT += wt[minIndex];

        currentTime = completion[minIndex];
    }

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        ct[i] = completion[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], at[i], bt[i], wt[i], tat[i], ct[i]);
    }
    printf("Average turn around time = %f\n", avgTAT / n);
    printf("Average waiting time = %f\n", avgWT / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int burst_time[n];
    int arrival_time[n];

    printf("Enter the arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Arrival time for process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        processes[i] = i + 1;
    }

    int wt[n], tat[n], ct[n];

    printf("\nFCFS Scheduling:\n");
    findCompletionTime(processes, n, burst_time, arrival_time, wt, tat, ct);

    return 0;
}
