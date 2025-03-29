#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

// 定义队列结构
typedef struct {
    int data[MAXSIZE];
    int front;
    int rear;
} Queue;

// 初始化队列
void InitQueue(Queue *Q) {
    Q->front = Q->rear = 0;
}

// 判断队列是否为空
int IsEmpty(Queue *Q) {
    return Q->front == Q->rear;
}

// 判断队列是否已满
int IsFull(Queue *Q) {
    return (Q->rear + 1) % MAXSIZE == Q->front;
}

// 入队操作
int Enqueue(Queue *Q, int x) {
    if (IsFull(Q)) {
        printf("队列已满！\n");
        return 0;
    }
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return 1;
}

// 出队操作
int Dequeue(Queue *Q, int *x) {
    if (IsEmpty(Q)) {
        return 0;
    }
    *x = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return 1;
}

// 移动偶数位元素到奇数位元素前面
void MoveEvenIndexToFront(int a[], int n) {
    Queue evenQ, oddQ;  // 分别存储偶数位和奇数位的元素
    
    // 初始化队列
    InitQueue(&evenQ);
    InitQueue(&oddQ);
    
    // 将数组元素按位置分类放入队列
    for (int i = 0; i < n; i++) {
        if (i % 2 == 1) {  // 偶数位（下标为奇数）
            Enqueue(&evenQ, a[i]);
        } else {  // 奇数位（下标为偶数）
            Enqueue(&oddQ, a[i]);
        }
    }
    
    // 重构数组：先放偶数位元素，再放奇数位元素
    int index = 0;
    int temp;
    
    // 先放入偶数位的元素
    while (Dequeue(&evenQ, &temp)) {
        a[index++] = temp;
    }
    
    // 再放入奇数位的元素
    while (Dequeue(&oddQ, &temp)) {
        a[index++] = temp;
    }
}

// 打印数组
void PrintArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    // 测试用例1: 题目给出的例子
    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n1 = sizeof(a1) / sizeof(a1[0]);
    
    printf("测试用例1:\n");
    printf("原始数组: ");
    PrintArray(a1, n1);
    
    MoveEvenIndexToFront(a1, n1);
    
    printf("移动后数组: ");
    PrintArray(a1, n1);
    
    // 测试用例2: 奇数长度数组
    int a2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(a2) / sizeof(a2[0]);
    
    printf("\n测试用例2:\n");
    printf("原始数组: ");
    PrintArray(a2, n2);
    
    MoveEvenIndexToFront(a2, n2);
    
    printf("移动后数组: ");
    PrintArray(a2, n2);
    
    // 测试用例3: 较短数组
    int a3[] = {1, 2};
    int n3 = sizeof(a3) / sizeof(a3[0]);
    
    printf("\n测试用例3:\n");
    printf("原始数组: ");
    PrintArray(a3, n3);
    
    MoveEvenIndexToFront(a3, n3);
    
    printf("移动后数组: ");
    PrintArray(a3, n3);
    
    return 0;
}
