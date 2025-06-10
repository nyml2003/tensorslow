#!/usr/bin/env python3
import os
import subprocess
import multiprocessing


def main():
    build_dir = "build/Debug"
    if not os.path.exists(build_dir):
        os.makedirs(build_dir)

    # Change to the build directory
    os.chdir(build_dir)

    # Configure with Release mode
    subprocess.run(
        ["cmake", "-G", "Ninja", "-DCMAKE_BUILD_TYPE=Debug", "../.."], check=True
    )

    # Build with parallel jobs
    cpu_count = multiprocessing.cpu_count()
    subprocess.run(["cmake", "--build", ".", "--", f"-j{cpu_count}"], check=True)


if __name__ == "__main__":
    main()
