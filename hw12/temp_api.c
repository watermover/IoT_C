#include "temp_api.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ta_init(TempArray *a, size_t initial_cap)
{
    if (!a) return 0;
    if (initial_cap == 0) initial_cap = 16;
    a->data = (TempRecord*)malloc(initial_cap * sizeof(TempRecord));
    if (!a->data) return 0;
    a->size = 0;
    a->cap = initial_cap;
    return 1;
}

void ta_free(TempArray *a)
{
    if (!a) return;
    free(a->data);
    a->data = NULL;
    a->size = 0;
    a->cap = 0;
}

static int ta_grow(TempArray *a)
{
    size_t new_cap = (a->cap == 0) ? 16 : a->cap * 2;
    TempRecord *p = (TempRecord*)realloc(a->data, new_cap * sizeof(TempRecord));
    if (!p) return 0;
    a->data = p;
    a->cap = new_cap;
    return 1;
}

int ta_push_back(TempArray *a, TempRecord r)
{
    if (!a) return 0;
    if (a->size == a->cap) {
        if (!ta_grow(a)) return 0;
    }
    a->data[a->size++] = r;
    return 1;
}

int ta_remove_at(TempArray *a, size_t idx)
{
    if (!a || idx >= a->size) return 0;
    for (size_t i = idx + 1; i < a->size; ++i) {
        a->data[i - 1] = a->data[i];
    }
    a->size--;
    return 1;
}

void ta_print(const TempArray *a)
{
    if (!a) return;
    for (size_t i = 0; i < a->size; ++i) {
        const TempRecord *r = &a->data[i];
        printf("%04d-%02d-%02d %02d:%02d  %d\n",
               r->year, r->month, r->day, r->hour, r->minute, r->temperature);
    }
}

static int cmp_records(const void *pa, const void *pb)
{
    const TempRecord *a = (const TempRecord*)pa;
    const TempRecord *b = (const TempRecord*)pb;

    if (a->year != b->year) return a->year - b->year;
    if (a->month != b->month) return a->month - b->month;
    if (a->day != b->day) return a->day - b->day;
    if (a->hour != b->hour) return a->hour - b->hour;
    return a->minute - b->minute;
}

void ta_sort(TempArray *a)
{
    if (!a || a->size == 0) return;
    qsort(a->data, a->size, sizeof(a->data[0]), cmp_records);
}


int ta_load_csv(TempArray *a, const char *path)
{
    if (!a || !path) return 0;
    FILE *f = fopen(path, "r");
    if (!f) return 0;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '\n' || line[0] == '\r' || line[0] == '#')
            continue;

        char *p = strtok(line, ",");
        if (!p) continue;
        TempRecord r;

        r.year = atoi(p);
        p = strtok(NULL, ","); if (!p) continue; r.month = atoi(p);
        p = strtok(NULL, ","); if (!p) continue; r.day = atoi(p);
        p = strtok(NULL, ","); if (!p) continue; r.hour = atoi(p);
        p = strtok(NULL, ","); if (!p) continue; r.minute = atoi(p);
        p = strtok(NULL, ","); if (!p) continue; r.temperature = atoi(p);

        if (r.month < 1 || r.month > 12) continue;
        if (r.temperature < -99 || r.temperature > 99) continue;

        if (!ta_push_back(a, r)) {
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    return 1;
}

double get_month_avg(const TempRecord *data, size_t size, int year, int month)
{
    long sum = 0;
    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (data[i].year == year && data[i].month == month) {
            sum += data[i].temperature;
            ++count;
        }
    }
    return count ? (double)sum / (double)count : 0.0;
}

int get_month_min(const TempRecord *data, size_t size, int year, int month)
{
    int found = 0, mn = 0;
    for (size_t i = 0; i < size; ++i) {
        if (data[i].year == year && data[i].month == month) {
            if (!found || data[i].temperature < mn) { mn = data[i].temperature; found = 1; }
        }
    }
    return found ? mn : 0;
}

int get_month_max(const TempRecord *data, size_t size, int year, int month)
{
    int found = 0, mx = 0;
    for (size_t i = 0; i < size; ++i) {
        if (data[i].year == year && data[i].month == month) {
            if (!found || data[i].temperature > mx) { mx = data[i].temperature; found = 1; }
        }
    }
    return found ? mx : 0;
}

double get_year_avg(const TempRecord *data, size_t size, int year)
{
    long sum = 0;
    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (data[i].year == year) { sum += data[i].temperature; ++count; }
    }
    return count ? (double)sum / (double)count : 0.0;
}

int get_year_min(const TempRecord *data, size_t size, int year)
{
    int found = 0, mn = 0;
    for (size_t i = 0; i < size; ++i) {
        if (data[i].year == year) {
            if (!found || data[i].temperature < mn) { mn = data[i].temperature; found = 1; }
        }
    }
    return found ? mn : 0;
}

int get_year_max(const TempRecord *data, size_t size, int year)
{
    int found = 0, mx = 0;
    for (size_t i = 0; i < size; ++i) {
        if (data[i].year == year) {
            if (!found || data[i].temperature > mx) { mx = data[i].temperature; found = 1; }
        }
    }
    return found ? mx : 0;
}
