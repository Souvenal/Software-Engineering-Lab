cmake_minimum_required(VERSION 3.10)
project(ShoppingApp)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)

set(target_name ShoppingApp)

# 设置目标输出目录
set(TARGET_DIR ${PROJECT_SOURCE_DIR}/target)

# 设置可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR})

# 设置库文件输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TARGET_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TARGET_DIR}/lib)

find_program(CLANG_TIDY_EXE "clang-tidy")

if (CLANG_TIDY_EXE)
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
else()
    message(WARNING "clang-tidy not found")
endif()

# 设置Qt5标准项目配置
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 查找Qt5核心和窗口部件模块
find_package(PkgConfig REQUIRED)
pkg_check_modules(QT5 REQUIRED IMPORTED_TARGET Qt5Core Qt5Widgets)
set(CMAKE_PREFIX_PATH $ENV{Qt5_DIR})
find_package(Qt5 REQUIRED COMPONENTS Core Widgets) # I don't know why using pkg-config solely doesn't work for automoc etc

# 添加子目录
add_subdirectory(thirdparty)

add_subdirectory(src)

add_subdirectory(test)
