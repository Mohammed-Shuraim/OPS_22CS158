#include <stdio.h>
#include <stdlib.h>

#define MAX 20
#define TQ 4

struct Proc {
    int id, at, bt, pri, rt, ct, tat, wt, exec, rem, q;
};

int next_fcfs(struct Proc p[], int n, int t) {
    int e = -1;
    for (int i = 0; i < n; i++) {
        if (p[i].at <= t && p[i].exec == 0 && p[i].q == 1) {
            if (e == -1 || p[i].at < p[e].at) {
                e = i;
            }
        }
    }
    return e;
}

int next_sjf(struct Proc p[], int n, int t) {
    int s = -1;
    for (int i = 0; i < n; i++) {
        if (p[i].at <= t && p[i].exec == 0 && p[i].q == 2) {
            if (s == -1 || p[i].bt < p[s].bt) {
                s = i;
            }
        }
    }
    return s;
}

int next_pri(struct Proc p[], int n, int t) {
    int h = -1;
    for (int i = 0; i < n; i++) {
        if (p[i].at <= t && p[i].exec == 0 && p[i].q == 3) {
            if (h == -1 || p[i].pri < p[h].pri) {
                h = i;
            }
        }
    }
    return h;
}

void rr(struct Proc p[], int n, int tq, int *t) {
    int d = 0;
    while (d < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].at <= *t && p[i].rem > 0 && p[i].q == 4) {
                if (p[i].rem > tq) {
                    *t += tq;
                    p[i].rem -= tq;
                } else {
                    *t += p[i].rem;
                    p[i].rem = 0;
                    p[i].ct = *t;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    if (p[i].wt < 0)
                        p[i].wt = 0;
                    d++;
                }
            }
        }
    }
}

void simulate(struct Proc p[], int n) {
    int t = 0, comp = 0;

    while (comp < n) {
        int np = -1;

        np = next_fcfs(p, n, t);
        if (np == -1) np = next_sjf(p, n, t);
        if (np == -1) np = next_pri(p, n, t);
        
        if (np != -1) {
            t += p[np].bt;
            p[np].ct = t;
            p[np].tat = p[np].ct - p[np].at;
            p[np].wt = p[np].tat - p[np].bt;
            if (p[np].wt < 0)
                p[np].wt = 0;
            p[np].exec = 1;
            comp++;
        } else {
            t++;
        }

        if (comp < n && np == -1) {
            rr(p, n, TQ, &t);
            for (int i = 0; i < n; i++) {
                if (p[i].exec == 1 && p[i].q == 4) {
                    comp++;
                }
            }
        }
    }
}

int main() {
    int n;
    struct Proc p[MAX];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &p[i].pri);
        printf("Enter queue number for process %d (1: FCFS, 2: SJF, 3: Priority, 4: RR): ", i + 1);
        scanf("%d", &p[i].q);
        p[i].rem = p[i].bt;
        p[i].exec = 0;
    }

    simulate(p, n);

    printf("ID\tAT\tBT\tPri\tQ\tCT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].pri,
               p[i].q, p[i].ct, p[i].wt, p[i].tat, p[i].rt);
    }

    return 0;
}
