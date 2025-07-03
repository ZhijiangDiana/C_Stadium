#ifndef MD5_H
#define MD5_H
#include <stddef.h>
#include <stdint.h>

#define MD5_DIGEST_LENGTH 16

// MD5 加密函数：输入字符串，输出 16 进制格式的 MD5
void md5_encrypt(const char *input_string, char *output_md5);
#endif // MD5_H
