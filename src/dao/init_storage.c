//
// Created by 14838 on 25-6-28.
//

#include "init_storage.h"


static list_t * field_list = NULL;
static list_t * resv_info_list = NULL;
static list_t * student_list = NULL;

void init_storage() {
    // TODO 读取所有文件，获取数据

    field_list = init_list();
    resv_info_list = init_list();
    student_list = init_list();
}

list_t* get_list(DB_TYPE type) {
    switch (type) {
        case FIELD_DB:
            return field_list;
        case RESV_INFO_DB:
            return resv_info_list;
        case STUDENT_DB:
            return student_list;
        default:
            return NULL;
    }
}

void store(DB_TYPE type) {
    // TODO 根据需要存储的类型，持久化存储对应的数据
}
