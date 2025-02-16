set(test_name "TEST_TOOLS")

add_executable(
    ${test_name}
    ${torchlight_dir}/test/extra/test_tools.cpp
    ${torchlight_dir}/src/Tools/Tools.cpp
)

# gtest
target_link_libraries(${test_name} gtest gtest_main)
add_test(NAME ${test_name} COMMAND ${test_name})
