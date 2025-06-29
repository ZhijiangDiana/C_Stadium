#ifndef MD5_H
#define MD5_H
#include <stddef.h>
#include <stdint.h>
// MD5 摘要长度
#define MD5_DIGEST_LENGTH 16
// MD5 初始化
void md5_init();
// MD5 更新：对输入数据进行处理
void md5_update(uint8_t *input, size_t length);
// MD5 完成：输出最终的 MD5 摘要
void md5_final(uint8_t *digest);
// MD5 加密函数：输入字符串，输出 16 进制格式的 MD5
void md5_encrypt(const char *input_string, char *output_md5);
#endif // MD5_H
