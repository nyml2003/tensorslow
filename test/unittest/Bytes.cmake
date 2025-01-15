set(test_name "TEST_BYTES")

add_executable(
    ${test_name}
    ${torchlight_dir}/src/collections/Iterator.cpp
    ${torchlight_dir}/src/collections/List.cpp
    ${torchlight_dir}/src/collections/String.cpp
    ${torchlight_dir}/src/collections/Bytes.cpp
    ${torchlight_dir}/src/collections/Integer.cpp
    ${torchlight_dir}/src/collections/Decimal.cpp
    ${torchlight_dir}/test/unittest/Bytes.cpp
)

# gtest
target_link_libraries(${test_name} gtest gtest_main)
add_test(NAME ${test_name} COMMAND ${test_name})
