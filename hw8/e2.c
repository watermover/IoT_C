#include <stdio.h>

int main() {
    int arr[5];
    int min;
    for (int i = 0; i < 5; i++) {
        scanf("%d", &arr[i]);
        if (i == 0)
            min = arr[i];
        else if (arr[i] < min)
            min = arr[i];
    }
    printf("%d\n", min);
    return 0;
}
