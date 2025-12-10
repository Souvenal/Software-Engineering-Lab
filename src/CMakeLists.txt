# 使用GLOB自动搜索源文件、头文件和表单文件
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE FORMS "*.ui")

# 如果有特殊命名的源文件需要排除或额外添加，可以在这里处理
# 例如：list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/exclude.cpp")

target_include_directories(${target_name} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${target_name} PRIVATE
    ${SOURCES} ${HEADERS} ${FORMS}
)