//
// Created by 14838 on 25-6-26.
//
#include "time_remake.h"
#include "stdio.h"

// 获取当前时间，并返回一个 re_time_t 结构
re_time_t get_current_time() {
    // 获取当前时间戳
    time_t now = time(NULL);
    if (now == -1) {
        re_time_t current_time = {0};
        return current_time; // 获取时间失败，返回一个空结构体
    }

    return time_t_to_re_time(now);
}

// 将 re_time_t 转换为格式化的时间字符串
int format_time(const re_time_t *time, char *buffer, size_t buffer_size) {
    if (time == NULL || buffer == NULL) {
        return -1; // 错误：传入的参数为空
    }

    // 使用 strftime 进行格式化
    tm tm_time = re_time_to_tm(time);

    // 格式化输出：例如 "2025-06-26 14:00"
    return strftime(buffer, buffer_size, "%Y-%m-%d %H:%M", &tm_time);
}

// 获取当前时间并打印为格式化字符串
int print_current_time() {
    re_time_t current_time = get_current_time();  // 获取当前时间
    char buffer[64];

    if (format_time(&current_time, buffer, sizeof(buffer)) != 0) {
        return -1; // 错误：格式化时间失败
    }

    printf("当前时间：%s\n", buffer);
    return 0; // 成功
}

// 比较两个时间，返回 -1 表示第一个时间早于第二个，0 表示相同，1 表示第一个时间晚于第二个
int compare_time(const re_time_t *time1, const re_time_t *time2) {
    if (time1 == NULL || time2 == NULL) {
        return -2; // 错误：参数为空
    }

    if (time1->year < time2->year) return -1;
    if (time1->year > time2->year) return 1;

    if (time1->month < time2->month) return -1;
    if (time1->month > time2->month) return 1;

    if (time1->day < time2->day) return -1;
    if (time1->day > time2->day) return 1;

    if (time1->hour < time2->hour) return -1;
    if (time1->hour > time2->hour) return 1;

    if (time1->minute < time2->minute) return -1;
    if (time1->minute > time2->minute) return 1;

    if (time1->second < time2->second) return -1;
    if (time1->second > time2->second) return 1;

    return 0; // 相同
}

// 获取指定时间之后多少小时的时间
re_time_t add_hours(const re_time_t *time, int hours) {
    if (time == NULL) {
        return (re_time_t){0}; // 错误：参数为空
    }

    tm tm_time = re_time_to_tm(time);

    // 使用 mktime 函数将 tm 结构转为 time_t 类型
    time_t current_time = mktime(&tm_time);
    current_time += hours * 3600; // 添加指定小时数的秒数

    // 转换回 re_time 结构
    re_time_t new_re_time = time_t_to_re_time(current_time);

    return new_re_time;
}

// 获取指定时间之前多少小时的时间
re_time_t subtract_hours(const re_time_t *time, int hours) {
    return add_hours(time, -hours);
}

// 获取当前小时开始的时间
re_time_t get_hour_start_time() {
    re_time_t current_time = get_current_time();
    current_time.minute = 0; // 将分钟设为 0
    current_time.second = 0; // 将秒数设为 0
    return current_time;
}

// 获取当天开始的时间（00:00）
re_time_t get_day_start_time() {
    re_time_t current_time = get_current_time();
    current_time.hour = 0;    // 将小时设为 0
    current_time.minute = 0;  // 将分钟设为 0
    current_time.second = 0;  // 将秒数设为 0
    return current_time;
}

// 获取 Unix 元年到当前的秒数
time_t get_seconds_epoch() {
    return time(NULL);  // time(NULL) 返回自 Unix 元年（1970年1月1日）以来的秒数
}

// 将 time_t 转换为 re_time_t
re_time_t time_t_to_re_time(time_t timestamp) {
    tm *tm_time = localtime(&timestamp);  // 获取本地时间
    re_time_t time = {
        tm_time->tm_year + 1900,
        tm_time->tm_mon + 1,
        tm_time->tm_mday,
        tm_time->tm_hour,
        tm_time->tm_min,
        tm_time->tm_sec
    };
    return time;
}

time_t re_time_to_time_t(const re_time_t *time) {
    tm tm_time = re_time_to_tm(time);
    return mktime(&tm_time);
}

tm re_time_to_tm(const re_time_t *time) {
    tm tm_time = {
        .tm_year = time->year - 1900,
        .tm_mon  = time->month - 1,
        .tm_mday = time->day,
        .tm_hour = time->hour,
        .tm_min  = time->minute,
        .tm_sec  = time->second
    };

    return tm_time;
}