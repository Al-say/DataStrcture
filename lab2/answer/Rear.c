#include <stdio.h>
#include <stdlib.h>

// 定义链队结点类型
typedef struct QNode {
    int data;           // 数据域
    struct QNode *next; // 指针域
} QNode;

// 定义队列结构（仅包含队尾指针）
typedef struct {
    QNode *rear;       // 队尾指针
} LinkQueue;

// 初始化队列
void InitQueue(LinkQueue *Q) {
    // 创建头结点
    QNode *head = (QNode *)malloc(sizeof(QNode));
    if (!head) {
        printf("内存分配失败！\n");
        exit(1);
    }
    head->next = head;  // 头结点自己指向自己，形成循环
    Q->rear = head;     // 队尾指针指向头结点
}

// 入队操作
void Enqueue(LinkQueue *Q, int x) {
    QNode *newNode = (QNode *)malloc(sizeof(QNode));
    if (!newNode) {
        printf("内存分配失败！\n");
        exit(1);
    }
    newNode->data = x;
    // 新结点插入到队尾和队首之间
    newNode->next = Q->rear->next;  // 新结点指向头结点
    Q->rear->next = newNode;        // 原队尾结点指向新结点
    Q->rear = newNode;              // 修改队尾指针
}

// 出队操作
int Dequeue(LinkQueue *Q, int *x) {
    if (Q->rear == Q->rear->next) {  // 队列为空
        printf("队列为空！\n");
        return 0;
    }
    QNode *head = Q->rear->next;     // 保存头结点位置
    QNode *firstNode = head->next;    // 第一个数据结点
    *x = firstNode->data;            // 获取队头元素
    head->next = firstNode->next;    // 头结点指向第二个结点
    
    // 如果队列只有一个元素，出队后需要修改rear指针
    if (firstNode == Q->rear) {
        Q->rear = head;
    }
    
    free(firstNode);                 // 释放原队头结点
    return 1;
}

// 计算队列长度
int Length(LinkQueue *Q) {
    if (Q->rear == Q->rear->next) {  // 空队列
        return 0;
    }
    
    int len = 0;
    QNode *head = Q->rear->next;     // 头结点
    QNode *p = head->next;           // 第一个数据结点
    
    // 从第一个数据结点开始计数，直到回到头结点
    while (p != head) {
        len++;
        p = p->next;
    }
    return len;
}

// 销毁队列
void DestroyQueue(LinkQueue *Q) {
    QNode *head = Q->rear->next;  // 保存头结点
    Q->rear->next = NULL;         // 断开循环链接
    
    // 释放所有结点
    QNode *p = head;
    while (p) {
        QNode *temp = p;
        p = p->next;
        free(temp);
    }
    Q->rear = NULL;
}

// 主函数，用于测试
int main() {
    LinkQueue Q;
    int item;
    
    // 初始化队列
    InitQueue(&Q);
    
    printf("测试入队操作：\n");
    Enqueue(&Q, 10);
    Enqueue(&Q, 20);
    Enqueue(&Q, 30);
    printf("当前队列长度：%d\n", Length(&Q));
    
    printf("\n测试出队操作：\n");
    if (Dequeue(&Q, &item)) {
        printf("出队元素：%d\n", item);
    }
    if (Dequeue(&Q, &item)) {
        printf("出队元素：%d\n", item);
    }
    
    printf("\n当前队列长度：%d\n", Length(&Q));
    
    // 测试继续入队
    printf("\n继续入队测试：\n");
    Enqueue(&Q, 40);
    printf("当前队列长度：%d\n", Length(&Q));
    
    // 销毁队列
    DestroyQueue(&Q);
    
    return 0;
}
