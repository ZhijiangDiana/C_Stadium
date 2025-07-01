//
// Created by 14838 on 25-6-24.
//
#include "dllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 获取一个结点并初始化
static node_t * get_node(void * data) {
    node_t * node = (node_t *) malloc(sizeof(node_t));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

list_t * init_list() {
    // 分配并初始化链表结构内存
    list_t * list = (list_t *) malloc(sizeof(list_t));
    list->head = get_node(NULL);
    list->length = 0;

    // 初始化头结点内存
    node_t * head = list->head;
    head->next = head;
    head->prev = head;

    return list;
}

// TODO 不销毁data，可能会内存泄漏
void destroy_list(list_t* list, bool is_free_data) {
    if (!list || !list->head)
        return;

    node_t * node = list->head->next;
    while (node != list->head) {
        node_t * temp = node;
        node = node->next;
        if (is_free_data)
            free(temp->data);
        free(temp);
    }
    free(list->head);
    free(list);
}

void push_back(list_t* list, void* data) {
    node_t * new_node = get_node(data);
    node_t * head = list->head;
    node_t * last = head->prev;

    // 修改指针
    last->next = new_node;
    new_node->next = list->head;
    new_node->prev = last;
    head->prev = new_node;

    // 增加length记录
    list->length++;
}

void push_front(list_t* list, void* data) {
    node_t * new_node = get_node(data);
    node_t * head = list->head;
    node_t * first = head->next;

    // 修改指针
    head->next = new_node;
    new_node->next = first;
    first->prev = new_node;
    new_node->prev = head;

    // 增加length记录
    list->length++;
}

void pop_front(list_t* list) {
    // 判断是否为空
    if (list->length == 0)
        return;

    node_t * head = list->head;
    node_t * first = head->next;
    node_t * second = first->next;

    // 修改指针
    head->next = second;
    second->prev = head;
    free(first);

    // 减少length记录
    list->length--;
}

void pop_back(list_t* list) {
    // 判断是否为空
    if (list->length == 0)
        return;

    node_t * head = list->head;
    node_t * last = head->prev;
    node_t * second = last->prev;

    // 修改指针
    head->prev = second;
    second->next = head;
    free(last);

    // 减少length记录
    list->length--;
}

void* front(list_t* list) {
    // 判断是否为空
    if (list->length == 0)
        return NULL;

    return list->head->next->data;
}

void* back(list_t* list) {
    // 判断是否为空
    if (list->length == 0)
        return NULL;

    return list->head->prev->data;
}

void del_item(list_t* list, int index) {
    // 判断index是否合法
    if (index < 0 || index >= list->length)
        return;

    // 爬到需要操作的结点
    node_t * node = list->head->next;
    for (int i = 0; i < index; ++i) {
        node = node->next;
    }

    // 删除结点
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);

    list->length--;
}

void set_item(list_t* list, int index, void* data) {
    // 判断index是否合法
    if (index < 0 || index >= list->length)
        return;

    // 爬到需要操作的结点
    node_t * node = list->head->next;
    for (int i = 0; i < index; ++i) {
        node = node->next;
    }

    // 修改值
    free(node->data);
    node->data = data;
}

void* get_item(list_t* list, int index) {
    // 判断index是否合法
    if (index < 0 || index >= list->length)
        return NULL;

    // 爬到需要操作的结点
    node_t * node = list->head->next;
    for (int i = 0; i < index; ++i) {
        node = node->next;
    }

    return node->data;
}

void print_list(list_t* list) {
    node_t * node = list->head->next;
    while (node != list->head) {
        printf("%d ", *(int *) node->data);
        node = node->next;
    }
}

bool save_to_file(list_t* list, char* filename, char * (*serialize)(void *input)) {
    FILE * file = fopen(filename, "w");
    if (!file)
        return false;

    node_t * node = list->head->next;
    while (node != list->head) {
        char * buffer = serialize(node->data);

        fwrite(buffer, sizeof(char), strlen(buffer), file);  // 写入文件
        fwrite("\n", sizeof(char), 1, file);  // 分隔符
        node = node->next;
    }

    fclose(file);

    return true;
}

bool load_from_file(list_t* list, char* filename, void * (*deserialize)(char *input)) {
    list = init_list();

    FILE * file = fopen(filename, "r");
    if (!file) {
        file = fopen(filename, "w");
        fclose(file);
        file = fopen(filename, "r");
    }

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        void *data = deserialize(buffer);

        node_t *new_node = malloc(sizeof(node_t));
        new_node->data = data;
        new_node->next = list->head;
        list->head = new_node;
    }

    fclose(file);

    return true;
}
