//
// Created by 14838 on 25-6-26.
//

#ifndef FIELD_H
#define FIELD_H
#include "time_remake.h"

#define MAX_RESV_HOURS          2

typedef struct _field_t {
    int id;
    char name[50];
    re_time_t open_from;
    re_time_t open_to;
    int total_resv_cnt;
} field_t;

char * field_t_serializer(field_t * input);
field_t * field_t_deserializer(char * input);

#endif //FIELD_H
