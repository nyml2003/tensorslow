import os
import subprocess

# 定义路径和可执行文件
build_dir = "../release"
test_dir = "../test/integration"
frontend_exe = os.path.join(build_dir, "torchlight_frontend")
backend_exe = os.path.join(build_dir, "torchlight_backend")

# 获取源代码文件路径
source_code = "../test/dev/dev.py"

# 显示源代码内容
print("源代码:")
with open(source_code, 'r') as file:
    print(file.read())
print()

# 编译到字节码
print("正在编译到字节码...")
frontend_command = [frontend_exe, f"--file={source_code}"]
result = subprocess.run(frontend_command, capture_output=True, text=True)
print(result.stdout)
if result.stderr:
    print(result.stderr)

# 执行字节码（替换文件扩展名为.pyc）
backend_file = source_code.replace('.py', '.pyc')
print("正在读取并执行字节码...")
if os.path.exists(backend_file):
    backend_command = [backend_exe, f"--file={backend_file}"]
    result = subprocess.run(backend_command, capture_output=True, text=True)
    print(result.stdout)
    if result.stderr:
        print(result.stderr)
else:
    print("错误：字节码文件未生成或路径无效。")
