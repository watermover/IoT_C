#include <stdio.h>
#include "temp_api.h"

int main(void)
{
    TempRecord records[] = {
        {2025, 1,  1,  8, 30, -5},
        {2025, 1,  1, 14, 15,  0},
        {2025, 1, 15, 12,  0, -2},
        {2025, 2,  1,  9, 45,  3},
        {2025, 2, 10, 18, 10,  5},
        {2025, 2, 28, 23, 50, -1},
        {2025, 3,  5, 13, 20, 10},
        {2025, 3, 20, 16, 40,  7}
    };

    size_t size = sizeof(records) / sizeof(records[0]);
    int year = 2025;
    int month = 2;

    printf("Month %d %d:\n", month, year);
    printf("  avg = %.2f\n", get_month_avg(records, size, year, month));
    printf("  min = %d\n",    get_month_min(records, size, year, month));
    printf("  max = %d\n",    get_month_max(records, size, year, month));

    printf("Year %d:\n", year);
    printf("  avg = %.2f\n", get_year_avg(records, size, year));
    printf("  min = %d\n",    get_year_min(records, size, year));
    printf("  max = %d\n",    get_year_max(records, size, year));

    return 0;
}
