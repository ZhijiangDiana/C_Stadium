#include "md5_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
// 初始化MD5状态值
static uint32_t state[4];
// MD5常量
static const uint32_t k[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0x8b44f7af,
    0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xabcdefee, 0x999ddcc5, 0xaac4cbd3, 0x0b43fb99
};
// 32位常数
static const uint32_t shift_sizes[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 20, 6, 10, 15, 20, 6, 10, 15, 20, 6, 10, 15, 20
};
void md5_init() {
    state[0] = 0x67452301;
    state[1] = 0xefcdab89;
    state[2] = 0x98badcfe;
    state[3] = 0x10325476;
}
void md5_transform(uint32_t *state, const uint8_t *block) {
    uint32_t a = state[0];
    uint32_t b = state[1];
    uint32_t c = state[2];
    uint32_t d = state[3];
    uint32_t x[16];
    for (int i = 0; i < 16; ++i) {
        x[i] = ((uint32_t)block[i * 4]) |
               ((uint32_t)block[i * 4 + 1] << 8) |
               ((uint32_t)block[i * 4 + 2] << 16) |
               ((uint32_t)block[i * 4 + 3] << 24);
    }
    for (int i = 0; i < 64; ++i) {
        uint32_t f, g;
        if (i < 16) {
            f = (b & c) | (~b & d);
            g = i;
        } else if (i < 32) {
            f = (d & b) | (~d & c);
            g = (5 * i + 1) % 16;
        } else if (i < 48) {
            f = b ^ c ^ d;
            g = (3 * i + 5) % 16;
        } else {
            f = c ^ (b | ~d);
            g = (7 * i) % 16;
        }
        uint32_t temp = d;
        d = c;
        c = b;
        b = b + ((a + f + k[i] + x[g]) << shift_sizes[i] | (a + f + k[i] + x[g]) >> (32 - shift_sizes[i]));
        a = temp;
    }
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}
void md5_update(uint8_t *input, size_t length) {
    size_t index = 0;
    size_t pad_length = length + 1 + 8 + (64 - (length + 1 + 8) % 64);
    uint8_t *padded_input = malloc(pad_length);
    if (!padded_input) {
        return;
    }
    memcpy(padded_input, input, length);
    padded_input[length] = 0x80;
    for (size_t i = 0; i < 8; ++i) {
        padded_input[pad_length - 8 + i] = (length * 8) >> (i * 8);
    }
    for (size_t i = 0; i < pad_length / 64; ++i) {
        md5_transform(state, &padded_input[i * 64]);
    }
    free(padded_input);
}
void md5_final(uint8_t *digest) {
    for (int i = 0; i < 4; ++i) {
        digest[i * 4] = (state[i] >> 0) & 0xFF;
        digest[i * 4 + 1] = (state[i] >> 8) & 0xFF;
        digest[i * 4 + 2] = (state[i] >> 16) & 0xFF;
        digest[i * 4 + 3] = (state[i] >> 24) & 0xFF;
    }
}
void md5_encrypt(const char *input_string, char *output_md5) {
    uint8_t digest[MD5_DIGEST_LENGTH];
    md5_init();
    md5_update((uint8_t *)input_string, strlen(input_string));
    md5_final(digest);
    // 转为十六进制字符串
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(&output_md5[i * 2], "%02x", digest[i]);
    }
}



