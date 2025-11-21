#include <stdio.h>

int main() {
    int arr[10];
    int i, max_i = 0, min_i = 0;
    for (i = 0; i < 10; ++i) {
        scanf("%d", &arr[i]);
        if (arr[i] > arr[max_i]) max_i = i;
        if (arr[i] < arr[min_i]) min_i = i;
    }
    printf("%d %d %d %d\n", max_i + 1, arr[max_i], min_i + 1, arr[min_i]);
    return 0;
}
