#include <stdio.h>

#define MAX_PROC 10

struct Proc {
    int pid, at, bt, pri, ct, tat, wt, rt, exec;
};

void prio_non_preemptive(struct Proc proc[], int n) {
    int curr_time = 0, total_ct = 0;

    while (1) {
        int high_prio = 9999, high_prio_idx = -1;

       
        for (int i = 0; i < n; i++) {
            if (proc[i].at <= curr_time && proc[i].exec == 0) {
                if (proc[i].pri < high_prio) {
                    high_prio = proc[i].pri;
                    high_prio_idx = i;
                }
            }
        }

       
        if (high_prio_idx == -1) {
            break;
        }

        
        proc[high_prio_idx].ct = curr_time + proc[high_prio_idx].bt;
        proc[high_prio_idx].tat = proc[high_prio_idx].ct - proc[high_prio_idx].at;
        proc[high_prio_idx].wt = proc[high_prio_idx].tat - proc[high_prio_idx].bt;
        proc[high_prio_idx].rt = curr_time - proc[high_prio_idx].at;
        if (proc[high_prio_idx].wt < 0)
            proc[high_prio_idx].wt = 0;
        proc[high_prio_idx].exec = 1;
        total_ct = proc[high_prio_idx].ct;
        curr_time = total_ct;
    }
}

int main() {
    int n;
    struct Proc proc[MAX_PROC];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

   
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &proc[i].at);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].bt);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &proc[i].pri);
        proc[i].exec = 0;
    }

    prio_non_preemptive(proc, n);

    
    printf("PID\tAT\tBT\tPri\tCT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               proc[i].pid, proc[i].at, proc[i].bt, proc[i].pri,
               proc[i].ct, proc[i].wt, proc[i].tat, proc[i].rt);
    }

    return 0;
}
