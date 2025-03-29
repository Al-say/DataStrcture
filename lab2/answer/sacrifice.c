#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100  // 队列的最大容量

// 定义循环队列结构
typedef struct {
    int *data;       // 存储队列元素
    int front;       // 队头指针
    int rear;        // 队尾指针
    int maxSize;     // 队列最大容量
} SqQueue;

// 初始化队列
void InitQueue(SqQueue *Q) {
    Q->data = (int *)malloc(MAXSIZE * sizeof(int));
    if (!Q->data) {
        printf("内存分配失败！\n");
        exit(1);
    }
    Q->front = Q->rear = 0;  // 初始化队头队尾指针
    Q->maxSize = MAXSIZE;
}

// 判断队列是否为空
int IsEmpty(SqQueue *Q) {
    return Q->front == Q->rear;  // 队头等于队尾时为空
}

// 判断队列是否已满
int IsFull(SqQueue *Q) {
    return (Q->rear + 1) % Q->maxSize == Q->front;  // 牺牲一个空间来区分队空和队满
}

// 计算队列长度
int Length(SqQueue *Q) {
    return (Q->rear - Q->front + Q->maxSize) % Q->maxSize;
}

// 入队操作
int Enqueue(SqQueue *Q, int x) {
    if (IsFull(Q)) {
        printf("队列已满！\n");
        return 0;  // 队列已满，入队失败
    }
    Q->data[Q->rear] = x;  // 将元素插入队尾
    Q->rear = (Q->rear + 1) % Q->maxSize;  // 队尾指针循环后移
    return 1;  // 入队成功
}

// 出队操作
int Dequeue(SqQueue *Q, int *x) {
    if (IsEmpty(Q)) {
        printf("队列为空！\n");
        return 0;  // 队列为空，出队失败
    }
    *x = Q->data[Q->front];  // 取出队头元素
    Q->front = (Q->front + 1) % Q->maxSize;  // 队头指针循环后移
    return 1;  // 出队成功
}

// 销毁队列
void DestroyQueue(SqQueue *Q) {
    if (Q->data) {
        free(Q->data);
        Q->data = NULL;
    }
}

// 主函数，用于测试循环队列的功能
int main() {
    SqQueue Q;
    int item;
    
    // 初始化队列
    InitQueue(&Q);
    
    printf("测试入队操作：\n");
    // 测试入队
    Enqueue(&Q, 10);
    Enqueue(&Q, 20);
    Enqueue(&Q, 30);
    printf("当前队列长度：%d\n", Length(&Q));
    
    printf("\n测试出队操作：\n");
    // 测试出队
    if (Dequeue(&Q, &item)) {
        printf("出队元素：%d\n", item);
    }
    if (Dequeue(&Q, &item)) {
        printf("出队元素：%d\n", item);
    }
    
    printf("\n当前队列长度：%d\n", Length(&Q));
    
    // 测试队列为空的情况
    if (IsEmpty(&Q)) {
        printf("\n队列为空！\n");
    } else {
        printf("\n队列不为空！\n");
    }
    
    // 销毁队列
    DestroyQueue(&Q);
    
    return 0;
}
