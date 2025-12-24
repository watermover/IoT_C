#ifndef TEMP_API_H
#define TEMP_API_H

#include <stddef.h>

typedef struct TempRecord {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int temperature;
} TempRecord;

typedef struct TempNode {
    TempRecord data;
    struct TempNode *next;
} TempNode;

// Управление списком
void list_add(TempNode **head, TempRecord record);
void list_clear(TempNode **head);

// Загрузка данных
int load_csv_to_list(TempNode **head, const char *path);

// Статистика (по месяцам)
double get_month_avg(TempNode *head, int month);
int get_month_min(TempNode *head, int month);
int get_month_max(TempNode *head, int month);

// Статистика (за год)
double get_year_avg(TempNode *head);
int get_year_min(TempNode *head);
int get_year_max(TempNode *head);

#endif
