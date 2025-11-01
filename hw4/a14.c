#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n); // n - трёхзначное число
    int d1 = n / 100;            // первая цифра
    int d2 = (n / 10) % 10;      // вторая цифра
    int d3 = n % 10;             // третья цифра

    int max = d1;
    if (d2 > max) max = d2;
    if (d3 > max) max = d3;

    printf("%d\n", max);
    return 0;
}
