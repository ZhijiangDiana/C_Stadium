//
// Created by 14838 on 25-6-30.
//

#include "resv_service.h"

#include <stdlib.h>
#include "field_dao.h"
#include "student_dao.h"


response_result_t get_student_resv_info(resv_dto_t dto) {
    if (dto.is_search_by_id) {
        return request_success(select_resv_by_student_id(dto.stu_id));
    }
    return request_success(select_resv_by_student_phone(dto.stu_phone));
}

response_result_t add_resv(resv_info_t info) {
    info.resv_time.minute = 0;
    info.resv_time.second = 0;

    // 获取field对象
    field_t * field = select_field_by_field_id(info.field_id);

    // 校验预约时间是否合法
    if (info.resv_hours > MAX_RESV_HOURS)
        return request_error(INPUT_ERROR, RESV_TIME_TOO_LONG);

    // 校验当前用户是否已预约过
    resv_info_t * resv_info = select_resv_by_student_id(info.stu_id);
    if (resv_info != NULL) {
        return request_error(INPUT_ERROR, RESERVE_REACH_LIMIT);
    }

    // 校验起始终止时间是否合法
    re_time_t resv_from = info.resv_time;
    re_time_t resv_to = add_hours(&resv_from, info.resv_hours);
    if (field->open_from.hour <= resv_from.hour && resv_to.hour <= field->open_to.hour) {
        // 将栈内存中的对象复制到堆内存中
        resv_info_t * db_info = malloc(sizeof(resv_info_t));
        memcpy(db_info, &info, sizeof(resv_info_t));
        insert_resv(db_info);
        return request_success(NULL);
    }

    // TODO 校验预约人数是否已满

    // 时间不合法，返回错误
    return request_error(INPUT_ERROR, RESV_TIME_ILLEGAL);
}

response_result_t cancel_resv(resv_dto_t dto) {
    // 使用学生id删除预约信息
    if (dto.is_search_by_id) {
        delete_resv_by_student_id(dto.stu_id);
        return request_success(NULL);
    }

    // 使用手机号删除预约信息
    resv_info_t * info = select_resv_by_student_phone(dto.stu_phone);
    if (info != NULL)
        delete_resv_by_student_id(info->stu_id);
    return request_success(NULL);
}
