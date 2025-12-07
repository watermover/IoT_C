#include <stdio.h>
#include <string.h>

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
    // убираем \r и \n в конце
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[--len] = '\0';
    }

    if (len == 0) {
        fclose(fin);
        fclose(fout);
        return 0;
    }

    char last = s[len - 1];

    int first = 1;
    for (int i = 0; i < len - 1; ++i) {    
        if (s[i] == last) {
            if (!first) fprintf(fout, " ");
            fprintf(fout, "%d", i);          
            first = 0;
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
