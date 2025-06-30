//
// Created by 14838 on 25-6-30.
//

#ifndef STUDENT_DAO_TEST_H
#define STUDENT_DAO_TEST_H

#include "student.h"
#include "stdio.h"
#include "string.h"
#include "student_dao.h"
#include "dllist_iterator.h"

static inline void print_student(student_t *student) {
    printf("ID: %d, Name: %s, Gender: %d, Phone: %ld, Password: %s\n",
        student->id,
        student->name,
        student->gender,
        student->phone,
        student->password);
}

static inline void test_student_dao() {
    // 插入第一个学生
    student_t s1 = {
        .id = 1001,
        .gender = MALE,
        .phone = 1234567890,
    };
    strcpy(s1.name, "Alice");
    strcpy(s1.password, "alice123");
    strcpy(s1.salt, "s@1t1");
    insert_student(&s1);

    // 插入第二个学生
    student_t s2 = {
        .id = 1002,
        .gender = FEMALE,
        .phone = 9876543210,
    };
    strcpy(s2.name, "Bob");
    strcpy(s2.password, "bob123");
    strcpy(s2.salt, "s@1t2");
    insert_student(&s2);

    printf("\n== 查询所有学生 ==\n");
    list_t *all = select_all_student();
    // 假设你实现了 list_foreach 或者手动遍历
    if (all) {
        // 遍历打印
        list_iterator_t * itr = init_iterator(all);
        while (has_next(itr)) {
            print_student(next(itr));
        }
        destroy_iterator(itr);
    }

    printf("\n== 按ID查询学生 ==\n");
    student_t *found_id = select_student_by_student_id(1002);
    if (found_id) {
        print_student(found_id);
    } else {
        printf("未找到 ID 为 1002 的学生\n");
    }

    printf("\n== 按手机号查询学生 ==\n");
    student_t *found_phone = select_student_by_student_phone(1234567890);
    if (found_phone) {
        print_student(found_phone);
    } else {
        printf("未找到手机号为 1234567890 的学生\n");
    }

    found_phone = select_student_by_student_phone(1145141919810);
    if (found_phone) {
        print_student(found_phone);
    } else {
        printf("未找到手机号为 1145141919810 的学生\n");
    }
}


#endif //STUDENT_DAO_TEST_H
