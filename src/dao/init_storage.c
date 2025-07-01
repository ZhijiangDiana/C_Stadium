//
// Created by 14838 on 25-6-28.
//

#include "init_storage.h"

#define FIELD_DB_FILE          "data/field.db"
#define RESV_INFO_DB_FILE      "data/resv.db"
#define STUDENT_DB_FILE        "data/student.db"

static list_t * field_list = NULL;
static list_t * resv_info_list = NULL;
static list_t * student_list = NULL;

void init_storage() {
    // 读取所有文件，获取数据
    load_from_file(field_list, FIELD_DB_FILE, field_t_serializer);
    load_from_file(resv_info_list, RESV_INFO_DB_FILE, resv_info_t_serializer);
    load_from_file(student_list, STUDENT_DB_FILE, student_t_serializer);
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
    // 根据需要存储的类型，持久化存储对应的数据
    switch (type) {
        case FIELD_DB:
        save_to_file(field_list, FIELD_DB_FILE, field_t_deserializer);
        break;
        case RESV_INFO_DB:
        save_to_file(resv_info_list, RESV_INFO_DB_FILE, resv_info_t_deserializer);
        break;
        case STUDENT_DB:
        save_to_file(student_list, STUDENT_DB_FILE, student_t_deserializer);
        break;
        default:
        break;
    }
}
