//
// Created by 14838 on 25-6-30.
//

#ifndef RESV_SERVICE_H
#define RESV_SERVICE_H

#include "resv_dao.h"
#include "response_result.h"
#include "resv_dto.h"

response_result_t get_student_resv_info(resv_dto_t dto);
response_result_t add_resv(resv_info_t info);
response_result_t cancel_resv(resv_dto_t dto);

#endif //RESV_SERVICE_H
