//
// Created by 14838 on 25-6-26.
//

#ifndef RESV_INFO_H
#define RESV_INFO_H

#include "time_remake.h"

typedef struct _resv_info_t {
    int stu_id;
    long long stu_phone;  // 十年OI一场空，不开longlong见祖宗
    int field_id;
    re_time_t resv_time;
    int resv_hours;
} resv_info_t;

char * resv_info_t_serializer(resv_info_t * input);
resv_info_t * resv_info_t_deserializer(char * input);

#endif //RESV_INFO_H
