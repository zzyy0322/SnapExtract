@echo off
setlocal enabledelayedexpansion

set mocexePath=E:\Qt\6.9.1\msvc2022_64\bin\moc.exe
set sourceFilePath=D:\Project\SnapExtract\SEQtMoc
set outputFilePath=D:\Project\SnapExtract\SnapExtract

rem ����ļ�·��
echo MOC Executable Path: %mocexePath%
echo Source File Path: %sourceFilePath%
echo Output File Path: %outputFilePath%

rem ����Դ�ļ�Ŀ¼�е�����.h�ļ�
for %%f in (%sourceFilePath%\*.h) do (
    rem ��ȡ�ļ���������·������չ����
    set filename=%%~nf
    echo Processing file: %%f
    rem ��������ļ���
    set outputFile=%outputFilePath%\moc_%%~nf.cpp
    rem ����moc.exe��������ļ�
    "%mocexePath%" "%%f" -o "!outputFile!"
    rem �������ļ���ͷ���� #include "pch.h"
    echo #include "pch.h" > "!outputFile!.tmp"
    type "!outputFile!" >> "!outputFile!.tmp"
    move /Y "!outputFile!.tmp" "!outputFile!" >nul
    echo Generated: !outputFile!
)

endlocal
pause