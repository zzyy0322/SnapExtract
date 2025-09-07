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
echo                MOC文件生成工具
echo           （自动添加pch.h引用）
echo ==============================================
echo [配置信息]
echo 输出目录:    "%OutputPath%"
echo MOC程序路径: "%mocExePath%"
echo 头文件目录:  "%HeaderDir%"
echo 预编译头路径: "%PCHPath%"
echo 处理文件类型: %FileExt%
echo ==============================================
echo.

if not exist "%mocExePath%" (
    echo [错误] 未找到moc.exe："%mocExePath%"
    pause
    exit /b 1
)

if not exist "%HeaderDir%" (
    echo [错误] 头文件目录不存在："%HeaderDir%"
    pause
    exit /b 1
)

if not exist "%PCHPath%" (
    echo [错误] pch.h文件不存在："%PCHPath%"
    pause
    exit /b 1
)

echo [开始处理] 正在扫描并处理头文件...
echo ----------------------------------------------

pushd "%OutputPath%" || (
    echo [错误] 无法切换到输出目录："%OutputPath%"
    pause
    exit /b 1
)

rem 统计变量
set total=0
set success=0
set failed=0

for %%f in ("%HeaderDir%\%FileExt%") do (
    set /a total+=1
    echo [处理中] 源文件：%%~nf%%~xf
    
    set "targetFile=moc_%%~nf.cpp"
    set "tempFile=temp_%%~nf.cpp"
    
    rem 1. 生成临时MOC文件（移除>nul 2>&1，显示moc的原始输出）
    "%mocExePath%" "%%f" -o "!tempFile!"
    
    if not exist "!tempFile!" (
        echo [失败] MOC处理失败，跳过此文件
        set /a failed+=1
        echo ----------------------------------------------
        goto nextFile
    )
    
    rem 2. 手动添加pch.h引用
    echo #include "%PCHPath%" > "!targetFile!"
    type "!tempFile!" >> "!targetFile!"
    del "!tempFile!" >nul 2>&1
    
    rem 3. 检查结果
    if exist "!targetFile!" (
        echo [成功] 已生成：!targetFile!（已添加pch.h）
        set /a success+=1
    ) else (
        echo [失败] 无法生成目标文件
        set /a failed+=1
    )
    
    echo ----------------------------------------------
    :nextFile
)

endlocal & set total=%total% & set success=%success% & set failed=%failed%

popd

echo ==============================================
echo [处理结果]
echo 总文件数：%total%
echo 成功：%success% 个
echo 失败：%failed% 个
echo ==============================================
echo [完成] 所有文件处理完毕
echo ==============================================
pause

rem 确保脚本在最后有暂停，即使前面出错也能看到
if %ERRORLEVEL% neq 0 (
    echo 脚本执行过程中发生错误，错误代码：%ERRORLEVEL%
    pause
)
