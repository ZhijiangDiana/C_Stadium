//
// Created by 14838 on 25-7-1.
//

#include "student_resv_view.h"

#include <stdio.h>
#include <stdlib.h>

#include "field_service.h"
#include "resv_service.h"


void find_student() {
    system("cls");
    printf("==========查看/取消预约==========\n");
    printf("请输入学生id：");
    int stu_id;
    scanf_s("%d", &stu_id);

    resv_dto_t dto = {stu_id, 0, true};
    response_result_t resp = get_student_resv_info(dto);
    if (resp.code == SUCCESS) {
        resv_info_t * resv_info = resp.data;

        // 检查是否有有效预约
        if (resv_info == NULL) {
            printf("当前学生没有任何待完成的预约\n");
            system("pause");
            return;
        }

        // 再次询问是否需要取消
        response_result_t field_resp = get_field_by_id(resv_info->field_id);
        if (field_resp.code == SUCCESS) {
            field_t * field = field_resp.data;

            printf("预约场次：%s  %02d-%02d-%02d %02d:%02d-%02d-%02d", field->name,
                resv_info->resv_time.year, resv_info->resv_time.month, resv_info->resv_time.day,
                resv_info->resv_time.hour, resv_info->resv_time.minute,
                resv_info->resv_time.hour + resv_info->resv_hours, resv_info->resv_time.minute);

            cancel_resv_view();
        }
    }
}

void cancel_resv_view() {
    // cancel_resv();
}