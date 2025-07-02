//
// Created by 14838 on 25-7-1.
//
#include "student.h"


char * student_t_serializer(student_t* student) {
    char * buffer = malloc(sizeof(student_t) * 2);

    sprintf(buffer, "%d %s %d %lld", student->id, student->name, student->gender, student->phone);

    // // 序列化 password
    // strcat(buffer, student->password);
    // strcat(buffer, " ");
    //
    // // 序列化 salt
    // strcat(buffer, student->salt);

    return buffer;
}

student_t * student_t_deserializer(char* input) {
    char *token;
    student_t * result = malloc(sizeof(student_t));

    // 解析 id
    token = strtok(input, " ");
    result->id = atoi(token);

    // 解析 name
    token = strtok(NULL, " ");
    strncpy(result->name, token, sizeof(result->name) - 1);
    result->name[sizeof(result->name) - 1] = '\0';  // 确保 null 终止

    // 解析 gender
    token = strtok(NULL, " ");
    result->gender = (gender_t)atoi(token);

    // 解析 phone
    token = strtok(NULL, " ");
    result->phone = atoll(token);

    // // 解析 password
    // token = strtok(NULL, " ");
    // strncpy(result->password, token, sizeof(result->password) - 1);
    // result->password[sizeof(result->password) - 1] = '\0';
    //
    // // 解析 salt
    // token = strtok(NULL, " ");
    // strncpy(result->salt, token, sizeof(result->salt) - 1);
    // result->salt[sizeof(result->salt) - 1] = '\0';

    return result;
}
