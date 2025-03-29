#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

// 定义栈结构
typedef struct {
    char data[MAXSIZE];
    int top;
} Stack;

// 初始化栈
void InitStack(Stack *S) {
    S->top = -1;
}

// 判断栈是否为空
int IsEmpty(Stack *S) {
    return S->top == -1;
}

// 判断栈是否已满
int IsFull(Stack *S) {
    return S->top == MAXSIZE - 1;
}

// 入栈操作
int Push(Stack *S, char x) {
    if (IsFull(S)) {
        printf("栈已满！\n");
        return 0;
    }
    S->data[++S->top] = x;
    return 1;
}

// 出栈操作
int Pop(Stack *S, char *x) {
    if (IsEmpty(S)) {
        return 0;
    }
    *x = S->data[S->top--];
    return 1;
}

// 判断括号是否匹配
int IsMatchedBrackets(const char *expr) {
    Stack S;
    InitStack(&S);
    
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(') {
            // 遇到左括号，入栈
            if (!Push(&S, '(')) {
                return 0;  // 栈满，无法继续判断
            }
        } else if (expr[i] == ')') {
            // 遇到右括号，尝试出栈
            char c;
            if (!Pop(&S, &c)) {
                return 0;  // 栈空，说明右括号多于左括号
            }
        }
        // 其他字符忽略
    }
    
    // 最后检查栈是否为空
    return IsEmpty(&S);  // 如果为空则匹配成功
}

int main() {
    char expr[MAXSIZE];
    
    printf("请输入表达式（包含括号的数学表达式）：\n");
    fgets(expr, MAXSIZE, stdin);
    
    // 移除换行符
    expr[strcspn(expr, "\n")] = 0;
    
    // 判断括号是否匹配并输出结果
    if (IsMatchedBrackets(expr)) {
        printf("括号匹配成功！\n");
    } else {
        printf("括号不匹配！\n");
    }
    
    // 测试一些示例
    printf("\n测试示例：\n");
    
    const char *testCases[] = {
        "a+((b+c)*5)",
        "((a+((b+c)*5)",
        "(a+b)*(c+d)",
        "((()))",
        ")()",
        "a+b+c",
        NULL
    };
    
    for (int i = 0; testCases[i] != NULL; i++) {
        printf("表达式 \"%s\" : ", testCases[i]);
        if (IsMatchedBrackets(testCases[i])) {
            printf("括号匹配成功\n");
        } else {
            printf("括号不匹配\n");
        }
    }
    
    return 0;
}
