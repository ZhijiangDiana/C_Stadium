//
// Created by 14838 on 25-6-30.
//

#include "resv_dao.h"
#include "init_storage.h"
#include "dllist_iterator.h"

// 插入的实体不能位于栈区
void insert_resv(resv_info_t* resv) {
    list_t * resv_list = get_list(RESV_INFO_DB);

    push_back(resv_list, resv);
}

void delete_resv_by_student_id(int id) {
    list_t * resv_list = get_list(RESV_INFO_DB);

    list_iterator_t * itr = init_iterator(resv_list);
    int index = 0;
    while (has_next(itr)) {
        resv_info_t * stu = next(itr);
        if (id == ((resv_info_t *) stu)->stu_id)
            break;
        index++;
    }
    destroy_iterator(itr);

    del_item(resv_list, index);
}

// 不要释放！！！！！不要释放！！！！！
list_t* select_all_resv() {
    return get_list(RESV_INFO_DB);
}

// 可以释放链表，但是不能释放数据
list_t* select_resv_by_field_and_time(int field_id, re_time_t day) {
    list_t * resv_list = get_list(RESV_INFO_DB);

    list_t * res_list = init_list();

    list_iterator_t * itr = init_iterator(resv_list);
    int index = 0;
    while (has_next(itr)) {
        resv_info_t * resv = next(itr);
        re_time_t resv_time = resv->resv_time;
        if (resv_time.year == day.year && resv_time.month == day.month && resv_time.day == day.day)
            if (field_id == resv->field_id)
                push_back(res_list, resv);
        index++;
    }
    destroy_iterator(itr);

    return res_list;
}

// 不要释放！！！！！不要释放！！！！！
resv_info_t* select_resv_by_student_id(int id) {
    list_t * resv_list = get_list(RESV_INFO_DB);

    list_iterator_t * itr = init_iterator(resv_list);
    int index = 0;
    resv_info_t * resv = NULL;
    while (has_next(itr)) {
        resv = next(itr);
        re_time_t now = get_current_time();
        re_time_t resv_end_time = add_hours(&resv->resv_time, 1);
        if (id == resv->stu_id && compare_time(&resv_end_time, &now) >= 0) {
            break;
        }
        index++;
    }
    destroy_iterator(itr);

    return get_item(resv_list, index);
}

// 不要释放！！！！！不要释放！！！！！
resv_info_t* select_resv_by_student_phone(long long phone) {
    list_t * resv_list = get_list(RESV_INFO_DB);

    list_iterator_t * itr = init_iterator(resv_list);
    int index = 0;
    resv_info_t * resv = NULL;
    while (has_next(itr)) {
        resv = next(itr);
        resv->resv_time.hour += resv->resv_hours;
        re_time_t now = get_current_time();
        if (phone == resv->stu_phone && compare_time(&resv->resv_time, &now)) {
            break;
        }
        index++;
    }
    destroy_iterator(itr);

    return resv;
}
