#!/bin/bash
build_dir=/app/build
test_dir=/app/test/integration
frontend_exe=$build_dir/tensorslow_frontend
backend_exe=$build_dir/tensorslow_backend
source_code=$1

echo "源代码:"
cat $source_code
echo 
echo "正在编译到字节码..."
$frontend_exe --file="$source_code"
echo 
echo "正在读取并执行字节码..."
$backend_exe --file="$source_code"c
echo 
