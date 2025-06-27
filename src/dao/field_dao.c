//
// Created by 14838 on 25-6-28.
//

#include "field_dao.h"


// 插入的实体不能位于栈区
void insert_field(field_t* field) {
    list_t * field_list = get_list(FIELD_DB);

    field_t * last_field = back(field_list);
    if (last_field == NULL)
        field->id = 10000;
    else
        field->id = last_field->id + 1;

    push_back(field_list, field);
}

void delete_by_field_id(int id) {
    list_t * field_list = get_list(FIELD_DB);

    list_iterator_t * itr = init_iterator(field_list);
    int index = 0;
    while (has_next(itr)) {
        if (id == ((field_t *) next(itr))->id)
            break;
        index++;
    }
    destroy_iterator(itr);

    del_item(field_list, index);
}

void update_by_field_id(field_t* field) {
    list_t * field_list = get_list(FIELD_DB);

    list_iterator_t * itr = init_iterator(field_list);
    int index = 0;
    while (has_next(itr)) {
        if (field->id == ((field_t *) next(itr))->id)
            break;
        index++;
    }
    destroy_iterator(itr);

    set_item(field_list, index, field);
}

// 不要释放！！！！！不要释放！！！！！
list_t* select_all_field() {
    return get_list(FIELD_DB);
}

// 不要释放！！！！！不要释放！！！！！
field_t* select_by_field_id(int id) {
    list_t * field_list = get_list(FIELD_DB);

    list_iterator_t * itr = init_iterator(field_list);
    int index = 0;
    while (has_next(itr)) {
        if (id == ((field_t *) next(itr))->id)
            break;
        index++;
    }
    destroy_iterator(itr);

    return get_item(field_list, index);
}


