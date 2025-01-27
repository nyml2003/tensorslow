#!/bin/bash
build_dir=/app/build
test_dir=/app/test/integration
# 遍历所有的测试用例，以py结尾
for test_case in $(ls $test_dir | grep -E "*.py$"); do
    test_case_name=$(basename $test_case .py) 
    echo 
    echo "Testing $test_case_name"
    echo "===================="
    echo "Source code:"
    cat $test_dir/$test_case_name.py
    echo 
    echo "frontend:"
    $build_dir/torchlight_frontend -f $test_dir/$test_case_name.py
    echo 
    echo "backend:"
    $build_dir/torchlight_backend -f $test_dir/$test_case_name.pyc
    echo 
done