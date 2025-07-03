//
// Created by 14838 on 25-7-1.
//

#include "student_create_view.h"

#include "student.h"
#include "student_dao.h"


void student_create_menu() {
    system("cls");
    printf("==========录入学生信息==========\n");

    student_t * student = malloc(sizeof(student_t));

    // 输入学号
    printf("请输入学号：");
    scanf_s("%d", &student->id);

    // 输入学号
    printf("请输入姓名：");
    scanf_s("%s", &student->name);

    // 输入手机号
    printf("请输入手机号：");
    scanf_s("%lld", &student->phone);

    student->gender = NOT_SET;

    insert_student(student);

    printf("录入学生信息成功！\n");
    system("pause");
}
