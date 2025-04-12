import os
import subprocess

# 设置基础目录和脚本路径
# 获取当前工作目录的父目录
base_dir = os.path.abspath(os.path.join(os.getcwd(), ".."))
print_code = "print_code.py"
script_to_run = "dev.py"

# 打印变量值以调试
print(f"Base directory: {base_dir}")
print(f"Print code script: {print_code}")
print(f"Script to run: {script_to_run}")

# 构建 Docker 命令
docker_cmd = [
    "docker", "run", "-it", "--rm",
    "-v", f"{base_dir}:/app",
    "python:3.6",
    "python", "/app/tools/print_code.py", "/app/test/dev/dev.py"
]

# 输出 Docker 命令
print("Docker command: ", " ".join(docker_cmd))

# 执行 Docker 命令
try:
    subprocess.run(docker_cmd, check=True)
except subprocess.CalledProcessError as e:
    print(f"Error occurred while running Docker command: {e}")
