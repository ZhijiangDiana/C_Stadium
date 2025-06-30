//
// Created by 14838 on 25-6-30.
//

#include "resv_dao.h"
#include "init_storage.h"
#include "dllist_iterator.h"

// 插入的实体不能位于栈区
void insert_resv(resv_info_t* resv) {
    list_t * resv_list = get_list(RESV_INFO_DB);

    push_back(resv_list, resv);
}

void delete_resv_by_student_id(int id) {
    list_t * student_list = get_list(RESV_INFO_DB);

    list_iterator_t * itr = init_iterator(student_list);
    int index = 0;
    while (has_next(itr)) {
        if (id == ((resv_info_t *) next(itr))->stu_id)
            break;
        index++;
    }
    destroy_iterator(itr);

    del_item(student_list, index);
}

// 不要释放！！！！！不要释放！！！！！
list_t* select_all_resv() {
    return get_list(RESV_INFO_DB);
}

// 不要释放！！！！！不要释放！！！！！
resv_info_t* select_resv_by_student_id(int id) {
    list_t * resv_list = get_list(RESV_INFO_DB);

    list_iterator_t * itr = init_iterator(resv_list);
    int index = 0;
    while (has_next(itr)) {
        if (id == ((resv_info_t *) next(itr))->stu_id)
            break;
        index++;
    }
    destroy_iterator(itr);

    return get_item(resv_list, index);
}

// 不要释放！！！！！不要释放！！！！！
resv_info_t* select_resv_by_student_phone(long long phone) {
    list_t * resv_list = get_list(RESV_INFO_DB);

    list_iterator_t * itr = init_iterator(resv_list);
    int index = 0;
    while (has_next(itr)) {
        if (phone == ((resv_info_t *) next(itr))->stu_phone)
            break;
        index++;
    }
    destroy_iterator(itr);

    return get_item(resv_list, index);
}
