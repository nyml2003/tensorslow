#!/bin/bash
root_dir=/home/test/Desktop/torchlight
build_dir=$root_dir/build
test_dir=$root_dir/test/integration
frontend_exe=$build_dir/torchlight_frontend
backend_exe=$build_dir/torchlight_backend

# 遍历test_dir
subdirs=$(ls $test_dir)

# 目录数
test_total=$(ls $test_dir | wc -l)
if [ $test_total -eq 0 ]; then
    echo "没有测试用例"
    exit 0
fi
test_passed=0
test_not_passed_names=()
for subdir in $subdirs
do
    # 删除目录下的所有.pyc文件和所有.out文件
    rm -f $test_dir/$subdir/*.pyc
    rm -f $test_dir/$subdir/*.out
    echo '---------------------------------'
    # 扫描subdir下的所有py文件
    pys=$(ls $test_dir/$subdir | grep .py | grep -v .pyc)
    for py in $pys
    do
        source_code=$test_dir/$subdir/$py
        echo "源代码:"
        cat $source_code
        echo 
        echo "正在编译到字节码..."
        $frontend_exe --file="$source_code"
        echo 
    done
    # 扫描subdir下的所有pyc文件,如果有main.pyc就选择main.pyc，否则选择第一个pyc文件
    pycs=$(ls $test_dir/$subdir | grep .pyc)
    main_pyc=$(ls $test_dir/$subdir | grep main.pyc)
    if [ -n "$main_pyc" ]; then
        pyc=main.pyc
    else
        pyc=$(ls $test_dir/$subdir | grep .pyc | head -n 1)
    fi
    source_code=$test_dir/$subdir/$pyc
    echo source_code: $source_code
    echo "正在读取并执行字节码..."
    $backend_exe --file="$source_code" --compare_result=true
    if [ $? -eq 0 ]; then
        test_passed=$((test_passed+1))
        test_passed_names+=($subdir)
    else
        test_not_passed_names+=($subdir)
    fi
    echo '---------------------------------'
    echo
done
# 百分比 *100%

echo "通过率: $(echo "scale=2; $test_passed / $test_total * 100" | bc)%"
if [ $test_passed -eq $test_total ]; then
    echo "所有测试用例通过"
else
    echo "不通过的测试用例数: ${#test_not_passed_names[@]}"
    echo "不通过的测试用例: ${test_not_passed_names[@]}"
fi

