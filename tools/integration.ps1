# ����·���͹�������
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

# ��ȡ������Ŀ¼��Ϊ��������
$subdirs = Get-ChildItem -Path $testDir -Directory | Select-Object -ExpandProperty Name
$testTotal = $subdirs.Count

Write-Host "������������: $testTotal"
if ($testTotal -eq 0) {
    Write-Host "û�в�������"
    exit 0
}

$testPassed = 0
$testNotPassedNames = @()

Write-Host "��������: $($subdirs -join ' ')"

foreach ($subdir in $subdirs) {
    $subdirPath = Join-Path $testDir $subdir

    # ɾ���ɵ� .pyc �� .out �ļ�
    Get-ChildItem -Path $subdirPath -Filter *.pyc | Remove-Item
    Get-ChildItem -Path $subdirPath -Filter *.out | Remove-Item

    # ��ȡ���� .py �ļ�
    $pyFiles = Get-ChildItem -Path $subdirPath -Filter *.py | Select-Object -ExpandProperty FullName

    foreach ($pyFile in $pyFiles) {
        # Write-Host "$frontendExe --file=$pyFile"
        & $frontendExe "--file=$pyFile"
    }

    # ���� main.pyc ������һ�� .pyc
    $mainPyc = Join-Path $subdirPath "main.pyc"
    if (Test-Path $mainPyc) {
        $selectedPyc = $mainPyc
    } else {
        $pycFiles = Get-ChildItem -Path $subdirPath -Filter *.pyc | Select-Object -ExpandProperty FullName
        if ($pycFiles.Count -gt 0) {
            $selectedPyc = $pycFiles[0]
        } else {
            Write-Host "���棺${subdir} Ŀ¼��û���ҵ� .pyc �ļ�"
            $selectedPyc = $null
        }
    }

    if ($selectedPyc) {
        # Write-Host "$backendExe --file=$selectedPyc --compare_result=true"
        $result = & $backendExe "--file=$selectedPyc" "--compare_result=true"
        if ($LASTEXITCODE -eq 0) {
            $testPassed++
            # Write-Host "���� $subdir �ɹ�"
        } else {
            $testNotPassedNames += $subdir
            Write-Host "���� $subdir ʧ��"
        }
    } else {
        Write-Host "���棺${subdir} Ŀ¼��û����Ч�� .pyc �ļ�"
        $testNotPassedNames += $subdir
    }
}

# ���ͳ����Ϣ
$percentage = [math]::Round(($testPassed / $testTotal) * 100, 2)
Write-Host "ͨ����: ${percentage}%"

if ($testPassed -eq $testTotal) {
    Write-Host "���в�������ͨ��"
} else {
    Write-Host "��ͨ���Ĳ���������: $($testNotPassedNames.Count)"
    Write-Host "��ͨ���Ĳ�������: $($testNotPassedNames -join ' ')"
}