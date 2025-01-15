set(test_name "TEST_MAP")

add_executable(
    ${test_name}
    ${torchlight_dir}/src/collections/Iterator.cpp
    ${torchlight_dir}/src/collections/List.cpp
    ${torchlight_dir}/src/collections/String.cpp
    ${torchlight_dir}/src/collections/Bytes.cpp
    ${torchlight_dir}/src/collections/Integer.cpp
    ${torchlight_dir}/src/collections/Decimal.cpp
    ${torchlight_dir}/src/collections/Map.cpp
    ${torchlight_dir}/src/object/Klass.cpp
    ${torchlight_dir}/src/object/PyObject.cpp
    ${torchlight_dir}/src/object/PyString.cpp
    ${torchlight_dir}/src/object/PyBytes.cpp
    ${torchlight_dir}/src/object/PyInteger.cpp
    ${torchlight_dir}/src/object/PyBoolean.cpp
    ${torchlight_dir}/src/object/ByteCode.cpp
    ${torchlight_dir}/src/object/PyDictionary.cpp
    ${torchlight_dir}/test/unittest/Map.cpp
)

# gtest
target_link_libraries(${test_name} gtest gtest_main)
add_test(NAME ${test_name} COMMAND ${test_name})
