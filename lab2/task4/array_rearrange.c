#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} Queue;

void init_queue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

bool enqueue(Queue *q, int item) {
    if ((q->rear + 1) % MAX_SIZE == q->front)
        return false;
    q->data[q->rear] = item;
    q->rear = (q->rear + 1) % MAX_SIZE;
    return true;
}

bool dequeue(Queue *q, int *item) {
    if (q->front == q->rear)
        return false;
    *item = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    return true;
}

bool is_empty(Queue *q) {
    return q->front == q->rear;
}

void rearrange_array(int a[], int n) {
    Queue q;
    init_queue(&q);
    
    // Enqueue even positions (1-based: 2nd,4th... elements)
    for (int i = 1; i < n; i += 2) {
        enqueue(&q, a[i]);
    }
    
    // Enqueue odd positions (1-based: 1st,3rd... elements)
    for (int i = 0; i < n; i += 2) {
        enqueue(&q, a[i]);
    }
    
    // Dequeue back into array
    int index = 0;
    int val;
    while (dequeue(&q, &val)) {
        a[index++] = val;
    }
}

int main() {
    int a[] = {1,2,3,4,5,6,7,8};
    int n = sizeof(a)/sizeof(a[0]);
    
    printf("原始数组: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    
    rearrange_array(a, n);
    
    printf("重组后数组: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    
    return 0;
}
