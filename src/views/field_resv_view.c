//
// Created by 14838 on 25-7-1.
//

#include "field_resv_view.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "dllist_iterator.h"
#include "field_service.h"
#include "response_result.h"
#include "student_service.h"
#include "field_service.h"
#include "resv_service.h"


void field_menu(bool need_resv) {
    response_result_t resp = list_all_field();

    if (resp.code == SUCCESS) {
        system("cls");
        printf("==========请选择您需要查询的场地==========\n");

        list_iterator_t * itr = init_iterator(resp.data);
        while (has_next(itr)) {
            field_t * field = next(itr);
            printf("%d. %s  可预约时段：%02d:%02d - %02d:%02d  场馆数：%d\n", field->id, field->name,
                field->open_from.hour, field->open_from.minute,
                field->open_to.hour, field->open_to.minute,
                field->total_resv_cnt);
        }
        destroy_iterator(itr);

        int chosen_f_id;
        // 需要进入预约界面
        printf("请选择您需要预约的场地id：");
        scanf_s("%d", &chosen_f_id);

        // 查询是否有该项
        itr = init_iterator(resp.data);
        bool has_id = false;
        while (has_next(itr)) {
            field_t * field = next(itr);
            if (field->id == chosen_f_id) {
                has_id = true;
                break;
            }
        }
        destroy_iterator(itr);
        if (!has_id) {
            printf("输入id有误，请重新输入！\n");
            system("pause");
            return;
        }

        // 选择该field
        resv_field_menu(chosen_f_id, need_resv);
    } else {
        printf("发生错误：%s\n", resp.error_msg);
    }
}

void resv_field_menu(int field_id, bool need_resv) {
    re_time_t now = get_hour_start_time();
    field_resv_info_dto_t dto = {field_id, now};
    response_result_t resp = list_field_three_days_resv(dto);

    list_t **vo_lists = resp.data;
    if (resp.code == SUCCESS) {
        int choice = 0;
        while (true) {
            // 处理choice溢出
            choice = (choice + 3) % 3;

            system("cls");
            printf("==========%d号场馆 %d-%d-%d 预约信息==========\n", field_id, now.year, now.month, now.day + choice);

            list_t * chosen_list = vo_lists[choice];
            list_iterator_t * itr = init_iterator(chosen_list);
            int index = 1;
            while (has_next(itr)) {
                field_resv_vo_t * vo = next(itr);
                printf("%2d. %02d:%02d - %02d:%02d  可约%d/总共%d\n", index,
                    vo->unit_from.hour, vo->unit_from.minute,
                    vo->unit_to.hour, vo->unit_to.minute,
                    vo->empty_cnt, vo->total_cnt);
                index++;
            }
            destroy_iterator(itr);

            // 选择选项
            if (need_resv)
                printf("键盘←→可切换预约天数，回车键进入下一步\n");
            else
                printf("键盘←→可切换预约天数，回车键退出\n");
            int ch = _getch();

            // 处理按键
            if (ch == 13) {  // 回车
                // 确定
                break;
            }
            if (ch == 224) {
                int arrow = _getch();  // 第二个键值
                if (arrow == 75) {     // ← 左箭头
                    choice--;
                } else if (arrow == 77) {  // → 右箭头
                    choice++;
                }
            }
        }

        if (need_resv) {
            // 需要预约
            int chosen_index;
            printf("请输入需要预约的场次：");
            scanf_s("%d", &chosen_index);

            // 获取vo
            list_t * chosen_list = vo_lists[choice];
            field_resv_vo_t * vo = get_item(chosen_list, chosen_index - 1);
            if (vo == NULL) {
                printf("场次输入错误！\n");
                system("pause");
                return;
            }

            int hours;    // 预约时长
            printf("请输入预约时长：");
            scanf_s("%d", &hours);
            if (hours > MAX_RESV_HOURS) {
                printf("预约时长太长，请重新输入！\n");
                system("pause");
                return;
            }

            student_find_menu(vo, hours);
        }
    } else {
        printf("发生错误：%s\n", resp.error_msg);
    }
}

void student_find_menu(field_resv_vo_t * vo, int hours) {
    system("cls");
    printf("==========学生查询==========\n");
    printf("请输入学生id：");
    int id;
    scanf_s("%d", &id);

    response_result_t resp = get_student_by_id(id);
    if (resp.code == SUCCESS) {
        student_t * stu = resp.data;
        // 未查到学生
        if (stu == NULL) {
            printf("学生id不存在，请重新输入！\n");
            system("pause");
            return;
        }

        // 预约已满
        if (vo->empty_cnt == 0) {
            printf("该场预约人数已满！\n");
            system("pause");
            return;
        }

        check_menu(stu, vo, hours);
    } else {
        printf("发生错误：%s\n", resp.error_msg);
    }
}

void check_menu(student_t * stu, field_resv_vo_t * vo, int hours) {
    response_result_t field_resp = get_field_by_id(vo->field_id);
    if (field_resp.code == SUCCESS) {
        field_t * field = field_resp.data;

        system("cls");
        printf("请核对身份信息及预约信息是否正确：\n");
        printf("学生id：%d\n", stu->id);
        printf("姓名：%s\n", stu->name);
        printf("性别：");
        switch (stu->gender) {
        case MALE:
            printf("男\n");
            break;
        case FEMALE:
            printf("女\n");
            break;
        case NOT_SET:
            printf("未设置\n");
        }
        printf("手机号：%lld\n", stu->phone);

        printf("预约场次：%s  %02d:%02d-%02d:%02d ", field->name,
            vo->unit_from.hour, vo->unit_from.minute,
            vo->unit_from.hour + hours, vo->unit_to.minute);


        printf("继续（y）返回（n）：");
        char choice;
        scanf_s(" %c", &choice);    // %c前面有空格可以跳过空白字符
        if (choice == 'y') {
            // 确认预约
            resv_info_t resv = {stu->id, stu->phone, vo->field_id, vo->unit_from, hours};
            response_result_t resp = add_resv(resv);
            if (resp.code == SUCCESS) {
                printf("预约成功！\n");
            } else {
                printf("发生错误：%s\n", resp.error_msg);
            }
            system("pause");
        }
    }
}
