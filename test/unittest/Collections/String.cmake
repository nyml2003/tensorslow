set(test_name "TEST_STRING")

add_executable(
        ${test_name}
        ${torchlight_dir}/src/Collections/String/String.cpp
        ${torchlight_dir}/src/Collections/String/StringHelper.cpp
        ${torchlight_dir}/test/unittest/Collections/String.cpp
)

# gtest
target_link_libraries(${test_name} gtest gtest_main torchlight_common)
add_test(NAME ${test_name} COMMAND ${test_name})
