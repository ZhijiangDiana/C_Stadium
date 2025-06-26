//
// Created by 14838 on 25-6-26.
//

#ifndef DLLIST_ITERATOR_H
#define DLLIST_ITERATOR_H

#include "dllist.h"
#include <stdbool.h>

typedef struct _list_iterator_t {
    node_t * current;
    node_t * head;
    int started;
} list_iterator_t;

list_iterator_t * init_iterator(list_t * list);
bool has_next(list_iterator_t * it);
void * next(list_iterator_t * it);
bool has_prev(list_iterator_t * it);
void * prev(list_iterator_t * it);
void destroy_iterator(list_iterator_t * it);


#endif //DLLIST_ITERATOR_H
