#include <stdio.h>

#include <windows.h>
#include "init_storage.h"
#include "main_view.h"

void set_console_utf8() {
    SetConsoleOutputCP(CP_UTF8);  // 设置输出为 UTF-8 编码
    SetConsoleCP(CP_UTF8);        // 设置输入为 UTF-8 编码
}

void module_test() {
    // dllist_iterator_test();
    // time_remake_test();
    // field_dao_test();
    // test_student_dao();
    // test_resv_dao();
    // field_dao_test();
    // // 测试用例
    // test_md5("hello world", "b94d27b9934d3e08a52e52d7da7dabfa");
    // test_md5("md5", "1bc29b36f623ba82aaf6724fd3b16718");
    // test_md5("123456", "e10adc3949ba59abbe56e057f20f883e");
    // test_md5("OpenAI", "e6d3d3bc6cfdd7f03d846db5c1305e92");
    //
    // // 其他可以用来验证的自定义测试用例
    // test_md5("1234", "81dc9bdb52d04dc20036dbd8313ed055");
    // test_md5("abc123", "e99a18c428cb38d5f260853678922e03");
}

int main(void) {
    set_console_utf8();
    init_storage();
    enter_menu();

    module_test();
}