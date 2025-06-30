//
// Created by 14838 on 25-6-30.
//

#ifndef RESV_DAO_TEST_H
#define RESV_DAO_TEST_H

#include "resv_dao.h"
#include <stdio.h>

// 用于打印预约信息
static inline void print_resv(const resv_info_t *resv) {
    char time_str[64];
    format_time(&resv->resv_time, time_str, sizeof(time_str));
    printf("学生ID: %d, 手机号: %lld, 场地ID: %d, 时间: %s, 时长: %d小时\n",
           resv->stu_id,
           resv->stu_phone,
           resv->field_id,
           time_str,
           resv->resv_hours);
}

static inline void test_resv_dao() {
    printf("=== 插入预约记录 ===\n");
    re_time_t now = get_current_time();

    resv_info_t r1 = {
        .stu_id = 1001,
        .stu_phone = 1234567890LL,
        .field_id = 1,
        .resv_time = now,
        .resv_hours = 2
    };
    insert_resv(&r1);

    resv_info_t r2 = {
        .stu_id = 1002,
        .stu_phone = 9876543210LL,
        .field_id = 2,
        .resv_time = add_hours(&now, 2),
        .resv_hours = 1
    };
    insert_resv(&r2);

    printf("\n=== 查询所有预约记录 ===\n");
    list_t *all = select_all_resv();
    if (all) {
        list_iterator_t * itr = init_iterator(all);
        while (has_next(itr)) {
            print_resv(next(itr));
        }
        destroy_iterator(itr);
    }

    printf("\n=== 按学生ID查询预约 (ID=1001) ===\n");
    resv_info_t *by_id = select_resv_by_student_id(1001);
    if (by_id) {
        print_resv(by_id);
    } else {
        printf("未找到 ID 为 1001 的预约\n");
    }

    printf("\n=== 按学生手机号查询预约 (phone=9876543210) ===\n");
    resv_info_t *by_phone = select_resv_by_student_phone(9876543210LL);
    if (by_phone) {
        print_resv(by_phone);
    } else {
        printf("未找到手机号为 9876543210 的预约\n");
    }

    printf("\n=== 删除学生ID为1001的预约记录 ===\n");
    delete_resv_by_student_id(1001);

    printf("\n=== 再次查询所有预约记录 ===\n");
    all = select_all_resv();
    if (all) {
        list_iterator_t * itr = init_iterator(all);
        while (has_next(itr)) {
            print_resv(next(itr));
        }
        destroy_iterator(itr);
    }

    printf("\n=== 查询已删除的学生ID=1001的预约记录 ===\n");
    resv_info_t *deleted = select_resv_by_student_id(1001);
    if (!deleted) {
        printf("预约记录已删除，未找到。\n");
    }
}

#endif //RESV_DAO_TEST_H
