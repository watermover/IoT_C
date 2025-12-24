#include "temp_api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void list_add(TempNode **head, TempRecord record) {
    TempNode *new_node = malloc(sizeof(TempNode));
    if (!new_node) return;
    new_node->data = record;
    new_node->next = *head;
    *head = new_node;
}

void list_clear(TempNode **head) {
    TempNode *current = *head;
    while (current) {
        TempNode *next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

int load_csv_to_list(TempNode **head, const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return 0;
    char line[256];
    TempRecord r;
    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "%d,%d,%d,%d,%d,%d", &r.year, &r.month, &r.day, &r.hour, &r.minute, &r.temperature) == 6) {
            list_add(head, r);
        }
    }
    fclose(f);
    return 1;
}

double get_month_avg(TempNode *head, int month) {
    long sum = 0;
    int count = 0;
    for (TempNode *curr = head; curr != NULL; curr = curr->next) {
        if (curr->data.month == month) {
            sum += curr->data.temperature;
            count++;
        }
    }
    return count > 0 ? (double)sum / count : 0.0;
}

int get_month_min(TempNode *head, int month) {
    int min = INT_MAX;
    int found = 0;
    for (TempNode *curr = head; curr != NULL; curr = curr->next) {
        if (curr->data.month == month) {
            if (curr->data.temperature < min) min = curr->data.temperature;
            found = 1;
        }
    }
    return found ? min : 0;
}

int get_month_max(TempNode *head, int month) {
    int max = INT_MIN;
    int found = 0;
    for (TempNode *curr = head; curr != NULL; curr = curr->next) {
        if (curr->data.month == month) {
            if (curr->data.temperature > max) max = curr->data.temperature;
            found = 1;
        }
    }
    return found ? max : 0;
}

double get_year_avg(TempNode *head) {
    long sum = 0;
    int count = 0;
    for (TempNode *curr = head; curr != NULL; curr = curr->next) {
        sum += curr->data.temperature;
        count++;
    }
    return count > 0 ? (double)sum / count : 0.0;
}

int get_year_min(TempNode *head) {
    int min = INT_MAX;
    if (!head) return 0;
    for (TempNode *curr = head; curr != NULL; curr = curr->next) {
        if (curr->data.temperature < min) min = curr->data.temperature;
    }
    return min;
}

int get_year_max(TempNode *head) {
    int max = INT_MIN;
    if (!head) return 0;
    for (TempNode *curr = head; curr != NULL; curr = curr->next) {
        if (curr->data.temperature > max) max = curr->data.temperature;
    }
    return max;
}
