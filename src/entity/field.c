//
// Created by 14838 on 25-7-1.
//
#include "field.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* field_t_serializer(field_t* input) {
    // 预分配一个足够大的缓冲区
    char* buffer = malloc(512);

    // 临时缓冲区用于格式化时间
    char time_buffer[64];

    // 格式化起始时间
    char open_from_str[64];
    sprintf(open_from_str, "%d-%d-%dT%d:%d",
        input->open_from.year, input->open_from.month, input->open_from.day,
        input->open_from.hour, input->open_from.minute);
    open_from_str[sizeof(open_from_str) - 1] = '\0';

    // 格式化终止时间
    char open_to_str[64];
    sprintf(open_to_str, "%d-%d-%dT%d:%d",
        input->open_to.year, input->open_to.month, input->open_to.day,
        input->open_to.hour, input->open_to.minute);
    open_to_str[sizeof(open_to_str) - 1] = '\0';

    // 将各个字段拼接到缓冲区中
    sprintf(buffer, "%d %s %s %s %d", input->id, input->name, open_from_str, open_to_str, input->total_resv_cnt);

    return buffer;  // 返回构造的字符串
}

field_t* field_t_deserializer(char* input) {
    field_t* result = (field_t*)malloc(sizeof(field_t));
    if (!result) {
        return NULL;
    }

    // 临时缓冲区
    char time_buffer[64];

    // 使用 strtok 拆分输入字符串
    char* token = strtok(input, " ");
    result->id = atoi(token);  // 场地ID

    token = strtok(NULL, " ");
    strncpy(result->name, token, sizeof(result->name) - 1);  // 场地名称
    result->name[sizeof(result->name) - 1] = '\0';

    token = strtok(NULL, " ");
    strncpy(time_buffer, token, sizeof(time_buffer) - 1);  // open_from 时间
    time_buffer[sizeof(time_buffer) - 1] = '\0';
    sscanf_s(time_buffer, "%d-%d-%dT%d:%d",
              &result->open_from.year, &result->open_from.month, &result->open_from.day,
              &result->open_from.hour, &result->open_from.minute);
    result->open_from.second = 0;

    token = strtok(NULL, " ");
    strncpy(time_buffer, token, sizeof(time_buffer) - 1);  // open_to 时间
    time_buffer[sizeof(time_buffer) - 1] = '\0';
    sscanf_s(time_buffer, "%d-%d-%dT%d:%d",
          &result->open_to.year, &result->open_to.month, &result->open_to.day,
          &result->open_to.hour, &result->open_to.minute);
    result->open_to.second = 0;

    token = strtok(NULL, " ");
    result->total_resv_cnt = atoi(token);  // 总预定次数

    return result;  // 返回反序列化后的结构体
}
