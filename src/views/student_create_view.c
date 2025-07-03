//
// Created by 14838 on 25-7-1.
//

#include "student_create_view.h"

#include "student.h"
#include "student_service.h"


void student_create_menu() {
    system("cls");
    printf("==========录入学生信息==========\n");

    student_t student;

    // 输入学号
    printf("请输入学号：");
    scanf_s("%d", &student.id);

    // 输入学号
    printf("请输入姓名：");
    scanf_s("%s", &student.name);

    // 输入手机号
    printf("请输入手机号：");
    scanf_s("%lld", &student.phone);

    student.gender = NOT_SET;

    response_result_t resp = add_new_student(student);
    if (resp.code == SUCCESS)
        printf("录入学生信息成功！\n");
    else
        printf("发生错误：%s\n", resp.error_msg);

    system("pause");
}
