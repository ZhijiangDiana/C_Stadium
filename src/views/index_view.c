//
// Created by 14838 on 25-7-3.
//

#include "index_view.h"

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

char frame0[10][128] = {
    " ",
    "  欢迎使用工地通 - 羽毛球场预约系统",
    " ",
    " ",
    "             系统正在初始化.",
    " ",
    " ",
    "\\o/\\o/\\o/\\o/\\o/\\o/\\o/\\o/\\o/",
    " |  |  |  |  |  |  |  |  |",
    "/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\",
};

char frame1[10][128] = {
    " ",
    "  欢迎使用工地通 - 羽毛球场预约系统",
    " ",
    " ",
    "             系统正在初始化...",
    " ",
    "\\o/\\o/\\o/\\o/\\o/\\o/\\o/\\o/\\o/",
    " |  |  |  |  |  |  |  |  |",
    "/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\",
    " "
};


void index() {
    int cnt = 0;
    while (cnt < 10) {
        system("cls");
        if (cnt % 2 == 0)
            for (int i = 0; i < 10; ++i)
                printf("%s\n", frame0[i]);
        else
            for (int i = 0; i < 10; ++i)
                printf("%s\n", frame1[i]);
        cnt++;
        _sleep(500);
    }
    password_menu();
}

void password_menu() {
    char password[128];

    do {
        system("cls");
        printf("====================\n");
        printf("请输入密码：");

        int idx = 0;
        char ch;
        while ((ch = _getch()) != '\r') { // \r 是回车键（Enter）
            if (ch == '\b') {  // 处理退格键
                if (idx > 0) {
                    idx--;
                    printf("\b \b");  // 删除一个字符
                }
            } else if (idx < 127 && ch >= 32 && ch <= 126) {
                password[idx++] = ch;
                printf("*");
            }
        }
        password[idx] = '\0';  // 字符串结束

        if (strcmp(password, "1145141919810") == 0)
            break;

        printf("\n密码错误！\n");
        system("pause");
    } while (1);
}
