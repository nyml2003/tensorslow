set(test_name "TEST_DECIMAL")

add_executable(
    ${test_name}
    ${torchlight_Collections_files}
    ${torchlight_dir}/test/unittest/Collections/Decimal.cpp
)

# gtest
target_link_libraries(${test_name} gtest gtest_main)
add_test(NAME ${test_name} COMMAND ${test_name})
