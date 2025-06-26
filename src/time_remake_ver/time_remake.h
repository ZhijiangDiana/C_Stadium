//
// Created by 14838 on 25-6-26.
//

#ifndef TIME_REMAKE_H
#define TIME_REMAKE_H
#include <stddef.h>
#include "time.h"

// 比time.h的实现的更直观更好用
typedef struct _re_time_t {
    int year;
    int month;   // 1~12
    int day;     // 1~31
    int hour;    // 0~23
    int minute;  // 0~59
    int second;  // 0~59
} re_time_t;

typedef struct tm tm;

re_time_t get_current_time();
int format_time(const re_time_t *time, char *buffer, size_t buffer_size);
int print_current_time();

int compare_time(const re_time_t *time1, const re_time_t *time2);
re_time_t add_hours(const re_time_t *time, int hours);
re_time_t subtract_hours(const re_time_t *time, int hours);
re_time_t get_hour_start_time();
re_time_t get_day_start_time();
long long get_seconds_since_epoch();
long long re_time_to_seconds_since_epoch(const re_time_t *time);
re_time_t time_t_to_re_time(time_t timestamp);
time_t re_time_to_time_t(const re_time_t *time);
tm re_time_to_tm(const re_time_t *time);

#endif //TIME_REMAKE_H
