//
// Created by 14838 on 25-6-30.
//

#ifndef RESPONSE_RESULT_H
#define RESPONSE_RESULT_H
#include <stddef.h>
#include <string.h>

typedef enum _err_code_t {
    SUCCESS = 0,
    INPUT_ERROR = 1,
    INTERNAL_ERROR = 2,
} err_code_t;

#define REQUEST_SUCCESS        "请求成功"
#define INVALID_PARAM          "无效参数"
#define STU_ID_EXISTS          "学生id已注册"
#define STU_PHONE_EXISTS       "学生手机号已注册"
#define STU_NAME_TOO_LONG      "学生姓名太长"
#define RESV_TIME_TOO_LONG     "预约时间太长"
#define RESV_TIME_ILLEGAL      "预约时间不合法"

// 使用完data后需要释放
typedef struct _response_result_t {
    err_code_t code;
    char error_msg[64];
    void * data;
} response_result_t;

static inline response_result_t request_success(void * data) {
    response_result_t res = {SUCCESS, REQUEST_SUCCESS, data};
    return res;
}

static inline response_result_t request_error(err_code_t code, char const * msg) {
    response_result_t res = {code, "", NULL};
    strcpy(res.error_msg, msg);
    return res;
}

#endif //RESPONSE_RESULT_H
