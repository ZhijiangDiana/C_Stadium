//
// Created by 14838 on 25-6-30.
//

#ifndef RESV_DAO_H
#define RESV_DAO_H

#include "resv_info.h"
#include "dllist.h"


void insert_resv(resv_info_t * resv);
void delete_resv_by_student_id(int id);
list_t * select_all_resv();
list_t * select_resv_by_field_and_time(int field_id, re_time_t day);
resv_info_t * select_resv_by_student_id(int id);
resv_info_t * select_resv_by_student_phone(long long phone);

#endif //RESV_DAO_H
