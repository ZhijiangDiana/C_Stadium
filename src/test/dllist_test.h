//
// Created by 14838 on 25-6-26.
//

#ifndef DLLIST_TEST_H
#define DLLIST_TEST_H

#include "dllist.h"
#include "dllist_iterator.h"

inline void dllist_iterator_test() {
    list_t * list = init_list();

    int a = 114;
    int b = 514;
    int c = 1919;
    int d = 810;
    push_back(list, &a);
    push_back(list, &b);
    push_front(list, &c);
    push_front(list, &d);

    int * p1 = get_item(list, 0);
    int * p2 = get_item(list, 1);
    int * p3 = get_item(list, 2);
    int * p4 = get_item(list, 3);

    printf("%d %d %d %d\n", *p1, *p2, *p3, *p4);

    list_iterator_t * iterator = init_iterator(list);
    while (has_next(iterator)) {
        printf("%d ", *(int *) next(iterator));
    }

    print_list(list);

    destroy_list(list);
    destroy_iterator(iterator);
}

#endif //DLLIST_TEST_H
