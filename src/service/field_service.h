//
// Created by 14838 on 25-6-30.
//

#ifndef FIELD_SERVICE_H
#define FIELD_SERVICE_H

#include "field.h"
#include "response_result.h"
#include "resv_dto.h"
#include "field_resv_vo.h"
#include "dllist.h"

response_result_t add_field(field_t field);
response_result_t list_all_field();
response_result_t get_field_by_id(int id);
response_result_t list_field_three_days_resv(field_resv_info_dto_t info);
list_t * list_field_resv(field_t field, re_time_t time);

#endif //FIELD_SERVICE_H
