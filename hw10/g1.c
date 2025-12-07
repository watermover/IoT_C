#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    if (!fin || !fout) return 0;

    char s[105];              /* до 100 символов + запас */
    if (!fgets(s, sizeof(s), fin)) {
        fclose(fin);
        fclose(fout);
        return 0;
    }

    /* убираем завершающий \n или \r\n */
    int len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[--len] = '\0';
    }

    fprintf(fout, "%s, %s, %s %d", s, s, s, len);

    fclose(fin);
    fclose(fout);
    return 0;
}
