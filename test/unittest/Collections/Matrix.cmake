set(test_name "TEST_MATRIX")

add_executable(
        ${test_name}

        ${tensorslow_dir}/test/unittest/Collections/Matrix.cpp
)

# gtest
target_link_libraries(${test_name} gtest gtest_main tensorslow_common)
add_test(NAME ${test_name} COMMAND ${test_name})
