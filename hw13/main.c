#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temp_api.h"

void print_help() {
    printf("Usage: temp_app -f <file.csv> [-m <month>]\n");
    printf("-h         Show this help\n");
    printf("-f <file>  Input CSV file\n");
    printf("-m <1..12> Stats for specific month\n");
}

int main(int argc, char *argv[]) {
    const char *csvpath = NULL;
    int month_filter = 0;
    TempNode *head = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            csvpath = argv[++i];
        } else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            month_filter = atoi(argv[++i]);
        }
    }

    if (!csvpath) {
        print_help();
        return 1;
    }

    if (!load_csv_to_list(&head, csvpath)) {
        fprintf(stderr, "Error: Could not read file %s\n", csvpath);
        return 1;
    }

    if (month_filter > 0) {
        printf("Month %02d: avg %.2f, min %d, max %d\n", 
               month_filter, get_month_avg(head, month_filter), 
               get_month_min(head, month_filter), get_month_max(head, month_filter));
    } else {
        for (int m = 1; m <= 12; m++) {
            double avg = get_month_avg(head, m);
            if (avg != 0.0 || get_month_min(head, m) != 0) {
                printf("Month %02d: avg %.2f, min %d, max %d\n", 
                       m, avg, get_month_min(head, m), get_month_max(head, m));
            }
        }
        printf("Year stats: avg %.2f, min %d, max %d\n", 
               get_year_avg(head), get_year_min(head), get_year_max(head));
    }

    list_clear(&head);
    return 0;
}
