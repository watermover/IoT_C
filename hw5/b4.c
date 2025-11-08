#include <stdio.h>

int main() {
    int n, count = 0;
    scanf("%d", &n);
    while (n > 0) {
        count++;
        n /= 10;
    }
    if (count == 3)
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
