//
// Created by 14838 on 25-6-30.
//

#include "field_service.h"
#include "field_dao.h"
#include "resv_dao.h"


response_result_t add_field(field_t field) {
    field_t * db_field = malloc(sizeof(field_t));
    memcpy(db_field, &field, sizeof(field_t));

    insert_field(db_field);
    return request_success(NULL);
}

response_result_t list_all_field() {
    list_t * res = select_all_field();
    return request_success(res);
}

response_result_t get_field_by_id(int id) {
    field_t * field = select_field_by_field_id(id);
    return request_success(field);
}

list_t * three_day_vos[3];
response_result_t list_field_three_days_resv(field_resv_info_dto_t dto) {
    dto.time.minute = 0;
    dto.time.second = 0;

    // 1. 查询field信息
    field_t * field = select_field_by_field_id(dto.field_id);

    // 2. 求出当天开始，三天之内的预约vo列表
    for (int i = 0; i < 3; ++i, dto.time.day++) {
        three_day_vos[i] = list_field_resv(*field, dto.time);
    }

    return request_success(three_day_vos);
}

list_t * list_field_resv(field_t field, re_time_t time) {
    // 1. 列出当天场馆所有预约记录
    list_t * resv_list = select_resv_by_field_and_time(field.id, time);

    // 获取field当天开始结束时间
    re_time_t field_start_time = get_field_start_time(time);

    // 2. 初始化VO列表
    list_t * vo_list = init_list();
    int unit_cnt = field.open_to.hour - field_start_time.hour;
    for (int i = 0; i < unit_cnt; i++) {
        // 初始化结构体
        field_resv_vo_t resv_vo = {field.id, {0}, {0}, field.total_resv_cnt, field.total_resv_cnt};
        // 设定时间
        resv_vo.unit_from = time;
        resv_vo.unit_from.hour = field_start_time.hour + i;
        resv_vo.unit_from.minute = 0;
        resv_vo.unit_to = time;
        resv_vo.unit_to.hour = field_start_time.hour + i + 1;
        resv_vo.unit_to.minute = 0;
        // 设定是否是教职工使用
        resv_vo.teacher_use = is_teacher_use_hour(&resv_vo.unit_from) && is_teacher_use_hour(&resv_vo.unit_to);

        // 将栈内存复制到堆内存
        field_resv_vo_t * db_vo = malloc(sizeof(field_resv_vo_t));
        memcpy(db_vo, &resv_vo, sizeof(field_resv_vo_t));

        // 加入列表
        push_back(vo_list, db_vo);
    }

    // 3. 根据预约记录，扣减对应的名额
    list_iterator_t * itr = init_iterator(resv_list);
    while (has_next(itr)) {
        // 获取下一条预约记录
        resv_info_t * resv = next(itr);
        // 获取需要更改的index
        int start_index = resv->resv_time.hour - field_start_time.hour;
        // 更改empty_cnt
        for (int i = 0; i < resv->resv_hours; ++i) {
            field_resv_vo_t * vo = get_item(vo_list, start_index + i);
            vo->empty_cnt--;
        }
    }
    destroy_iterator(itr);

    // 4. 返回list
    return vo_list;
}

bool is_teacher_use_hour(re_time_t * time) {
    int day = get_day_of_week(time);

    if (day == 1 || day == 3 || day == 5) {
        if (17 <= time->hour && time->hour <= 20) {
            return true;
        }
    }
    return false;
}

re_time_t get_field_start_time(re_time_t time) {
    int day = get_day_of_week(&time);

    if (1 <= day && day <= 5) {
        time.hour = 15;
        time.minute = 0;
        time.second = 0;
        return time;
    }
    time.hour = 9;
    time.minute = 0;
    time.second = 0;
    return time;
}
