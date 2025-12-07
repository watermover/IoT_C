#include <stdio.h>
#include <string.h>

int is_palindrom(const char *s) {
    int i = 0;
    int j = (int)strlen(s) - 1;
    while (i < j) {
        if (s[i] != s[j]) return 0;
        ++i;
        --j;
    }
    return 1;
}

int main(void) {
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    if (!fin || !fout) return 0;

    char s[1005];
    if (!fgets(s, sizeof(s), fin)) {
        fclose(fin);
        fclose(fout);
        return 0;
    }

    int len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[--len] = '\0';
    }

    if (is_palindrom(s))
        fprintf(fout, "YES");
    else
        fprintf(fout, "NO");

    fclose(fin);
    fclose(fout);
    return 0;
}
