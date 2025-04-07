# 定义参数
$torchlight_src_dir = "D:\code\project\torchlight\src"  # 替换为实际路径
$exclude_dir = "MockFront"  # 排除的子目录名称

# 查找符合条件的文件（.h 和 .cpp），排除指定子目录
$files = Get-ChildItem -Path $torchlight_src_dir -Recurse -Include *.h, *.cpp |
        Where-Object { $_.FullName -notmatch [regex]::Escape("$torchlight_src_dir\$exclude_dir") }

# 统计总行数
$total_lines = 0
foreach ($file in $files)
{
    $file_path = $file.FullName
    $file_name = $file.Name
    $line_count = Get-Content $file.FullName | Measure-Object -Line | Select-Object -ExpandProperty Lines

    # 输出文件信息
    Write-Host ("File Path: $file_path" + "`n" + "Line Count: $line_count" + "`n")

    # 累加总行数
    $total_lines += $line_count
}

Write-Host "Total lines of code: $total_lines"