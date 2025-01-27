set(test_name "TEST_SERIALIZE")

add_executable(
    ${test_name}
    ${torchlight_Collections_files}
    ${torchlight_Object_files}
    ${torchlight_Function_files}
    ${torchlight_ByteCode_files}
    ${torchlight_Runtime_files}
    ${torchlight_dir}/test/unittest/Runtime/Serialize.cpp
)

# gtest
target_link_libraries(${test_name} gtest gtest_main)
add_test(NAME ${test_name} COMMAND ${test_name})
