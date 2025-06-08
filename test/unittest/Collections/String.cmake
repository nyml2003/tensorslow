set(test_name "TEST_STRING")

add_executable(
        ${test_name}
        ${tensorslow_dir}/test/unittest/Collections/String.cpp
)

# gtest
target_link_libraries(${test_name} tensorslow_common gtest gtest_main)
add_test(NAME ${test_name} COMMAND ${test_name})
