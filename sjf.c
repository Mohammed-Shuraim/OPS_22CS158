//cs158
#include <stdio.h>

#define MAX_PROCESS 10

typedef struct {
    int pid;
    int arr;
    int burst;
    int comp;
    int turn;
    int wait;
    int processed;
} Proc;

void sjf_np(Proc procs[], int n) {
    int curr_time = 0;
    int total_comp_time = 0;
    int total_wait_time = 0;
    int total_turnaround_time = 0;

    while (1) {
        int shortest_job = -1;
        int shortest_burst = 9999;

        for (int i = 0; i < n; i++) {
            if (procs[i].arr <= curr_time && procs[i].processed == 0) {
                if (procs[i].burst < shortest_burst) {
                    shortest_burst = procs[i].burst;
                    shortest_job = i;
                }
            }
        }

        if (shortest_job == -1) {
            break;
        }

        procs[shortest_job].comp = curr_time + procs[shortest_job].burst;
        procs[shortest_job].turn = procs[shortest_job].comp - procs[shortest_job].arr;
        procs[shortest_job].wait = procs[shortest_job].turn - procs[shortest_job].burst;
        if (procs[shortest_job].wait < 0)
            procs[shortest_job].wait = 0;

        total_comp_time += procs[shortest_job].comp;
        total_wait_time += procs[shortest_job].wait;
        total_turnaround_time += procs[shortest_job].turn;

        procs[shortest_job].processed = 1;
        curr_time = procs[shortest_job].comp;
    }
 
    double avg_turnaround_time = (double)total_turnaround_time / n;
    double avg_waiting_time = (double)total_wait_time / n;

    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               procs[i].pid, procs[i].arr, procs[i].burst,
               procs[i].comp, procs[i].wait, procs[i].turn);
    }

    
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
}

int main() {
    int n;
    Proc procs[MAX_PROCESS];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        procs[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &procs[i].arr);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &procs[i].burst);
        procs[i].processed = 0;
    }

    sjf_np(procs, n);

    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               procs[i].pid, procs[i].arr, procs[i].burst,
               procs[i].comp, procs[i].wait, procs[i].turn);
    }

    return 0;
}