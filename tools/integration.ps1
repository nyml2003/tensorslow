# 定义路径和可执行文件
param (
    [string]$buildType = "build"  # Default to "build" if no parameter is provided
)

# 根据传参判断是build还是release
if ($buildType -eq "release") {
    $build_dir = "D:\code\project\torchlight\release"
} else {
    $build_dir = "D:\code\project\torchlight\build"
}

Write-Host "Build directory: $build_dir"
$test_dir = "D:\code\project\torchlight\test/integration"
$frontend_exe = "$build_dir/torchlight_frontend"
$backend_exe = "$build_dir/torchlight_backend"

# 获取测试目录下的所有子目录
$subdirs = Get-ChildItem -Path $test_dir -Directory | Select-Object -ExpandProperty Name

# 计算测试总数
$test_total = $subdirs.Count
if ($test_total -eq 0) {
    Write-Host "没有测试用例"
    exit 0
}

$test_passed = 0
$test_not_passed_names = @()

foreach ($subdir in $subdirs) {
    # 构建子目录路径
    $subdirPath = Join-Path $test_dir $subdir

    # 删除.pyc和.out文件
    Write-Host "Remove-Item -Path `"$subdirPath/*.pyc`" -Force -ErrorAction SilentlyContinue"
    Remove-Item -Path "$subdirPath/*.pyc" -Force -ErrorAction SilentlyContinue

    Write-Host "Remove-Item -Path `"$subdirPath/*.out`" -Force -ErrorAction SilentlyContinue"
    Remove-Item -Path "$subdirPath/*.out" -Force -ErrorAction SilentlyContinue

    Write-Host '---------------------------------'

    # 获取所有.py文件（排除.pyc）
    $pys = Get-ChildItem -Path $subdirPath -Filter *.py | Where-Object { $_.Extension -eq ".py" }

    foreach ($py in $pys) {
        $source_code = $py.FullName
        Write-Host "源代码:"
        Get-Content $source_code
        Write-Host
        Write-Host "正在编译到字节码..."

        # 打印前端执行命令
        $frontend_command = "& `"$frontend_exe`" --file=`"$source_code`""
        Write-Host $frontend_command
        & $frontend_exe --file="$source_code"
        Write-Host
    }

    # 选择执行的.pyc文件
    $main_pyc = Get-ChildItem -Path $subdirPath -Filter main.pyc -ErrorAction SilentlyContinue
    if ($main_pyc) {
        $selected_pyc = $main_pyc.FullName
    } else {
        $pycs = Get-ChildItem -Path $subdirPath -Filter *.pyc
        if ($pycs.Count -gt 0) {
            $selected_pyc = $pycs[0].FullName
        } else {
            Write-Host "警告：$subdir 目录中没有找到 .pyc 文件"
            $selected_pyc = $null
        }
    }

    if ($selected_pyc) {
        Write-Host "source_code: $selected_pyc"
        Write-Host "正在读取并执行字节码..."

        # 打印后端执行命令
        $backend_command = "& `"$backend_exe`" --file=`"$selected_pyc`" --compare_result=`"true`""
        Write-Host $backend_command
        & $backend_exe --file="$selected_pyc" --compare_result="true"

        if ($LASTEXITCODE -eq 0) {
            $test_passed++
            Write-Host "测试 $subdir 成功"
        } else {
            $test_not_passed_names += $subdir
            Write-Host "测试 $subdir 失败"
        }

    } else {
        Write-Host "警告：$subdir 目录中没有有效的 .pyc 文件"
        $test_not_passed_names += $subdir
    }

    Write-Host '---------------------------------'
    Write-Host
}

# 计算通过率
$percentage = [math]::Round( ($test_passed / $test_total)*100, 2 )
Write-Host "通过率: $percentage%"

if ($test_passed -eq $test_total) {
    Write-Host "所有测试用例通过"
} else {
    Write-Host "不通过的测试用例数: $($test_not_passed_names.Count)"
    Write-Host "不通过的测试用例: $($test_not_passed_names -join ' ')"
}