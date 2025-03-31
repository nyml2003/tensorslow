# 定义路径和可执行文件
$build_dir = "../release"
$test_dir = "../test/integration"
$frontend_exe = Join-Path $build_dir "torchlight_frontend"
$backend_exe = Join-Path $build_dir "torchlight_backend"

# 获取源代码文件路径
$source_code = "../test/dev/dev.py"

# 显示源代码内容
Write-Host "源代码:"
# Get-Content $source_code
Write-Host

# 编译到字节码
Write-Host "正在编译到字节码..."
& $frontend_exe --file "$source_code" 2>&1 | ForEach-Object { Write-Host $_ }
Write-Host

# 执行字节码（替换文件扩展名为.pyc）
$backend_file = $source_code -replace '\.py$', '.pyc'
Write-Host "正在读取并执行字节码..."
if (Test-Path $backend_file)
{
    & $backend_exe --file "$backend_file" 2>&1 | ForEach-Object { Write-Host $_ }
}
else
{
    Write-Host "错误：字节码文件未生成或路径无效。"
}
Write-Host