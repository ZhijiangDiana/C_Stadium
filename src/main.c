#include <stdio.h>

#include "dllist_test.h"
#include "time_remake_test.h"

#include <windows.h>

void set_console_utf8() {
    SetConsoleOutputCP(CP_UTF8);  // 设置输出为 UTF-8 编码
    SetConsoleCP(CP_UTF8);        // 设置输入为 UTF-8 编码
}

void module_test() {
    // dllist_iterator_test();
    time_remake_test();
}

int main(void) {
    set_console_utf8();

    module_test();
}