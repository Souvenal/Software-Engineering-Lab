add_executable(${target_name})

# 添加子目录 - shop和ui
add_subdirectory(shop)

# 使用GLOB自动搜索UI目录下的源文件、头文件和表单文件
file(GLOB_RECURSE SOURCES "ui/*.cpp")
file(GLOB_RECURSE HEADERS "ui/*.h")
file(GLOB_RECURSE FORMS "*.ui")

# 如果有特殊命名的源文件需要排除或额外添加，可以在这里处理
# 例如：list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/exclude.cpp")

target_include_directories(${target_name} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${target_name} PkgConfig::QT5)

target_sources(${target_name} PRIVATE
    main.cpp  # 主入口文件
    ${SOURCES} ${HEADERS} ${FORMS}
)

# 链接shop库到主程序
target_link_libraries(${target_name}
    shop
)