#include <stdio.h>

void printFrom1ToN(int n) {
    if (n == 0) {
        return;
    }
    printFrom1ToN(n - 1);
    printf("%d ", n);
}

int main() {
    int n;
    scanf("%d", &n);
    printFrom1ToN(n);
    return 0;
}
