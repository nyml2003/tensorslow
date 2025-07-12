# -*- coding: utf-8 -*-
import glob
import os
import subprocess
import sys


def parse_args():
    args = sys.argv[1:]

    build_type = "Release"
    test_type = "base"

    help_msg = (
        "Usage: python test_runner.py [-d | -r] [-b | -ml | -a]\n"
        "Options:\n"
        "  -d            Debug 模式\n"
        "  -r            Release 模式（默认）\n"
        "  -b            Base 测试（默认）\n"
        "  -ml           ML 测试\n"
        "  -a            同时运行 Base 和 Integration 测试"
    )

    if "-h" in args or "--help" in args:
        print(help_msg)
        sys.exit(0)

    i = 0
    while i < len(args):
        arg = args[i]

        if arg == "-d":
            build_type = "Debug"
        elif arg == "-r":
            build_type = "Release"
        elif arg == "-b":
            test_type = ["base"]
        elif arg == "-ml":
            test_type = ["ml"]
        elif arg == "-a":
            test_type = ["base", "ml"]
        else:
            print(f"未知参数: {arg}")
            print(help_msg)
            sys.exit(1)

        i += 1

    return build_type, test_type


def run_test_suite(build_type, test_dir, suite_name):
    frontend_exe = os.path.join(f"build/{build_type}", "tensorslow_compiler.exe")
    backend_exe = os.path.join(f"build/{build_type}", "tensorslow_interpreter.exe")

    # 检查编译器和解释器是否存在
    if not os.path.exists(frontend_exe):
        print(f"前端不存在: {frontend_exe}")
        sys.exit(1)
    if not os.path.exists(backend_exe):
        print(f"后端不存在: {backend_exe}")
        sys.exit(1)

    if not os.path.exists(test_dir):
        print(f"测试目录不存在: {test_dir}")
        sys.exit(1)

    subdirs = [
        d for d in os.listdir(test_dir) if os.path.isdir(os.path.join(test_dir, d))
    ]
    test_total = len(subdirs)
    print(f"[{suite_name}] 测试用例总数: {test_total}")
    if test_total == 0:
        print(f"[{suite_name}] 没有测试用例")
        return 0, 0

    test_passed = 0
    test_not_passed_names = []

    print(f"[{suite_name}] 测试用例: {' '.join(subdirs)}")

    for subdir in subdirs:
        subdir_path = os.path.join(test_dir, subdir)

        # 删除旧文件
        for file in glob.glob(os.path.join(subdir_path, "*.pyc")) + glob.glob(
            os.path.join(subdir_path, "*.out")
        ):
            os.remove(file)

        # 编译所有 .py 文件
        py_files = glob.glob(os.path.join(subdir_path, "*.py"))
        for py_file in py_files:
            source_code = py_file
            frontend_command = [frontend_exe, "--file=" + source_code]
            print("[CMD]", " ".join(frontend_command))
            result = subprocess.run(frontend_command)
            if result.returncode != 0:
                print(f"[ERROR] 编译失败: {source_code}")
                continue

        # 查找 pyc 文件
        main_pyc = os.path.join(subdir_path, "main.pyc")
        if os.path.exists(main_pyc):
            selected_pyc = main_pyc
        else:
            pyc_files = glob.glob(os.path.join(subdir_path, "*.pyc"))
            if pyc_files:
                selected_pyc = pyc_files[0]
            else:
                print(f"[WARN] {subdir} 中没有找到 .pyc 文件")
                test_not_passed_names.append(subdir)
                continue

        # 运行解释器
        backend_command = [
            backend_exe,
            "--file=" + selected_pyc,
            "--compare_result=true",
        ]
        print("[CMD]", " ".join(backend_command))
        result = subprocess.run(backend_command)

        if result.returncode == 0:
            test_passed += 1
            print(f"[{suite_name}] [PASS] 测试 {subdir} 成功")
        else:
            test_not_passed_names.append(subdir)
            print(f"[{suite_name}] [FAIL] 测试 {subdir} 失败")

    percentage = round((test_passed / test_total) * 100, 2)
    print(f"[{suite_name} RESULT] 通过率: {percentage}%")

    if test_passed == test_total:
        print(f"[{suite_name} SUCCESS] 所有测试用例通过")
    else:
        print(f"[{suite_name} FAILED] 不通过的测试用例数: {len(test_not_passed_names)}")
        print(f"不通过的测试用例: {' '.join(test_not_passed_names)}")

    return test_passed, test_total


def main():
    build_type, test_type = parse_args()

    total_passed = 0
    total_tests = 0

    if "base" in test_type:
        base_passed, base_total = run_test_suite(build_type, "test/base", "BASE")
        total_passed += base_passed
        total_tests += base_total

    if "ml" in test_type:
        ml_passed, ml_total = run_test_suite(build_type, "test/ml_base", "ML")
        total_passed += ml_passed
        total_tests += ml_total

    overall_percentage = round((total_passed / total_tests) * 100, 2)
    print(
        f"[OVERALL RESULT] 总体通过率: {total_passed} / {total_tests} = {overall_percentage}%"
    )

    if total_passed == total_tests:
        print("[OVERALL SUCCESS] 所有测试套件通过")
    else:
        print(f"[OVERALL FAILED] 总共有 {total_tests - total_passed} 个测试未通过")


if __name__ == "__main__":
    main()
