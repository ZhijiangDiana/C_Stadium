//
// Created by 14838 on 25-7-1.
//

#ifndef FIELD_RESV_VIEW_H
#define FIELD_RESV_VIEW_H
#include <stdbool.h>

#include "student.h"
#include "field_resv_vo.h"


void field_menu(bool need_resv);    // 场地选择界面
void resv_field_menu(int field_id, bool need_resv);  // 场次选择界面
void student_find_menu(field_resv_vo_t * vo, int hours);    // 学生查询界面
void check_menu(student_t * stu, field_resv_vo_t * vo, int hours);

#endif //FIELD_RESV_VIEW_H
