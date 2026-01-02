# Find Google Test
find_package(GTest REQUIRED)

add_executable(test
    test.cpp
    test_unit.cpp
    test_integration.cpp
)

# Link against Google Test libraries and shop library
if(TARGET GTest::gtest AND TARGET GTest::gtest_main)
    target_link_libraries(test
        GTest::gtest
        GTest::gtest_main
        shop  # 链接到shop库
        Qt5::Core
        Qt5::Widgets
    )
else()
    target_link_libraries(test
        gtest
        gtest_main
        shop  # 链接到shop库
        Qt5::Core
        Qt5::Widgets
    )
endif()