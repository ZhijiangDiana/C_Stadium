//
// Created by 14838 on 25-6-26.
//

#ifndef BOOK_INFO_H
#define BOOK_INFO_H

#include "../time_remake_ver/time_remake.h"

typedef struct _resv_info_t {
    int stu_id;
    long stu_phone;
    int pg_id;
    re_time_t resv_time;
    int resv_hours;
} resv_info_t;

#endif //BOOK_INFO_H
