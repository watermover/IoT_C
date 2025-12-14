#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "temp_api.h"

static void print_help(const char *prog)
{
    printf("Usage:\n");
    printf("  %s -h\n", prog);
    printf("  %s -f <file.csv> [-m <1..12>]\n", prog);
    printf("\nOptions:\n");
    printf("  -h            Show this help\n");
    printf("  -f <file>     Input CSV file\n");
    printf("  -m <month>    Print stats only for this month (1..12)\n");
}

static int detect_year(const TempArray *a)
{
    /* по заданию не уточнено, как выбирать год;
       сделаем: берем год первой записи */
    if (!a || a->size == 0) return 0;
    return a->data[0].year;
}

static void print_month_stats(const TempArray *a, int year, int month)
{
    printf("Month %02d, year %d:\n", month, year);
    printf("  avg = %.2f\n", get_month_avg(a->data, a->size, year, month));
    printf("  min = %d\n",    get_month_min(a->data, a->size, year, month));
    printf("  max = %d\n",    get_month_max(a->data, a->size, year, month));
}

static void print_year_stats(const TempArray *a, int year)
{
    printf("Year %d:\n", year);
    printf("  avg = %.2f\n", get_year_avg(a->data, a->size, year));
    printf("  min = %d\n",    get_year_min(a->data, a->size, year));
    printf("  max = %d\n",    get_year_max(a->data, a->size, year));
}

int main(int argc, char **argv)
{
    const char *csv_path = NULL;
    int month_filter = 0;

    if (argc == 1) {
        print_help(argv[0]);
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0) {
            print_help(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 >= argc) { fprintf(stderr, "Error: -f needs a file\n"); return 1; }
            csv_path = argv[++i];
        } else if (strcmp(argv[i], "-m") == 0) {
            if (i + 1 >= argc) { fprintf(stderr, "Error: -m needs month number\n"); return 1; }
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

    if (!csv_path) {
        fprintf(stderr, "Error: input CSV is required (-f <file.csv>)\n");
        return 1;
    }

    TempArray arr;
    if (!ta_init(&arr, 64)) {
        fprintf(stderr, "Error: no memory\n");
        return 1;
    }

    if (!ta_load_csv(&arr, csv_path)) {
        fprintf(stderr, "Error: cannot read CSV: %s\n", csv_path);
        ta_free(&arr);
        return 1;
    }

    ta_sort(&arr);

    int year = detect_year(&arr);
    if (year == 0) {
        fprintf(stderr, "No data\n");
        ta_free(&arr);
        return 1;
    }

    if (month_filter) {
        print_month_stats(&arr, year, month_filter);
    } else {
        for (int m = 1; m <= 12; ++m) {
            print_month_stats(&arr, year, m);
        }
        print_year_stats(&arr, year);
    }

    ta_free(&arr);
    return 0;
}
