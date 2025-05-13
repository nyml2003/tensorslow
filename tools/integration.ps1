# 设置路径和构建类型
param(
    [string]$buildType = "release"
)

$scriptPath = "$PSScriptRoot\.."
$buildDir = Join-Path $scriptPath $buildType
$testDir = Join-Path $scriptPath "test\integration"

if ($buildType -notin @("release", "debug")) {
    Write-Host "Invalid build type: $buildType"
    exit 1
}

if (-not (Test-Path $buildDir)) {
    Write-Host "Build directory not found: $buildDir"
    exit 1
}

$frontendExe = Join-Path $buildDir "tensorslow_compiler.exe"
$backendExe = Join-Path $buildDir "tensorslow_interpreter.exe"

# 获取所有子目录作为测试用例
$subdirs = Get-ChildItem -Path $testDir -Directory | Select-Object -ExpandProperty Name
$testTotal = $subdirs.Count

Write-Host "测试用例总数: $testTotal"
if ($testTotal -eq 0) {
    Write-Host "没有测试用例"
    exit 0
}

$testPassed = 0
$testNotPassedNames = @()

Write-Host "测试用例: $($subdirs -join ' ')"

foreach ($subdir in $subdirs) {
    $subdirPath = Join-Path $testDir $subdir

    # 删除旧的 .pyc 和 .out 文件
    Get-ChildItem -Path $subdirPath -Filter *.pyc | Remove-Item
    Get-ChildItem -Path $subdirPath -Filter *.out | Remove-Item

    # 获取所有 .py 文件
    $pyFiles = Get-ChildItem -Path $subdirPath -Filter *.py | Select-Object -ExpandProperty FullName

    foreach ($pyFile in $pyFiles) {
        # Write-Host "$frontendExe --file=$pyFile"
        & $frontendExe "--file=$pyFile"
    }

    # 查找 main.pyc 或任意一个 .pyc
    $mainPyc = Join-Path $subdirPath "main.pyc"
    if (Test-Path $mainPyc) {
        $selectedPyc = $mainPyc
    } else {
        $pycFiles = Get-ChildItem -Path $subdirPath -Filter *.pyc | Select-Object -ExpandProperty FullName
        if ($pycFiles.Count -gt 0) {
            $selectedPyc = $pycFiles[0]
        } else {
            Write-Host "警告：${subdir} 目录中没有找到 .pyc 文件"
            $selectedPyc = $null
        }
    }

    if ($selectedPyc) {
        # Write-Host "$backendExe --file=$selectedPyc --compare_result=true"
        $result = & $backendExe "--file=$selectedPyc" "--compare_result=true"
        if ($LASTEXITCODE -eq 0) {
            $testPassed++
            # Write-Host "测试 $subdir 成功"
        } else {
            $testNotPassedNames += $subdir
            Write-Host "测试 $subdir 失败"
        }
    } else {
        Write-Host "警告：${subdir} 目录中没有有效的 .pyc 文件"
        $testNotPassedNames += $subdir
    }
}

# 输出统计信息
$percentage = [math]::Round(($testPassed / $testTotal) * 100, 2)
Write-Host "通过率: ${percentage}%"

if ($testPassed -eq $testTotal) {
    Write-Host "所有测试用例通过"
} else {
    Write-Host "不通过的测试用例数: $($testNotPassedNames.Count)"
    Write-Host "不通过的测试用例: $($testNotPassedNames -join ' ')"
}