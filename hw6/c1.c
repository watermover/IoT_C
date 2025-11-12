#include <stdio.h>

int abs_value(int n) {
    if (n < 0)
        return -n;
    else
        return n;
}

int main() {
    int x;
    scanf("%d", &x);          
    printf("%d\n", abs_value(x)); 
    return 0;
}
