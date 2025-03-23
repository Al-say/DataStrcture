#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

void init_stack(Stack *s) {
    s->top = -1;
}

bool push(Stack *s, char c) {
    if (s->top >= MAX_SIZE-1)
        return false;
    s->data[++s->top] = c;
    return true;
}

bool pop(Stack *s, char *c) {
    if (s->top == -1)
        return false;
    *c = s->data[s->top--];
    return true;
}

bool is_empty(Stack *s) {
    return s->top == -1;
}

bool bracket_match(const char *str) {
    Stack s;
    init_stack(&s);
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
            push(&s, str[i]);
        } else if (str[i] == ')' || str[i] == ']' || str[i] == '}') {
            char top_char;
            if (!pop(&s, &top_char))
                return false;
                
            if ((str[i] == ')' && top_char != '(') ||
                (str[i] == ']' && top_char != '[') ||
                (str[i] == '}' && top_char != '{')) {
                return false;
            }
        }
    }
    return is_empty(&s);
}

int main() {
    const char *test1 = "a+((b+c)*5)";     // 匹配
    const char *test2 = "((a+((b+c)*5)";   // 不匹配
    
    printf("Test1: %s\n", bracket_match(test1) ? "匹配" : "不匹配");
    printf("Test2: %s\n", bracket_match(test2) ? "匹配" : "不匹配");
    return 0;
}
