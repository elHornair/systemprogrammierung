#include <stdio.h>

#define STACKSIZE 10

struct c_stack {
    char data[STACKSIZE];
    int size;
} stack;

char push(char c) {
    if (stack.size == STACKSIZE)
        return 0;
    return stack.data[stack.size++] = c;
}

char pop() {
    if (stack.size == 0)
        return 0;
    return stack.data[--stack.size];
}

char peek() {
    if (stack.size == 0)
        return 0;
    return stack.data[stack.size-1];
}

int main(void) {
    printf("pushing a: %c\n", push('a'));
    printf("pushing b: %c\n", push('b'));
    printf("peeking  : %c\n", peek());
    printf("popping  : %c\n", pop());
    printf("peeking  : %c\n", peek());
    return 0;
}
