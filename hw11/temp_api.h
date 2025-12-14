#ifndef TEMP_API_H
#define TEMP_API_H

#include <stddef.h>

typedef struct {
    int year;      
    int month;   
    int day;     
    int hour;    
    int minute;    
    int temperature; 
} TempRecord;

double get_month_avg(const TempRecord *data, size_t size, int year, int month);
int    get_month_min(const TempRecord *data, size_t size, int year, int month);
int    get_month_max(const TempRecord *data, size_t size, int year, int month);

double get_year_avg(const TempRecord *data, size_t size, int year);
int    get_year_min(const TempRecord *data, size_t size, int year);
int    get_year_max(const TempRecord *data, size_t size, int year);

#endif 
