//
// Created by 14838 on 25-6-28.
//

#ifndef INIT_STORAGE_H
#define INIT_STORAGE_H

#include "dllist.h"
#include "entity.h"
#include <stdbool.h>


typedef enum _DB_TYPE {
    FIELD_DB = 0,
    RESV_INFO_DB = 1,
    STUDENT_DB = 2,
    ALL_DB = 3
} DB_TYPE;

void init_storage();
list_t * get_list(DB_TYPE type);
void store(DB_TYPE type);

#endif //INIT_STORAGE_H
