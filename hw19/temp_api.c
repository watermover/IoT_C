#include "temp_api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void list_append(TempNode **head, TempRecord rec) {
    TempNode *node = (TempNode *)malloc(sizeof(TempNode));
    if (!node) return;
    node->data = rec;
    node->next = NULL;

    if (!*head) {
        *head = node;
        return;
    }
    TempNode *cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = node;
}

void list_free(TempNode **head) {
    TempNode *cur = *head;
    while (cur) {
        TempNode *next = cur->next;
        free(cur);
        cur = next;
    }
    *head = NULL;
}

static int parse_line(const char *line, TempRecord *out) {
    char *tmp = strdup(line);
    if (!tmp) return 0;
    char *p = tmp;
    char *tok;
    int vals[6];
    int i = 0;

    while ((tok = strsep(&p, ";")) != NULL && i < 6) {
        if (*tok == '\0' || tok[0] == '\n' || tok[0] == '\r')
            break;
        vals[i++] = atoi(tok);
    }
    free(tmp);
    if (i != 6) return 0;

    out->year        = vals[0];
    out->month       = vals[1];
    out->day         = vals[2];
    out->hour        = vals[3];
    out->minute      = vals[4];
    out->temperature = vals[5];

    if (out->month < 1 || out->month > 12) return 0;
    if (out->day < 1 || out->day > 31) return 0;
    if (out->hour < 0 || out->hour > 23) return 0;
    if (out->minute < 0 || out->minute > 59) return 0;
    if (out->temperature < -99 || out->temperature > 99) return 0;
    return 1;
}

int load_csv(TempNode **head, const char *path, int *out_year) {
    FILE *f = fopen(path, "r");
    if (!f) return 0;

    char line[256];
    int year_set = 0;

    while (fgets(line, sizeof(line), f)) {
        TempRecord rec;
        if (!parse_line(line, &rec)) {
            continue;
        }
        if (!year_set) {
            *out_year = rec.year;
            year_set = 1;
        }
        list_append(head, rec);
    }

    fclose(f);
    return year_set ? 1 : 0;
}

static void month_stats_core(TempNode *head, int year, int month,
                             long *sum, int *cnt, int *mn, int *mx) {
    *sum = 0;
    *cnt = 0;
    *mn  = INT_MAX;
    *mx  = INT_MIN;

    for (TempNode *cur = head; cur; cur = cur->next) {
        TempRecord r = cur->data;
        if (r.year == year && r.month == month) {
            *sum += r.temperature;
            (*cnt)++;
            if (r.temperature < *mn) *mn = r.temperature;
            if (r.temperature > *mx) *mx = r.temperature;
        }
    }
}

double month_avg(TempNode *head, int year, int month) {
    long sum; int cnt, mn, mx;
    month_stats_core(head, year, month, &sum, &cnt, &mn, &mx);
    return cnt ? (double)sum / (double)cnt : 0.0;
}

int month_min(TempNode *head, int year, int month) {
    long sum; int cnt, mn, mx;
    month_stats_core(head, year, month, &sum, &cnt, &mn, &mx);
    return cnt ? mn : 0;
}

int month_max(TempNode *head, int year, int month) {
    long sum; int cnt, mn, mx;
    month_stats_core(head, year, month, &sum, &cnt, &mn, &mx);
    return cnt ? mx : 0;
}

double year_avg(TempNode *head, int year) {
    long sum = 0;
    int cnt = 0;
    for (TempNode *cur = head; cur; cur = cur->next) {
        if (cur->data.year == year) {
            sum += cur->data.temperature;
            cnt++;
        }
    }
    return cnt ? (double)sum / (double)cnt : 0.0;
}

int year_min(TempNode *head, int year) {
    int mn = INT_MAX;
    int found = 0;
    for (TempNode *cur = head; cur; cur = cur->next) {
        if (cur->data.year == year) {
            if (cur->data.temperature < mn) mn = cur->data.temperature;
            found = 1;
        }
    }
    return found ? mn : 0;
}

int year_max(TempNode *head, int year) {
    int mx = INT_MIN;
    int found = 0;
    for (TempNode *cur = head; cur; cur = cur->next) {
        if (cur->data.year == year) {
            if (cur->data.temperature > mx) mx = cur->data.temperature;
            found = 1;
        }
    }
    return found ? mx : 0;
}
