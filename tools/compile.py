import os
import subprocess

# 定义路径和可执行文件
build_dir = "../debug"
test_dir = "../test/integration"
frontend_exe = os.path.join(build_dir, "torchlight_frontend")
backend_exe = os.path.join(build_dir, "torchlight_backend")

# 获取源代码文件路径
source_code = "../ml/adaline_batch.py"
# source_code = "../test/dev/dev.py"
# 显示源代码内容
print("源代码:")
with open(source_code, 'r', encoding='utf-8') as file:
    print(file.read())

# 编译到字节码
print("正在编译到字节码...")
frontend_command = [frontend_exe, f"--file={source_code}"]
result = subprocess.run(frontend_command)

# 执行字节码（替换文件扩展名为.pyc）
backend_file = source_code.replace('.py', '.pyc')
print("正在读取并执行字节码...")
if os.path.exists(backend_file):
    backend_command = [backend_exe, f"--file={backend_file}"]
    print(backend_command)
    result = subprocess.run(backend_command)
else:
    print("错误：字节码文件未生成或路径无效。")
