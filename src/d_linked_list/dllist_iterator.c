//
// Created by 14838 on 25-6-26.
//

#include "dllist_iterator.h"
#include <stdlib.h>

// 初始化迭代器，指向链表头
list_iterator_t * init_iterator(list_t * list) {
    if (!list || list->length == 0)
        return NULL;

    list_iterator_t * it = malloc(sizeof(list_iterator_t));
    if (!it) return NULL;
    it->current = list->head->next;
    it->head = list->head;
    it->started = 0;
    return it;
}

// 是否还有下一个（循环链表版本）
bool has_next(list_iterator_t * it) {
    return it && it->current != it->head;
}

// 获取当前数据并前进
void * next(list_iterator_t * it) {
    if (!has_next(it))
        return NULL;

    void * data = it->current->data;
    it->current = it->current->next;
    it->started = 1;
    return data;
}

// 是否还有前一个（循环）
bool has_prev(list_iterator_t * it) {
    return it && it->current && (!it->started || it->current != it->head);
}

// 获取当前前一个节点数据并移动
void * prev(list_iterator_t * it) {
    if (!has_prev(it))
        return NULL;

    it->current = it->current->prev;
    it->started = 1;
    return it->current->data;
}

// 销毁
void destroy_iterator(list_iterator_t * it) {
    if (it)
        free(it);
}
