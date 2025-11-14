#include <stdio.h>

int sumFrom1ToN(int n) {
    if (n == 1) {
        return 1;
    }
    return n + sumFrom1ToN(n - 1);
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", sumFrom1ToN(n));
    return 0;
}
