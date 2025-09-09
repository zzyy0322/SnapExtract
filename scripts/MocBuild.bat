@echo off
setlocal enabledelayedexpansion

set mocexePath=E:\Qt\6.9.1\msvc2022_64\bin\moc.exe
set sourceFilePath=D:\Project\SnapExtract\SEQtMoc
set outputFilePath=D:\Project\SnapExtract\SnapExtract

rem 输出文件路径
echo MOC Executable Path: %mocexePath%
echo Source File Path: %sourceFilePath%
echo Output File Path: %outputFilePath%

rem 遍历源文件目录中的所有.h文件
for %%f in (%sourceFilePath%\*.h) do (
    rem 获取文件名（不含路径和扩展名）
    set filename=%%~nf
    echo Processing file: %%f
    rem 生成输出文件名
    set outputFile=%outputFilePath%\moc_%%~nf.cpp
    rem 调用moc.exe生成输出文件
    "%mocexePath%" "%%f" -o "!outputFile!"
    rem 在生成文件开头插入 #include "pch.h"
    echo #include "pch.h" > "!outputFile!.tmp"
    type "!outputFile!" >> "!outputFile!.tmp"
    move /Y "!outputFile!.tmp" "!outputFile!" >nul
    echo Generated: !outputFile!
)

endlocal
pause