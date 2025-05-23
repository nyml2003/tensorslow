#!/bin/bash
cd ..

# 初始化覆盖率数据
lcov -d build -z
lcov -d build -b . --no-external --initial -c -o build/initial_coverage.info

# 编译项目
cmake -B build
cmake --build build --config Debug

# 运行测试
python3 integration.py debug


# 生成最终覆盖率数据
lcov -d build -b . --no-external -c  -o build/coverage.info

# 合并初始和最终覆盖率数据
lcov -a build/initial_coverage.info -a build/coverage.info -o build/total_coverage.info

# 生成 HTML 报告
genhtml -o build/coverage_report --prefix=$(pwd) build/total_coverage.info