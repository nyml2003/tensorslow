# ����·���Ϳ�ִ���ļ�
$buildDir = "./release"
$testDir = "./test/integration"
$frontendExe = Join-Path -Path $buildDir -ChildPath "torchlight_frontend.exe"
$backendExe = Join-Path -Path $buildDir -ChildPath "torchlight_backend.exe"

# ��ȡԴ�����ļ�·��
$sourceCode = "./test/dev/dev.py"

# ��ʾԴ��������
Write-Host "���ڶ�ȡԴ����..."
Get-Content -Path $sourceCode

# ���뵽�ֽ���
Write-Host "���ڱ��뵽�ֽ���..."
$frontendCommand = @($frontendExe, "--file=$sourceCode")
Start-Process -FilePath $frontendCommand[0] -ArgumentList $frontendCommand[1] -Wait

# ִ���ֽ��루�滻�ļ���չ��Ϊ.pyc��
$backendFile = $sourceCode -replace '\.py$', '.pyc'
Write-Host "������ɣ��ֽ����ļ�Ϊ��$backendFile"
#Write-Host "���ڶ�ȡ��ִ���ֽ���..."
#
#$backendCommand = @($backendExe, "--file=$backendFile")
#& $backendCommand[0] $backendCommand[1]

