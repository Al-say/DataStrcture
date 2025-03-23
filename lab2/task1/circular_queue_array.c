#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} CircularQueue;

void init_queue(CircularQueue *q) {
    q->front = 0;
    q->rear = 0;
}

bool is_empty(CircularQueue *q) {
    return q->front == q->rear;
}

bool enqueue(CircularQueue *q, int item) {
    if ((q->rear + 1) % MAX_SIZE == q->front)
        return false;
    q->data[q->rear] = item;
    q->rear = (q->rear + 1) % MAX_SIZE;
    return true;
}

bool dequeue(CircularQueue *q, int *item) {
    if (is_empty(q))
        return false;
    *item = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    return true;
}

int queue_length(CircularQueue *q) {
    return (q->rear - q->front + MAX_SIZE) % MAX_SIZE;
}

int main() {
    CircularQueue q;
    init_queue(&q);
    
    // Test enqueue
    for (int i = 1; i <= 5; i++)
        enqueue(&q, i*10);
    
    // Test dequeue
    int val;
    while (!is_empty(&q)) {
        dequeue(&q, &val);
        printf("%d ", val);
    }
    printf("\nQueue length: %d\n", queue_length(&q));
    return 0;
}
