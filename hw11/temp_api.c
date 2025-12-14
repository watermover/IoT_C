#include "temp_api.h"

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
    int found = 0;
    int min = 0;
    for (size_t i = 0; i < size; ++i) {
        if (data[i].year == year && data[i].month == month) {
            if (!found || data[i].temperature < min) {
                min = data[i].temperature;
                found = 1;
            }
        }
    }
    return found ? min : 0;
}

int get_month_max(const TempRecord *data, size_t size, int year, int month)
{
    int found = 0;
    int max = 0;
    for (size_t i = 0; i < size; ++i) {
        if (data[i].year == year && data[i].month == month) {
            if (!found || data[i].temperature > max) {
                max = data[i].temperature;
                found = 1;
            }
        }
    }
    return found ? max : 0;
}

double get_year_avg(const TempRecord *data, size_t size, int year)
{
    long sum = 0;
    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (data[i].year == year) {
            sum += data[i].temperature;
            ++count;
        }
    }
    return count ? (double)sum / (double)count : 0.0;
}

int get_year_min(const TempRecord *data, size_t size, int year)
{
    int found = 0;
    int min = 0;
    for (size_t i = 0; i < size; ++i) {
        if (data[i].year == year) {
            if (!found || data[i].temperature < min) {
                min = data[i].temperature;
                found = 1;
            }
        }
    }
    return found ? min : 0;
}

int get_year_max(const TempRecord *data, size_t size, int year)
{
    int found = 0;
    int max = 0;
    for (size_t i = 0; i < size; ++i) {
        if (data[i].year == year) {
            if (!found || data[i].temperature > max) {
                max = data[i].temperature;
                found = 1;
            }
        }
    }
    return found ? max : 0;
}
