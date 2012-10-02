#include <stdio.h>

void some_subroutine(int b) {
  b = b - 1;
  printf("Sub: %d\n", b);
}

int main(void) {
  int a = 10;

  printf("Main 1: %d\n", a);
  some_subroutine(a);
  printf("Main 2: %d\n", a);
}

