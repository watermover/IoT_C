#include <stdio.h>

int main() {
    int n, prev = -1, flag = 0;
    scanf("%d", &n);
    while (n > 0) {
        int digit = n % 10;
        if (digit == prev) {
            flag = 1;
            break;
        }
        prev = digit;
        n /= 10;
    }
    if (flag)
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
