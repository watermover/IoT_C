#include <stdio.h>

int main(void) {
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    if (!fin || !fout) return 0;

    int ch;
    while ((ch = fgetc(fin)) != EOF) {
        if (ch == 'a') ch = 'b';
        else if (ch == 'b') ch = 'a';
        else if (ch == 'A') ch = 'B';
        else if (ch == 'B') ch = 'A';
        fputc(ch, fout);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
