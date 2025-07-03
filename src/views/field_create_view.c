//
// Created by 14838 on 25-7-1.
//

#include "field_create_view.h"

#include <stdlib.h>
#include <sec_api/stdio_s.h>

#include "field.h"
#include "field_dao.h"


void field_create_menu() {
    system("cls");
    printf("==========录入场地信息==========\n");

    field_t * field = malloc(sizeof(field_t));

    // 输入场地名
    printf("请输入场地名：");
    scanf_s("%s", &field->name);

    // 输入场地最大同时可约数（球场数）
    printf("请输入场地最大可约数（球场数）：");
    scanf_s("%d", &field->total_resv_cnt);

    field->open_from = get_current_time();
    field->open_from.hour = 9;
    field->open_from.minute = 0;
    field->open_to = get_current_time();
    field->open_to.hour = 21;
    field->open_to.minute = 0;

    insert_field(field);

    printf("录入场地信息成功！\n");
    system("pause");
}
