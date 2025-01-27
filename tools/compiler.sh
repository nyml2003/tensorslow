#!/bin/bash
build_dir=/app/build
test_dir=/app/test/integration
# 遍历所有的测试用例，以py结尾
for test_case in $(ls $test_dir | grep -E "*.py$"); do
    test_case_name=$(basename $test_case .py) 
    # 运行测试用例
    cat $test_dir/$test_case_name.py
    $build_dir/torchlight_frontend
    $build_dir/torchlight_backend
done