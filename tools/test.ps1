# -*- coding: utf-8 -*-
$buildType = "release"


# 根据传参判断是build还是release
if ($buildType -eq "release")
{
    $buildDir = "D:\code\project\torchlight\release"
}
elseif ($buildType -eq "debug")
{
    $buildDir = "D:\code\project\torchlight\build"
}
else
{
    Write-Host "Invalid build type: $buildType"
    exit 1
}

# 定义路径和可执行文件
$testDir = "D:\code\project\torchlight\test\integration"
$frontendExe = Join-Path -Path $buildDir -ChildPath "torchlight_frontend.exe"
$backendExe = Join-Path -Path $buildDir -ChildPath "torchlight_backend.exe"

# 获取测试目录下的所有子目录
$subdirs = Get-ChildItem -Path $testDir -Directory | ForEach-Object { $_.Name }

# 计算测试总数
$testTotal = $subdirs.Count
Write-Host "测试用例总数: $testTotal"
if ($testTotal -eq 0)
{
    Write-Host "没有测试用例"
    exit 0
}

$testPassed = 0
$testNotPassedNames = @()
Write-Host "测试用例: $( $subdirs -join ' ' )"
foreach ($subdir in $subdirs)
{
    # 构建子目录路径
    $subdirPath = Join-Path -Path $testDir -ChildPath $subdir

    # 删除.pyc和.out文件
    Get-ChildItem -Path $subdirPath -Filter "*.pyc" | ForEach-Object { Remove-Item $_.FullName }
    Get-ChildItem -Path $subdirPath -Filter "*.out" | ForEach-Object { Remove-Item $_.FullName }

    # 获取所有.py文件（排除.pyc）
    $pyFiles = Get-ChildItem -Path $subdirPath -Filter "*.py"

    foreach ($pyFile in $pyFiles)
    {
        $sourceCode = $pyFile.FullName
        # Write-Host "源代码:"
        # Get-Content -Path $sourceCode -Encoding UTF8 | Write-Host
        # Write-Host "正在编译到字节码..."

        # 打印前端执行命令
        $frontendCommand = @($frontendExe, "--file=$sourceCode")
        # Write-Host $frontendCommand
        Start-Process -FilePath $frontendCommand[0] -ArgumentList $frontendCommand[1] -Wait -NoNewWindow
    }

    # 选择执行的.pyc文件
    $mainPyc = Join-Path -Path $subdirPath -ChildPath "main.pyc"
    if (Test-Path -Path $mainPyc)
    {
        $selectedPyc = $mainPyc
    }
    else
    {
        $pycFiles = Get-ChildItem -Path $subdirPath -Filter "*.pyc"
        if ($pycFiles.Count -gt 0)
        {
            $selectedPyc = $pycFiles[0].FullName
        }
        else
        {
            Write-Host "警告：$subdir 目录中没有找到 .pyc 文件"
            $selectedPyc = $null
        }
    }

    if ($selectedPyc)
    {
        # Write-Host "source_code: $selectedPyc"
        # Write-Host "正在读取并执行字节码..."

        # 打印后端执行命令
        $backendCommand = @($backendExe, "--file=$selectedPyc", "--compare_result=true")
        # Write-Host $backendCommand
        $result = Start-Process -FilePath $backendCommand[0] -ArgumentList $backendCommand[1..2] -Wait -NoNewWindow -PassThru
        if ($result.ExitCode -eq 0)
        {
            $testPassed++
            # Write-Host "测试 $subdir 成功"
        }
        else
        {
            $testNotPassedNames += $subdir
            Write-Host "测试 $subdir 失败"
        }
    }
    else
    {
        Write-Host "警告：$subdir 目录中没有有效的 .pyc 文件"
        $testNotPassedNames += $subdir
    }
}

# 计算通过率
$percentage = [math]::Round(($testPassed / $testTotal) * 100, 2)
Write-Host "通过率: $percentage%"

if ($testPassed -eq $testTotal)
{
    Write-Host "所有测试用例通过"
}
else
{
    Write-Host "不通过的测试用例数: $( $testNotPassedNames.Count )"
    Write-Host "不通过的测试用例: $( $testNotPassedNames -join ' ' )"
}