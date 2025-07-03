//
// Created by 14838 on 25-7-1.
//

#include "main_view.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dllist_iterator.h"
#include "field_create_view.h"
#include "field_resv_view.h"
#include "field_service.h"
#include "init_storage.h"
#include "student_create_view.h"
#include "student_resv_view.h"


void enter_menu() {
    while (true) {
        int choice;
        system("cls");

        printf("==========欢迎使用工地通-羽毛球场预约系统==========\n");
        printf("1. 预约场地\n");
        printf("2. 查询场地预约情况\n");
        printf("3. 查看和取消预约\n");
        printf("4. 录入学生信息\n");
        printf("请选择：");

        scanf_s("%d", &choice);
        switch (choice) {
            case 1:
                // 进入预约场地界面
                field_menu(true);
                break;
            case 2:
                // 进入查询场地预约情况界面
                field_menu(false);
                break;
            case 3:
                // 进入取消预约界面
                cancel_resv_view();
                break;
            case 4:
                // 进入录入学生信息界面
                student_create_menu();
                break;
            case 114514:
                admin_menu();
                break;
            default:
                printf("输入错误，请重新输入！\n");
                system("pause");
                break;
        }
    }

}

void admin_menu() {
    while (true) {
        int choice;
        system("cls");

        printf("==========欢迎使用工地通-羽毛球场预约系统==========\n");
        printf("1. 录入场地信息\n");
        printf("2. 回到用户界面\n");
        printf("3. 退出程序\n");
        printf("请选择：");
        scanf_s("%d", &choice);
        switch (choice) {
        case 1:
            // 进入录入场地信息界面
            field_create_menu();
            break;
        case 2:
            // 返回用户界面
            return;
        case 3:
            printf("感谢使用！\n");
            store(ALL_DB);
            system("pause");
            exit(0);
            break;
        default:
            printf("输入错误，请重新输入！\n");
            system("pause");
            break;
        }
    }
}
