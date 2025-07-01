//
// Created by 14838 on 25-6-24.
//

#ifndef DLLIST_H
#define DLLIST_H

#include <stdbool.h>

typedef struct _node_t {
    void * data;
    struct _node_t * next;
    struct _node_t * prev;
} node_t;

typedef struct _list_t {
    node_t * head;
    int length;
} list_t;

list_t * init_list();
void destroy_list(list_t * list, bool is_free_data);

void push_back(list_t * list, void * data);
void push_front(list_t * list, void * data);

void pop_front(list_t * list);
void pop_back(list_t * list);

void * front(list_t * list);
void * back(list_t * list);

void del_item(list_t * list, int index);
void set_item(list_t * list, int index, void * data);
void * get_item(list_t * list, int index);

void print_list(list_t * list);  // 仅用于测试，仅限int型

bool save_to_file(list_t * list, char * filename, char * (*serialize)(void *input));
bool load_from_file(list_t ** list, char * filename, void * (*deserialize)(char *input));


#endif //DLLIST_H
