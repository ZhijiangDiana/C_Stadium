//
// Created by 14838 on 25-6-30.
//

#ifndef FIELD_RESV_VO_H
#define FIELD_RESV_VO_H
#include "time_remake.h"

typedef struct _field_resv_vo_t {
    int field_id;
    re_time_t unit_from;
    re_time_t unit_to;
    int empty_cnt;
    int total_cnt;
    bool teacher_use;
} field_resv_vo_t;

#endif //FIELD_RESV_VO_H
