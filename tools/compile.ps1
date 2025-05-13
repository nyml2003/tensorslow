# ����·���Ϳ�ִ���ļ�
$buildDir = "../release"
$testDir = "../test/integration"
$frontendExe = Join-Path -Path $buildDir -ChildPath "tensorslow_compiler.exe"
$backendExe = Join-Path -Path $buildDir -ChildPath "tensorslow_interpreter.exe"

# ��ȡԴ�����ļ�·��
# $sourceCode = "../test/ml/adaline.py"
$sourceCode = "../test/ml/iris.py"
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
Write-Host "���ڶ�ȡ��ִ���ֽ���..."

$backendCommand = @($backendExe, "--file=$backendFile")
& $backendCommand[0] $backendCommand[1]

