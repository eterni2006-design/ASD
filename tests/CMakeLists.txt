create_executable_project(AllTests)

target_sources(AllTests PRIVATE
    test_easy_example.cpp
    stack_gtest.cpp
    queue_gtest.cpp
    list_gtest.cpp
    st_q_onlist_gtest.cpp
)


target_link_libraries(AllTests
    stack_lib
    queue_lib
    list_lib
    st_q_onList
    gtest
    gtest_main
)

add_test(NAME AllTests COMMAND AllTests)