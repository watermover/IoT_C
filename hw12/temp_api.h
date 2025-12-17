#ifndef TEMP_API_H
#define TEMP_API_H

#include <stddef.h>

typedef struct {
    int year;        /* dddd */
    int month;       /* 1..12 */
    int day;         /* 1..31 */
    int hour;        /* 0..23 */
    int minute;      /* 0..59 */
    int temperature; /* -99..99 */
} TempRecord;

typedef struct {
    TempRecord *data;
    size_t size;
    size_t cap;
} TempArray;

int  ta_init(TempArray *a, size_t initial_cap);
void ta_free(TempArray *a);
int  ta_push_back(TempArray *a, TempRecord r);
int  ta_remove_at(TempArray *a, size_t idx);
void ta_print(const TempArray *a);
void ta_sort(TempArray *a);

int  ta_load_csv(TempArray *a, const char *path);

double get_month_avg(const TempRecord *data, size_t size, int year, int month);
int    get_month_min(const TempRecord *data, size_t size, int year, int month);
int    get_month_max(const TempRecord *data, size_t size, int year, int month);

double get_year_avg(const TempRecord *data, size_t size, int year);
int    get_year_min(const TempRecord *data, size_t size, int year);
int    get_year_max(const TempRecord *data, size_t size, int year);

#endif
