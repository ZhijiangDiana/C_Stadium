//
// Created by 14838 on 25-6-30.
//

#ifndef STUDENT_SERVICE_H
#define STUDENT_SERVICE_H

#include "student_dao.h"
#include "response_result.h"

response_result_t add_new_student(student_t dto);
response_result_t get_student_by_id(int stu_id);

#endif //STUDENT_SERVICE_H
