//cs158
#include <stdio.h>

#define MAX_PROC 10

void rr(int arr[], int bur[], int n, int tquan) {
    int rem[MAX_PROC];
    int comp[MAX_PROC] = {0};
    int turn[MAX_PROC] = {0};
    int wait[MAX_PROC] = {0};
    int curr = 0;
    int remain = n;
    float total_tat = 0, total_wt = 0;
    int completed = 0;

    for (int i = 0; i < n; i++) {
        rem[i] = bur[i];
    }

    while (completed < n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (rem[i] > 0 && arr[i] <= curr) {
                done = 0;
                int exe_time = (rem[i] > tquan) ? tquan : rem[i];

                curr += exe_time;
                rem[i] -= exe_time;

                if (rem[i] == 0) {
                    completed++;
                    comp[i] = curr;
                    turn[i] = comp[i] - arr[i];
                    wait[i] = turn[i] - bur[i];

                    total_tat += turn[i];
                    total_wt += wait[i];
                }
            }
        }
        if (done) {
            curr++;
        }
    }

    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               i + 1, arr[i], bur[i],
               comp[i], wait[i], turn[i]);
    }

    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
}

int main() {
    int n;
    int arr[MAX_PROC];
    int bur[MAX_PROC];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &arr[i]);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &bur[i]);
    }

    printf("Enter value of Time Quantum: ");
    int tquan;
    scanf("%d", &tquan);

    rr(arr, bur, n, tquan);

    return 0;
}
