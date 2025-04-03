set(test_name "TEST_SERIALIZE")

add_executable(
        ${test_name}
        ${torchlight_common_files}
        ${torchlight_dir}/test/unittest/Runtime/Serialize.cpp
)

# gtest
target_link_libraries(${test_name} gtest gtest_main)
add_test(NAME ${test_name} COMMAND ${test_name})

