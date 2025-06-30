//
// Created by 14838 on 25-6-30.
//

#include "student_service.h"

#include <stdlib.h>
#include <string.h>

response_result_t add_new_student(student_t * dto) {
    // 参数判空
    if (strlen(dto->name) == 0)
        return request_error(INPUT_ERROR, INVALID_PARAM);

    // 避免重复
    student_t * duplicate = select_student_by_student_id(dto->id);
    if (duplicate != NULL) {
        return request_error(INPUT_ERROR, STU_ID_EXISTS);
    }
    duplicate = select_student_by_student_phone(dto->phone);
    if (duplicate != NULL) {
        return request_error(INPUT_ERROR, STU_PHONE_EXISTS);
    }

    // 组装实体
    student_t * student = malloc(sizeof(student_t));
    student->id = dto->id;
    strcpy(student->name, dto->name);
    student->gender = dto->gender;
    student->phone = dto->phone;

    // 执行插入
    insert_student(student);

    // 返回结果
    return request_success(NULL);
}
