//
// Created by 14838 on 25-6-28.
//

#ifndef STUDENT_DAO_H
#define STUDENT_DAO_H

#include "student.h"
#include "dllist.h"


void insert_student(student_t * student);
list_t * select_all_student();
student_t * select_student_by_student_id(int id);
student_t * select_student_by_student_phone(long phone);

#endif //STUDENT_DAO_H
