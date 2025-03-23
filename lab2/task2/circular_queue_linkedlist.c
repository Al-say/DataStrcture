#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *tail;
} LinkedQueue;

void init_queue(LinkedQueue *q) {
    q->tail = (Node*)malloc(sizeof(Node));
    q->tail->next = q->tail; // 指向自己形成空队列
}

bool is_empty(LinkedQueue *q) {
    return q->tail->next == q->tail;
}

void enqueue(LinkedQueue *q, int item) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = item;
    new_node->next = q->tail->next;
    q->tail->next = new_node;
    q->tail = new_node;
}

bool dequeue(LinkedQueue *q, int *item) {
    if (is_empty(q))
        return false;
    
    Node *head = q->tail->next;
    Node *first_node = head->next;
    *item = first_node->data;
    
    head->next = first_node->next;
    if (first_node == q->tail) // 如果删除的是最后一个节点
        q->tail = head;
    
    free(first_node);
    return true;
}

int queue_length(LinkedQueue *q) {
    int count = 0;
    Node *current = q->tail->next->next; // 第一个实际节点
    while (current != q->tail->next) {   // 回到头结点时停止
        count++;
        current = current->next;
    }
    return count;
}

int main() {
    LinkedQueue q;
    init_queue(&q);
    
    // 测试入队
    for (int i = 1; i <= 5; i++)
        enqueue(&q, i*10);
    
    // 测试出队
    int val;
    while (!is_empty(&q)) {
        dequeue(&q, &val);
        printf("%d ", val);
    }
    printf("\nQueue length: %d\n", queue_length(&q));
    return 0;
}
