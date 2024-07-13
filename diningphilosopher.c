//cs158
//Write a C program to simulate the concept of Dining-Philosophers problem
/*#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 10

pthread_mutex_t fork_mutex[MAX_PHILOSOPHERS];
pthread_mutex_t table_mutex; // mutex for critical section access
pthread_mutex_t eating_mutex; // mutex to control eating philosophers
int eating_count = 0; // counter for philosophers eating at the same time

int num_philosophers;
int num_hungry;
int hungry_philosophers[MAX_PHILOSOPHERS];
int choice;

void* philosopher(void* arg) {
    int philosopher_id = *((int*)arg);
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % num_philosophers;

    while (1) {
        int is_hungry = 0;
        for (int i = 0; i < num_hungry; ++i) {
            if (hungry_philosophers[i] == philosopher_id) {
                is_hungry = 1;
                break;
            }
        }

        if (!is_hungry) {
            sleep(1); // If not hungry, continue thinking
            continue;
        }

        if (choice == 1) {
            // One philosopher can eat at a time
            pthread_mutex_lock(&table_mutex);
            pthread_mutex_lock(&fork_mutex[left_fork]);
            pthread_mutex_lock(&fork_mutex[right_fork]);
            pthread_mutex_unlock(&table_mutex);

            printf("Philosopher %d is granted to eat\n", philosopher_id);
            sleep(1); // Simulate eating
            printf("Philosopher %d is waiting\n", philosopher_id);

            pthread_mutex_unlock(&fork_mutex[left_fork]);
            pthread_mutex_unlock(&fork_mutex[right_fork]);

        } else if (choice == 2) {
            // Two philosophers can eat at a time
            pthread_mutex_lock(&eating_mutex);
            if (eating_count < 2) {
                eating_count++;
                pthread_mutex_unlock(&eating_mutex);

                pthread_mutex_lock(&fork_mutex[left_fork]);
                pthread_mutex_lock(&fork_mutex[right_fork]);

                printf("Philosopher %d is granted to eat\n", philosopher_id);
                sleep(1); // Simulate eating

                pthread_mutex_unlock(&fork_mutex[left_fork]);
                pthread_mutex_unlock(&fork_mutex[right_fork]);

                pthread_mutex_lock(&eating_mutex);
                eating_count--;
                pthread_mutex_unlock(&eating_mutex);
            } else {
                pthread_mutex_unlock(&eating_mutex);
                printf("Philosopher %d is waiting\n", philosopher_id);
                sleep(1);
            }
        }

        sleep(1); // Simulate thinking/waiting before next cycle
    }

    return NULL;
}

int main() {
    pthread_t philosophers[MAX_PHILOSOPHERS];
    int philosopher_ids[MAX_PHILOSOPHERS];

    printf("Enter the total number of philosophers (max %d): ", MAX_PHILOSOPHERS);
    scanf("%d", &num_philosophers);

    if (num_philosophers < 2 || num_philosophers > MAX_PHILOSOPHERS) {
        printf("Invalid number of philosophers. Exiting.\n");
        return 1;
    }

    printf("How many are hungry: ");
    scanf("%d", &num_hungry);

    for (int i = 0; i < num_hungry; ++i) {
        printf("Enter philosopher %d position: ", i + 1);
        scanf("%d", &hungry_philosophers[i]);
    }

    pthread_mutex_init(&table_mutex, NULL);
    pthread_mutex_init(&eating_mutex, NULL);
    for (int i = 0; i < num_philosophers; ++i) {
        pthread_mutex_init(&fork_mutex[i], NULL);
    }

    for (int i = 0; i < num_philosophers; ++i) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    while (1) {
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 3) {
            break;
        } else if (choice != 1 && choice != 2) {
            printf("Invalid choice. Please try again.\n");
        }
    }

    for (int i = 0; i < num_philosophers; ++i) {
        pthread_cancel(philosophers[i]);
        pthread_join(philosophers[i], NULL);
    }

    pthread_mutex_destroy(&table_mutex);
    pthread_mutex_destroy(&eating_mutex);
    for (int i = 0; i < num_philosophers; ++i) {
        pthread_mutex_destroy(&fork_mutex[i]);
    }

    return 0;
}*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_PHIL 10

typedef enum { T, H, E } S;

S s[MAX_PHIL];
int n;
int h;
int hp[MAX_PHIL];
int f[MAX_PHIL];

void p() {
    printf("\n");
    for (int i = 0; i < n; ++i) {
        if (s[i] == T) printf("P %d is thinking\n", i + 1);
        else if (s[i] == H) printf("P %d is waiting\n", i + 1);
        else if (s[i] == E) printf("P %d is eating\n", i + 1);
    }
}

void sim(int a) {
    int e = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == H) {
            int l = i;
            int r = (i + 1) % n;

            if (f[l] == 0 && f[r] == 0) {
                f[l] = f[r] = 1;
                s[i] = E;
                e++;
                printf("P %d is granted to eat\n", i + 1);
                if (!a && e == 1) break;
                if (a && e == 2) break;
            }
        }
    }

    sleep(1);

    for (int i = 0; i < n; ++i) {
        if (s[i] == E) {
            int l = i;
            int r = (i + 1) % n;
            f[l] = f[r] = 0;
            s[i] = T;
        }
    }
}

int main() {
    printf("Enter total number of philosophers (max %d): ", MAX_PHIL);
    scanf("%d", &n);

    if (n < 2 || n > MAX_PHIL) {
        printf("Invalid number of philosophers. Exiting.\n");
        return 1;
    }

    printf("How many are hungry: ");
    scanf("%d", &h);

    for (int i = 0; i < h; ++i) {
        printf("Enter philosopher %d position: ", i + 1);
        int p;
        scanf("%d", &p);
        hp[i] = p - 1;
        s[hp[i]] = H;
    }

    for (int i = 0; i < n; ++i) {
        f[i] = 0;
    }

    int c;
    do {
        p();
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &c);

        switch (c) {
            case 1:
                sim(0);
                break;
            case 2:
                sim(1);
                break;
            case 3:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

    } while (c != 3);

    return 0;
}
/* 
In this reduced version:
- Variable names like `states`, `num_philosophers`, `num_hungry`, `hungry_philosophers`, `forks`, `print_state`, and `simulate` have been shortened to `s`, `n`, `h`, `hp`, `f`, `p`, and `sim` respectively.
- Function and variable names are now shorter while maintaining clarity and functionality.
  
This version retains the functionality of the original code while adhering to the request to reduce variable names and functions.*/