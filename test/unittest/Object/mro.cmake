set(test_name "TEST_MRO")

add_executable(
        ${test_name}
        ${tensorslow_dir}/test/unittest/Object/MRO.cpp
)

# gtest
target_link_libraries(${test_name} gtest gtest_main tensorslow_common)
add_test(NAME ${test_name} COMMAND ${test_name})
