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
    re_time_t * resv_time = &input->resv_time;
    sprintf(time_buffer, "%02d-%02d-%02dT%02d:%02d:%02d",
        resv_time->year, resv_time->month, resv_time->day,
        resv_time->hour, resv_time->minute, resv_time->second);

    // 将各个字段拼接到缓冲区中
    sprintf(buffer, "%d %lld %d %s %d", input->stu_id, input->stu_phone, input->field_id, time_buffer, input->resv_hours);

    return buffer;  // 返回构造的字符串
}

resv_info_t* resv_info_t_deserializer(char* input) {
    resv_info_t* result = malloc(sizeof(resv_info_t));

    char time_buffer[64];
    sscanf_s(input, "%d %lld %d %63s %d",  // 限定 %s 最大长度
             &result->stu_id,
             &result->stu_phone,
             &result->field_id,
             time_buffer, sizeof(time_buffer),
             &result->resv_hours);

    sscanf_s(time_buffer, "%d-%d-%dT%d:%d:%d",
             &result->resv_time.year, &result->resv_time.month, &result->resv_time.day,
             &result->resv_time.hour, &result->resv_time.minute, &result->resv_time.second);
    // result->stu_id = i;
    // result->stu_phone = i;
    // result->field_id = i;
    // result->resv_hours = i;
    // i++;

    return result;
}
