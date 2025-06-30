//
// Created by 14838 on 25-6-30.
//

#ifndef RESV_DTO_H
#define RESV_DTO_H
#include <stdbool.h>

typedef struct _resv_dto_t {
    int stu_id;
    long long stu_phone;
    bool is_search_by_id;
} resv_dto_t;

typedef struct _field_resv_info_dto_t {
    int field_id;
    re_time_t time;
} field_resv_info_dto_t;

#endif //RESV_DTO_H
