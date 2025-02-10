
# 设置基础目录和脚本路径
$base_dir = "D:\code\project\torchlight"
$print_code = "print_code.py"
$script_to_run = "fibonacci.py"

# 构建 Docker 命令
$docker_cmd = "docker run -it --rm -v {0}:/app python:3.6 python /app/temp/{1} /app/test/integration/{2}" -f $base_dir, $print_code, $script_to_run

# 输出 Docker 命令
Write-Output "Docker command: "
Write-Output $docker_cmd

# 执行 Docker 命令
Invoke-Expression $docker_cmd
