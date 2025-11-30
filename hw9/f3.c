#include <stdio.h>

void print_digits_str(const char s[])
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

int main(void)
{
    char s[1005];          // до 1000 цифр + '\0'
    if (scanf("%1000s", s) != 1) return 0;
    print_digits_str(s);
    return 0;
}
