//
// Created by hp on 25-6-30.
//

#ifndef MD5_TEST_H
#define MD5_TEST_H

#include "stdio.h"
#include "md5_utils.h"
#include "string.h"

static inline void test_md5(const char *input, const char *expected_md5) {
    char output_md5[MD5_DIGEST_LENGTH * 2 + 1];  // MD5结果的长度是32字符，16字节
    md5_encrypt(input, output_md5);

    if (strcmp(output_md5, expected_md5) == 0) {
        printf("测试通过: 输入: \"%s\"\n", input);
        printf("预期 MD5: %s\n", expected_md5);
        printf("实际 MD5: %s\n\n", output_md5);
    } else {
        printf("测试失败: 输入: \"%s\"\n", input);
        printf("预期 MD5: %s\n", expected_md5);
        printf("实际 MD5: %s\n\n", output_md5);
    }
}

#endif //MD5_TEST_H
