# -*- coding: utf-8 -*-
import glob
import os
import subprocess
import sys

# 定义路径和可执行文件
build_type = sys.argv[1] if len(sys.argv) > 1 else "release"

# 根据传参判断是build还是release
if build_type == "release":
    build_dir = r"D:\code\project\tensorslow\release"
elif build_type == "debug":
    build_dir = r"D:\code\project\tensorslow\debug"
else:
    print(f"Invalid build type: {build_type}")
    sys.exit(1)

test_dir = r"D:\code\project\tensorslow\test\integration"
frontend_exe = os.path.join(build_dir, "tensorslow_compiler.exe")
backend_exe = os.path.join(build_dir, "tensorslow_interpreter.exe")

# 获取测试目录下的所有子目录
subdirs = [d for d in os.listdir(test_dir) if os.path.isdir(os.path.join(test_dir, d))]

# 计算测试总数
test_total = len(subdirs)
print(f"测试用例总数: {test_total}")
if test_total == 0:
    print("没有测试用例")
    sys.exit(0)

test_passed = 0
test_not_passed_names = []
print("测试用例:", ' '.join(subdirs))
for subdir in subdirs:
    # 构建子目录路径
    subdir_path = os.path.join(test_dir, subdir)

    # 删除.pyc和.out文件
    for file in glob.glob(os.path.join(subdir_path, "*.pyc")):
        os.remove(file)
    for file in glob.glob(os.path.join(subdir_path, "*.out")):
        os.remove(file)

    # 获取所有.py文件（排除.pyc）
    py_files = glob.glob(os.path.join(subdir_path, "*.py"))

    for py_file in py_files:
        source_code = py_file
        # 打印前端执行命令
        frontend_command = [frontend_exe, '--file=' + source_code]
        print(' '.join(frontend_command))  # 输出命令以便调试
        result = subprocess.run(frontend_command)

    # 选择执行的.pyc文件
    main_pyc = os.path.join(subdir_path, "main.pyc")
    if os.path.exists(main_pyc):
        selected_pyc = main_pyc
    else:
        pyc_files = glob.glob(os.path.join(subdir_path, "*.pyc"))
        if pyc_files:
            selected_pyc = pyc_files[0]
        else:
            print(f"警告：{subdir} 目录中没有找到 .pyc 文件")
            selected_pyc = None

    if selected_pyc:
        # 打印后端执行命令
        backend_command = [backend_exe, '--file=' + selected_pyc, '--compare_result=true']
        print(' '.join(backend_command))  # 输出命令以便调试
        result = subprocess.run(backend_command)
        if result.returncode == 0:
            test_passed += 1
            print(f"测试 {subdir} 成功")
        else:
            test_not_passed_names.append(subdir)
            print(f"测试 {subdir} 失败")
    else:
        print(f"警告：{subdir} 目录中没有有效的 .pyc 文件")
        test_not_passed_names.append(subdir)

# 计算通过率
percentage = round((test_passed / test_total) * 100, 2)
print(f"通过率: {percentage}%")

if test_passed == test_total:
    print("所有测试用例通过")
else:
    print(f"不通过的测试用例数: {len(test_not_passed_names)}")
    print(f"不通过的测试用例: {' '.join(test_not_passed_names)}")