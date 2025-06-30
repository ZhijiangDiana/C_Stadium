cmake_minimum_required(VERSION 3.16)
project(c_stadium LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

# Qt 5 安装路径
#set(CMAKE_PREFIX_PATH "C:/Qt/5.14.2/mingw73_64")
# 或者使用下面这句（推荐）：
# set(Qt5_DIR "C:/Qt/Qt5.14.2/5.14.2/mingw73_64/lib/cmake/Qt5")

#find_package(Qt5 REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE SOURCE_LIST "src/*.c" "src/*.cpp" "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCE_LIST})

include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/d_linked_list
        ${PROJECT_SOURCE_DIR}/src/time_remake_ver
        ${PROJECT_SOURCE_DIR}/src/test
        ${PROJECT_SOURCE_DIR}/src/entity
        ${PROJECT_SOURCE_DIR}/src/entity/dtos
        ${PROJECT_SOURCE_DIR}/src/entity/vos
        ${PROJECT_SOURCE_DIR}/src/dao
        ${PROJECT_SOURCE_DIR}/src/md5
)

# 链接 Qt5 Widgets 模块
#target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
