#include <stdio.h>

int adder() {
    int i;
    return i + 1;
}

int assign() {
    int y = 100;
    return y;
}

int main(void) {
    int x;
    assign();
    x = adder();
    printf("The value of x is: %d\n", x);
    return 0;
}
