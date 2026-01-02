# Google Test is available in thirdparty/googletest
# So we don't need to find it separately

add_executable(test
    test.cpp
    test_unit.cpp
    test_integration.cpp
)

# Link against Google Test libraries from thirdparty and other required libraries
target_link_libraries(test
    gtest
    gtest_main
    gmock
    gmock_main
    shop  # 链接到shop库
    Qt5::Core
    Qt5::Widgets
)
