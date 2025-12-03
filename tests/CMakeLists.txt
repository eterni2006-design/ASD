create_executable_project(AllTests)

target_sources(AllTests PRIVATE
    test_easy_example.cpp
    stack_gtest.cpp
)

target_link_libraries(AllTests gtest gtest_main)
add_test(NAME AllTests COMMAND AllTests)

target_link_libraries(AllTests stack_lib gtest_main)