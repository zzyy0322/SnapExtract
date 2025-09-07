@echo on
@echo off

setlocal enabledelayedexpansion
set ERRORLEVEL=0

set OutputPath=D:\Project\SnapExtract\SEQtMoc
set mocExePath=E:\Qt\6.9.1\msvc2022_64\bin\moc.exe
set HeaderDir=D:\Project\SnapExtract\SEQtMoc
set FileExt=*.h
set PCHPath=D:\Project\SnapExtract\SnapExtract\pch.h

echo ==============================================
echo                MOC�ļ����ɹ���
echo           ���Զ����pch.h���ã�
echo ==============================================
echo [������Ϣ]
echo ���Ŀ¼:    "%OutputPath%"
echo MOC����·��: "%mocExePath%"
echo ͷ�ļ�Ŀ¼:  "%HeaderDir%"
echo Ԥ����ͷ·��: "%PCHPath%"
echo �����ļ�����: %FileExt%
echo ==============================================
echo.

if not exist "%mocExePath%" (
    echo [����] δ�ҵ�moc.exe��"%mocExePath%"
    pause
    exit /b 1
)

if not exist "%HeaderDir%" (
    echo [����] ͷ�ļ�Ŀ¼�����ڣ�"%HeaderDir%"
    pause
    exit /b 1
)

if not exist "%PCHPath%" (
    echo [����] pch.h�ļ������ڣ�"%PCHPath%"
    pause
    exit /b 1
)

echo [��ʼ����] ����ɨ�貢����ͷ�ļ�...
echo ----------------------------------------------

pushd "%OutputPath%" || (
    echo [����] �޷��л������Ŀ¼��"%OutputPath%"
    pause
    exit /b 1
)

rem ͳ�Ʊ���
set total=0
set success=0
set failed=0

for %%f in ("%HeaderDir%\%FileExt%") do (
    set /a total+=1
    echo [������] Դ�ļ���%%~nf%%~xf
    
    set "targetFile=moc_%%~nf.cpp"
    set "tempFile=temp_%%~nf.cpp"
    
    rem 1. ������ʱMOC�ļ����Ƴ�>nul 2>&1����ʾmoc��ԭʼ�����
    "%mocExePath%" "%%f" -o "!tempFile!"
    
    if not exist "!tempFile!" (
        echo [ʧ��] MOC����ʧ�ܣ��������ļ�
        set /a failed+=1
        echo ----------------------------------------------
        goto nextFile
    )
    
    rem 2. �ֶ����pch.h����
    echo #include "%PCHPath%" > "!targetFile!"
    type "!tempFile!" >> "!targetFile!"
    del "!tempFile!" >nul 2>&1
    
    rem 3. �����
    if exist "!targetFile!" (
        echo [�ɹ�] �����ɣ�!targetFile!�������pch.h��
        set /a success+=1
    ) else (
        echo [ʧ��] �޷�����Ŀ���ļ�
        set /a failed+=1
    )
    
    echo ----------------------------------------------
    :nextFile
)

endlocal & set total=%total% & set success=%success% & set failed=%failed%

popd

echo ==============================================
echo [������]
echo ���ļ�����%total%
echo �ɹ���%success% ��
echo ʧ�ܣ�%failed% ��
echo ==============================================
echo [���] �����ļ��������
echo ==============================================
pause

rem ȷ���ű����������ͣ����ʹǰ�����Ҳ�ܿ���
if %ERRORLEVEL% neq 0 (
    echo �ű�ִ�й����з������󣬴�����룺%ERRORLEVEL%
    pause
)
