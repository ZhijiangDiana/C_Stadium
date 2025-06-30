//
// Created by 14838 on 25-6-28.
//

#ifndef FIELD_DAO_TEST_H
#define FIELD_DAO_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "field_dao.h"

static void print_all_item(void) {
    list_t * field_list = select_all_field();
    list_iterator_t * itr = init_iterator(field_list);
    while (has_next(itr)) {
        field_t * field = next(itr);
        printf("%d %s\n", field->id, field->name);
    }
    destroy_iterator(itr);
}

static inline void field_dao_test() {
    printf("==========Test 1==========\n");

    field_t * field1 = malloc(sizeof(field_t));
    strcpy(field1->name, "野兽羽毛球场1");
    field_t * field2 = malloc(sizeof(field_t));
    strcpy(field2->name, "野兽羽毛球场2");
    field_t * field3 = malloc(sizeof(field_t));
    strcpy(field3->name, "野兽羽毛球场3");
    field_t * field4 = malloc(sizeof(field_t));
    strcpy(field4->name, "野兽羽毛球场4");
    field_t * field5 = malloc(sizeof(field_t));
    strcpy(field5->name, "野兽羽毛球场5");
    insert_field(field1);
    insert_field(field2);
    insert_field(field3);
    insert_field(field4);
    insert_field(field5);
    print_all_item();

    printf("==========Test 2==========\n");

    delete_field_by_field_id(10002);
    print_all_item();

    printf("==========Test 3==========\n");

    field_t * field = malloc(sizeof(field_t));
    field->id = 10000;
    strcpy(field->name, "仙贝羽毛球场114514");
    update_field_by_field_id(field);
    print_all_item();

    printf("==========Test 4==========\n");

    field = select_field_by_field_id(10000);
    printf("%d %s\n", field->id, field->name);
    field = select_field_by_field_id(10003);
    printf("%d %s\n", field->id, field->name);
    field = select_field_by_field_id(10009);
    if (field == NULL)
        printf("114514114514");


}

#endif //FIELD_DAO_TEST_H
