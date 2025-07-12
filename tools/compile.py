import os
import subprocess
import sys

# 测试文件列表（可自由添加更多）
test_files = ["./test/ml/iris.py", "./test/dev/dev.py"]


def parse_args():
    build_type = "Release"
    test_index = None
    help_message = f"Usage: {sys.argv[0]} [-d | -r] [-t N]"

    if len(sys.argv) < 2:
        print("[INFO] No arguments provided, using default settings.")
        return build_type, test_index

    args = sys.argv[1:]
    i = 0
    while i < len(args):
        arg = args[i]
        if arg == "-d":
            build_type = "Debug"
        elif arg == "-r":
            build_type = "Release"
        elif arg == "-t":
            if i + 1 >= len(args):
                print("缺少 -t 参数值")
                print(help_message)
                sys.exit(1)
            try:
                test_index = int(args[i + 1])
                i += 1  # 跳过值部分
            except ValueError:
                print(f"无效的测试文件编号: {args[i + 1]}")
                sys.exit(1)
        else:
            print(f"未知参数: {arg}")
            print(help_message)
            sys.exit(1)
        i += 1

    return build_type, test_index


if __name__ == "__main__":
    build_type, test_index = parse_args()

    # 构建路径
    build_dir = f"./build/{build_type}"
    frontend_exe = os.path.join(build_dir, "tensorslow_compiler")
    backend_exe = os.path.join(build_dir, "tensorslow_interpreter")

    # 如果未指定测试文件编号，则提示用户选择
    if test_index is None:
        print("请选择要运行的测试文件：")
        for i, file in enumerate(test_files):
            print(f"{i}: {file}")
        try:
            choice = int(input("请输入文件编号: "))
            source_code = test_files[choice]
        except (ValueError, IndexError):
            print("无效的选择。")
            sys.exit(1)
    else:
        try:
            source_code = test_files[test_index]
        except IndexError:
            print(f"错误：测试文件索引超出范围（有效范围：0~{len(test_files)-1}）")
            sys.exit(1)

    # 显示源代码内容
    print("\n源代码:")
    with open(source_code, "r", encoding="utf-8") as file:
        print(file.read())

    # 编译到字节码
    print("\n正在编译到字节码...")
    frontend_command = [frontend_exe, f"--file={source_code}"]
    print("执行命令:", frontend_command)
    result = subprocess.run(frontend_command)
    if result.returncode != 0:
        print("编译失败。")
        sys.exit(1)

    # 执行字节码
    backend_file = source_code.replace(".py", ".pyc")
    print("\n正在读取并执行字节码...")
    if os.path.exists(backend_file):
        backend_command = [backend_exe, f"--file={backend_file}"]
        print("执行命令:", backend_command)
        result = subprocess.run(backend_command)
        if result.returncode != 0:
            print("执行失败。")
    else:
        print("错误：字节码文件未生成或路径无效。")
