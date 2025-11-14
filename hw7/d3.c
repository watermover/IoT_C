#include <stdio.h>

void printDigitsReversed(int n) {
    printf("%d", n % 10);
    if (n >= 10) {
        printf(" ");
        printDigitsReversed(n / 10);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    printDigitsReversed(n);
    return 0;
}
