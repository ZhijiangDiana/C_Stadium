//
// Created by 14838 on 25-6-26.
//

#ifndef TIME_REMAKE_TEST_H
#define TIME_REMAKE_TEST_H

#include <stdio.h>
#include "time_remake.h"

static inline void test_get_current_time() {
    printf("=== 当前时间 ===\n");
    re_time_t now = get_current_time();
    char buffer[64];
    format_time(&now, buffer, sizeof(buffer));
    printf("当前时间：%s\n\n", buffer);
}

static inline void test_compare_time() {
    printf("=== 时间比较 ===\n");
    re_time_t t1 = {2025, 6, 26, 10, 0, 0};
    re_time_t t2 = {2025, 6, 26, 12, 0, 0};
    int cmp = compare_time(&t1, &t2);
    printf("t1 vs t2：%d (期望 -1)\n\n", cmp);
}

static inline void test_add_subtract_hours() {
    printf("=== 时间加减 ===\n");
    re_time_t base = {2025, 6, 26, 10, 30, 0};

    re_time_t after = add_hours(&base, 5);
    re_time_t before = subtract_hours(&base, 3);

    char buf1[64], buf2[64], buf3[64];
    format_time(&base, buf1, sizeof(buf1));
    format_time(&after, buf2, sizeof(buf2));
    format_time(&before, buf3, sizeof(buf3));

    printf("基准时间：%s\n", buf1);
    printf("加5小时：%s\n", buf2);
    printf("减3小时：%s\n\n", buf3);
}

static inline void test_hour_day_start() {
    printf("=== 整点和零点时间 ===\n");

    re_time_t hour_start = get_hour_start_time();
    re_time_t day_start = get_day_start_time();

    char buf1[64], buf2[64];
    format_time(&hour_start, buf1, sizeof(buf1));
    format_time(&day_start, buf2, sizeof(buf2));

    printf("当前小时开始时间：%s\n", buf1);
    printf("今天开始时间：%s\n\n", buf2);
}

static inline void test_seconds_since_epoch() {
    printf("=== 秒数转换 ===\n");

    re_time_t now = get_current_time();
    long long seconds = get_seconds_since_epoch(&now);
    printf("当前时间对应的 Unix 秒数：%lld\n", seconds);

    re_time_t recovered = time_t_to_re_time(seconds);
    char buf[64];
    format_time(&recovered, buf, sizeof(buf));
    printf("从秒数还原的时间：%s\n\n", buf);
}

static inline void test_tm_conversion() {
    printf("=== tm 转换 ===\n");
    re_time_t now = get_current_time();
    tm std_tm = re_time_to_tm(&now);
    printf("tm结构体内容：%d-%02d-%02d %02d:%02d:%02d\n\n",
           std_tm.tm_year + 1900, std_tm.tm_mon + 1, std_tm.tm_mday,
           std_tm.tm_hour, std_tm.tm_min, std_tm.tm_sec);
}

static inline void time_remake_test() {
    test_get_current_time();
    test_compare_time();
    test_add_subtract_hours();
    test_hour_day_start();
    test_seconds_since_epoch();
    test_tm_conversion();
}

#endif //TIME_REMAKE_TEST_H
