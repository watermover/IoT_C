#ifndef TEMP_API_H
#define TEMP_API_H

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

void list_append(TempNode **head, TempRecord rec);
void list_free(TempNode **head);

int load_csv(TempNode **head, const char *path, int *out_year);

double month_avg(TempNode *head, int year, int month);
int month_min(TempNode *head, int year, int month);
int month_max(TempNode *head, int year, int month);

double year_avg(TempNode *head, int year);
int year_min(TempNode *head, int year);
int year_max(TempNode *head, int year);

#endif
