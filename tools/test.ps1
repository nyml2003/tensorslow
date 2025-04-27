# -*- coding: utf-8 -*-
$buildType = "release"


# ���ݴ����ж���build����release
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

# ����·���Ϳ�ִ���ļ�
$testDir = "D:\code\project\torchlight\test\integration"
$frontendExe = Join-Path -Path $buildDir -ChildPath "torchlight_frontend.exe"
$backendExe = Join-Path -Path $buildDir -ChildPath "torchlight_backend.exe"

# ��ȡ����Ŀ¼�µ�������Ŀ¼
$subdirs = Get-ChildItem -Path $testDir -Directory | ForEach-Object { $_.Name }

# �����������
$testTotal = $subdirs.Count
Write-Host "������������: $testTotal"
if ($testTotal -eq 0)
{
    Write-Host "û�в�������"
    exit 0
}

$testPassed = 0
$testNotPassedNames = @()
Write-Host "��������: $( $subdirs -join ' ' )"
foreach ($subdir in $subdirs)
{
    # ������Ŀ¼·��
    $subdirPath = Join-Path -Path $testDir -ChildPath $subdir

    # ɾ��.pyc��.out�ļ�
    Get-ChildItem -Path $subdirPath -Filter "*.pyc" | ForEach-Object { Remove-Item $_.FullName }
    Get-ChildItem -Path $subdirPath -Filter "*.out" | ForEach-Object { Remove-Item $_.FullName }

    # ��ȡ����.py�ļ����ų�.pyc��
    $pyFiles = Get-ChildItem -Path $subdirPath -Filter "*.py"

    foreach ($pyFile in $pyFiles)
    {
        $sourceCode = $pyFile.FullName
        # Write-Host "Դ����:"
        # Get-Content -Path $sourceCode -Encoding UTF8 | Write-Host
        # Write-Host "���ڱ��뵽�ֽ���..."

        # ��ӡǰ��ִ������
        $frontendCommand = @($frontendExe, "--file=$sourceCode")
        # Write-Host $frontendCommand
        Start-Process -FilePath $frontendCommand[0] -ArgumentList $frontendCommand[1] -Wait -NoNewWindow
    }

    # ѡ��ִ�е�.pyc�ļ�
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
            Write-Host "���棺$subdir Ŀ¼��û���ҵ� .pyc �ļ�"
            $selectedPyc = $null
        }
    }

    if ($selectedPyc)
    {
        # Write-Host "source_code: $selectedPyc"
        # Write-Host "���ڶ�ȡ��ִ���ֽ���..."

        # ��ӡ���ִ������
        $backendCommand = @($backendExe, "--file=$selectedPyc", "--compare_result=true")
        # Write-Host $backendCommand
        $result = Start-Process -FilePath $backendCommand[0] -ArgumentList $backendCommand[1..2] -Wait -NoNewWindow -PassThru
        if ($result.ExitCode -eq 0)
        {
            $testPassed++
            # Write-Host "���� $subdir �ɹ�"
        }
        else
        {
            $testNotPassedNames += $subdir
            Write-Host "���� $subdir ʧ��"
        }
    }
    else
    {
        Write-Host "���棺$subdir Ŀ¼��û����Ч�� .pyc �ļ�"
        $testNotPassedNames += $subdir
    }
}

# ����ͨ����
$percentage = [math]::Round(($testPassed / $testTotal) * 100, 2)
Write-Host "ͨ����: $percentage%"

if ($testPassed -eq $testTotal)
{
    Write-Host "���в�������ͨ��"
}
else
{
    Write-Host "��ͨ���Ĳ���������: $( $testNotPassedNames.Count )"
    Write-Host "��ͨ���Ĳ�������: $( $testNotPassedNames -join ' ' )"
}