//cs158
//Write a C program to simulate producer-consumer problem using semaphores.
#include <stdio.h>
#include <stdlib.h>

// Function declarations
void producer();
void consumer();
int wait(int);
int signal(int);

// Semaphore variables
int mutex = 1, full = 0, empty = 7, itemCount = 0;

int main() {
    int choice;
    printf("\n1. Producer\n2. Consumer\n3. Exit");
    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if (mutex == 1 && empty != 0)
                    producer();
                else
                    printf("Buffer is full!!\n");
                break;
            case 2:
                if (mutex == 1 && full != 0)
                    consumer();
                else
                    printf("Buffer is empty!!\n");
                break;
            case 3:
                printf("\nNumber of items remaining in buffer: %d\n", itemCount);
                exit(0);
            default:
                printf("Invalid choice!\n");
                break;
        }
    }
    return 0;
}

int wait(int s) {
    return (--s);
}

int signal(int s) {
    return (++s);
}                                                                                                                                                                                                          

void producer() {
    mutex = wait(mutex);
    full = signal(full);
    empty = wait(empty);
    itemCount++;
    printf("\nProducer produces the item %d", itemCount);
    mutex = signal(mutex);
}

void consumer() {
    mutex = wait(mutex);
    full = wait(full);
    empty = signal(empty);
    printf("\nConsumer consumes item %d", itemCount);
    itemCount--;
    mutex = signal(mutex);
}
