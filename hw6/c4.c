#include <stdio.h>

int f(int x) {
    if (x >= -2 && x < 2)
        return x * x;
    else if (x >= 2)
        return x * x + 4 * x + 5;
    else
        return 4;
}

int main() {
    int x, max = -2147483648; 
    while (scanf("%d", &x) && x != 0) {
        int val = f(x);
        if (val > max)
            max = val;
    }
    printf("%d\n", max);
    return 0;
}
