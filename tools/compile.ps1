# 定义路径和可执行文件
$buildDir = "../release"
$testDir = "../test/integration"
$frontendExe = Join-Path -Path $buildDir -ChildPath "tensorslow_compiler.exe"
$backendExe = Join-Path -Path $buildDir -ChildPath "tensorslow_interpreter.exe"

# 获取源代码文件路径
# $sourceCode = "../test/ml/adaline.py"
$sourceCode = "../test/ml/iris.py"
# 显示源代码内容
Write-Host "正在读取源代码..."
Get-Content -Path $sourceCode

# 编译到字节码
Write-Host "正在编译到字节码..."
$frontendCommand = @($frontendExe, "--file=$sourceCode")
Start-Process -FilePath $frontendCommand[0] -ArgumentList $frontendCommand[1] -Wait

# 执行字节码（替换文件扩展名为.pyc）
$backendFile = $sourceCode -replace '\.py$', '.pyc'
Write-Host "编译完成，字节码文件为：$backendFile"
Write-Host "正在读取并执行字节码..."

$backendCommand = @($backendExe, "--file=$backendFile")
& $backendCommand[0] $backendCommand[1]

