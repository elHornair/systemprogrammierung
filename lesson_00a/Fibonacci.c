#include <stdio.h>

/* calculates fibonacci */ 
int main() {
    int n;
    scanf("%d",&n);
    printf("%d\n", fibonacci(n));
    return 0;
}

int fibonacci(int n) {
    int a = 0;
    int b = 1;
    int sum;
    int i;

    for (i=0; i<n; i++) {
        sum = a + b;
        a = b;
        b = sum;
    }

    return sum;
}
