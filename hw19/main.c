#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temp_api.h"

static void print_help(const char *prog) {
    printf("Usage:\n");
    printf("  %s -f file.csv [-m 1..12]\n", prog);
    printf("\n");
    printf("Options:\n");
    printf("  -h           Show this help\n");
    printf("  -f file.csv  Input CSV file (YEAR;MONTH;DAY;HOUR;MINUTE;TEMPERATURE)\n");
    printf("  -m month     Print stats only for this month (1..12)\n");
}

static void print_month_stats(TempNode *head, int year, int month) {
    double avg = month_avg(head, year, month);
    int mn = month_min(head, year, month);
    int mx = month_max(head, year, month);
    printf("Month %02d, year %d: avg = %.2f, min = %d, max = %d\n",
           month, year, avg, mn, mx);
}

static void print_year_stats(TempNode *head, int year) {
    double avg = year_avg(head, year);
    int mn = year_min(head, year);
    int mx = year_max(head, year);
    printf("Year %d: avg = %.2f, min = %d, max = %d\n",
           year, avg, mn, mx);
}

int main(int argc, char *argv[]) {
    const char *csvpath = NULL;
    int month_filter = 0;

    if (argc == 1) {
        print_help(argv[0]);
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            print_help(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: -f needs file name\n");
                return 1;
            }
            csvpath = argv[++i];
        } else if (strcmp(argv[i], "-m") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: -m needs month number\n");
                return 1;
            }
            month_filter = atoi(argv[++i]);
            if (month_filter < 1 || month_filter > 12) {
                fprintf(stderr, "Error: month must be 1..12\n");
                return 1;
            }
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            print_help(argv[0]);
            return 1;
        }
    }

    if (!csvpath) {
        fprintf(stderr, "Error: input CSV is required (-f file.csv)\n");
        return 1;
    }

    TempNode *head = NULL;
    int year = 0;

    if (!load_csv(&head, csvpath, &year)) {
        fprintf(stderr, "Error: cannot read CSV '%s'\n", csvpath);
        list_free(&head);
        return 1;
    }

    if (month_filter) {
        print_month_stats(head, year, month_filter);
    } else {
        for (int m = 1; m <= 12; m++) {
            print_month_stats(head, year, m);
        }
        print_year_stats(head, year);
    }

    list_free(&head);
    return 0;
}
