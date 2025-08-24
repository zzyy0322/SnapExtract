@echo off

echo Begin Build ui_mainwindow.h

cd ../SEQt

set OutputPath=D:\Project\SnapExtract\SEQt

set uicExePath=E:\Qt\6.9.1\msvc2022_64\bin\uic.exe
set mocExePath=E:\Qt\6.9.1\msvc2022_64\bin\moc.exe

set uiFilePath=D:\Project\SnapExtract\SEQt\mainwindow.ui
set mocFilePath=D:\Project\SnapExtract\SEQt\MyQtWindow.h

echo ....
"%uicExePath%" "%uiFilePath%" -o "%OutputPath%\ui_mainwindow.h"
echo Success Build ui_mainwindow.h


set pchPath=D:\Project\SnapExtract\SnapExtract
echo ....
rem "%mocExePath%" "%mocFilePath%" -include "%pchPath%\pch.h" -o "%OutputPath%\moc_MyQtWindow.cpp"
echo Success Build moc_MyQtWindow.cpp

pause