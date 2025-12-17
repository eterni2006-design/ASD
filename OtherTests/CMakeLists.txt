create_executable_project(OtherTests)

target_sources(OtherTests PRIVATE
    st_q_onlist_gtest.cpp
)


target_link_libraries(OtherTests
    st_q_onlist
    gtest
    gtest_main
)

add_test(NAME OtherTests COMMAND OtherTests)