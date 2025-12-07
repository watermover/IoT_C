#include <stdio.h>

int main(void) {
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    if (!fin || !fout) return 0;

    char a[105], b[105];
    if (fscanf(fin, "%104s %104s", a, b) != 2) {
        fclose(fin);
        fclose(fout);
        return 0;
    }

    int ca[26] = {0}, cb[26] = {0};

    for (int i = 0; a[i]; ++i)
        ca[a[i] - 'a']++;

    for (int i = 0; b[i]; ++i)
        cb[b[i] - 'a']++;

    int first = 1;
    for (int i = 0; i < 26; ++i) {
        if (ca[i] == 1 && cb[i] == 1) {
            if (!first) fprintf(fout, " ");
            fputc('a' + i, fout);
            first = 0;
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
