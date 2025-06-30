//
// Created by 14838 on 25-6-28.
//

#include "student_dao.h"
#include <stddef.h>
#include "dllist_iterator.h"
#include "init_storage.h"


// 插入的实体不能位于栈区
void insert_student(student_t* student) {
    list_t * student_list = get_list(STUDENT_DB);

    push_back(student_list, student);
}

// 不要释放！！！！！不要释放！！！！！
list_t* select_all_student() {
    return get_list(STUDENT_DB);
}

// 不要释放！！！！！不要释放！！！！！
student_t* select_by_student_id(int id) {
    list_t * student_list = get_list(STUDENT_DB);

    list_iterator_t * itr = init_iterator(student_list);
    int index = 0;
    while (has_next(itr)) {
        if (id == ((student_t *) next(itr))->id)
            break;
        index++;
    }
    destroy_iterator(itr);

    return get_item(student_list, index);
}

// 不要释放！！！！！不要释放！！！！！
student_t* select_by_student_phone(long phone) {
    list_t * student_list = get_list(STUDENT_DB);

    list_iterator_t * itr = init_iterator(student_list);
    int index = 0;
    while (has_next(itr)) {
        if (phone == ((student_t *) next(itr))->phone)
            break;
        index++;
    }
    destroy_iterator(itr);

    return get_item(student_list, index);
}
