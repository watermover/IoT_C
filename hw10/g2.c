#include <stdio.h>

int main(void) {
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    if (!fin || !fout) return 0;

    int N;
    if (fscanf(fin, "%d", &N) != 1) {
        fclose(fin);
        fclose(fout);
        return 0;
    }

    char evenDigits[] = {'2','4','6','8'};
    int dCnt = 4;                 /* количество разных чётных цифр */

    for (int i = 0; i < N; ++i) {
        if ((i % 2) == 0) {
            /* нечётная позиция (1,3,5...) -> буква */
            char ch = 'A' + (i / 2);
            fputc(ch, fout);
        } else {
            /* чётная позиция -> чётная цифра по кругу 2,4,6,8 */
            char dig = evenDigits[(i / 2) % dCnt];
            fputc(dig, fout);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
