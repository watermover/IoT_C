#include <stdio.h>

void to_binary(int n) {
    if (n < 2) {
        printf("%d", n);
    } else {
        to_binary(n / 2);
        printf("%d", n % 2);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    to_binary(n);
    return 0;
}
