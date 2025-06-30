//
// Created by 14838 on 25-6-26.
//

#ifndef STUDENT_H
#define STUDENT_H

typedef enum _gender_t {
    MALE = 0,
    FEMALE = 1,
    NOT_SET = 2,
} gender_t;

typedef struct _student_t {
    int id;
    char name[50];
    gender_t gender;
    long long phone;  // 十年OI一场空，不开longlong见祖宗
    char password[128];
    char salt[16];
} student_t;


#endif //STUDENT_H
