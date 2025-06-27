//
// Created by 14838 on 25-6-28.
//

#ifndef FIELD_DAO_H
#define FIELD_DAO_H

#include "field.h"
#include "dllist.h"
#include "dllist_iterator.h"
#include "init_storage.h"

void insert_field(field_t * field);
void delete_by_field_id(int id);
void update_by_field_id(field_t * field);
list_t * select_all_field();
field_t * select_by_field_id(int id);


#endif //FIELD_DAO_H
