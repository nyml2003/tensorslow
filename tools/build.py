#!/usr/bin/env python3
import os
import subprocess
import multiprocessing
import sys


def parse_args():
    build_type = "Release"  # 默认是 Release 构建
    help_message = f"Usage: {sys.argv[0]} [-d | -r]"

    if len(sys.argv) == 1:
        print("[INFO] No build type specified, defaulting to Release.")
        return build_type

    if len(sys.argv) != 2:
        print(help_message)
        sys.exit(1)

    arg = sys.argv[1]
    if arg == "-d":
        build_type = "Debug"
    elif arg == "-r":
        build_type = "Release"
    else:
        print(f"Unknown argument: {arg}")
        print(help_message)
        sys.exit(1)

    return build_type


def main():
    build_type = parse_args()
    build_dir = f"build/{build_type}"

    print(f"[INFO] Building in {build_type} mode...")

    # 创建 build 目录（如果不存在）
    if not os.path.exists(build_dir):
        os.makedirs(build_dir)

    # 切换到 build 目录
    os.chdir(build_dir)

    # 配置 CMake
    cmake_configure_cmd = [
        "cmake",
        "-G",
        "Ninja",
        f"-DCMAKE_BUILD_TYPE={build_type}",
        "../..",
    ]

    print("[CMD] " + " ".join(cmake_configure_cmd))
    subprocess.run(cmake_configure_cmd, check=True)

    # 并行构建
    cpu_count = multiprocessing.cpu_count()
    cmake_build_cmd = ["cmake", "--build", ".", "--", f"-j{cpu_count}"]

    print("[CMD] " + " ".join(cmake_build_cmd))
    subprocess.run(cmake_build_cmd, check=True)

    print(f"[INFO] Successfully built in {build_type} mode!")


if __name__ == "__main__":
    main()
