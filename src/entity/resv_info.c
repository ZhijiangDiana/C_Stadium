//
// Created by 14838 on 25-7-1.
//
#include "resv_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* resv_info_t_serializer(resv_info_t* input) {
    // 预分配一个足够大的缓冲区
    char* buffer = malloc(512);

    // 临时缓冲区用于格式化时间
    char time_buffer[64];
    format_time(&(input->resv_time), time_buffer, sizeof(time_buffer));

    // 将各个字段拼接到缓冲区中
    sprintf(buffer, "%d %lld %d %s %d", input->stu_id, input->stu_phone, input->field_id, time_buffer, input->resv_hours);

    return buffer;  // 返回构造的字符串
}

resv_info_t* resv_info_t_deserializer(char* input) {
    resv_info_t* result = malloc(sizeof(resv_info_t));

    // 临时缓冲区
    char time_buffer[64];

    // 使用 strtok 拆分输入字符串
    char* token = strtok(input, " ");
    result->stu_id = atoi(token);  // 学生ID

    token = strtok(NULL, " ");
    result->stu_phone = atoll(token);  // 学生电话

    token = strtok(NULL, " ");
    result->field_id = atoi(token);  // 场地ID

    token = strtok(NULL, " ");
    strncpy(time_buffer, token, sizeof(time_buffer) - 1);  // 时间字符串
    time_buffer[sizeof(time_buffer) - 1] = '\0';

    // 将时间字符串解析为 re_time_t
    sscanf(time_buffer, "%d-%d-%d %d:%d",
           &result->resv_time.year, &result->resv_time.month, &result->resv_time.day,
           &result->resv_time.hour, &result->resv_time.minute);
    result->resv_time.second = 0;

    token = strtok(NULL, " ");
    result->resv_hours = atoi(token);  // 预约时长

    return result;  // 返回反序列化后的结构体

}
