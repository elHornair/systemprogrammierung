#include <stdio.h>
#include <string.h>

#define STACKSIZE 99

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
    char myString[STACKSIZE];
    int i = 0;

    scanf("%s", myString);

    while(myString[i] != '\0') {
        if (myString[i] == '(') {
            push('(');
        } else if (myString[i] == ')') {
            if (!pop()) {
                printf("Incorrect parantheses!\n");
            return 0;
            }
        } else {
            printf("Unknown character: %c\n", myString[i]);
            return 0;
        }
	    i++;
	}

    if (peek()) {
        printf("Incorrect parantheses!\n");
    } else {
        printf("Everything ok. Have a cookie.\n");
    }

    return 0;
}
