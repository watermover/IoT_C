#include <stdio.h>

void print_digit(char s[])
{
    int cnt[10] = {0};
    int i, d;

    for (i = 0; s[i] != '\0'; i++)
        if (s[i] >= '0' && s[i] <= '9')
        {
            d = s[i] - '0';
            cnt[d]++;
        }

    for (d = 0; d <= 9; d++)
        if (cnt[d] > 0)
            printf("%d %d\n", d, cnt[d]);
}
