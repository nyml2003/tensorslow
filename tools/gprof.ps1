# 定义变量
$tool_dir = "C:\tools\msys64\mingw64\bin"
$gprof = Join-Path -Path $tool_dir -ChildPath "gprof.exe"
$objdump = Join-Path -Path $tool_dir -ChildPath "objdump.exe"
$dir = "D:\code\project\torchlight\build"
$backend = "torchlight_frontend.exe"
$gmon_file = "gmon.out"
$gprof_file = "gprof.txt"

# 拼接完整路径
$backend_path = Join-Path -Path $dir -ChildPath $backend
$gmon_path = Join-Path -Path $dir -ChildPath $gmon_file
$gprof_path = Join-Path -Path $dir -ChildPath $gprof_file

# 检测
& $objdump -t $backend_path

# 生成 gprof.txt 文件
& $gprof $backend_path  -p $gmon_path | Out-File -FilePath $gprof_path -Encoding utf8

Write-Host "gprof analysis completed. Output written to $gprof_path"