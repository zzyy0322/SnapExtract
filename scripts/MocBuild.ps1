param(
    [string]$mocExePath = "E:\Qt\6.9.1\msvc2022_64\bin\moc.exe",
    [string]$sourceFilePath = "D:\Project\SnapExtract\SEQtMoct\TempFile",
    [string]$outputFilePath = "D:\Project\SnapExtract\SEQtMoc\TempFile"
)

Write-Host "MOC Executable Path: $mocExePath"
Write-Host "Source File Path: $sourceFilePath"
Write-Host "Output File Path: $outputFilePath"

Get-ChildItem -Path $sourceFilePath -Filter *.h | ForEach-Object {
    $filename = $_.BaseName
    $inputFile = $_.FullName
    $outputFile = Join-Path $outputFilePath ("moc_$filename.cpp")
    Write-Host "Processing file: $inputFile"
    & $mocExePath $inputFile -o $outputFile
    # 读取moc生成内容，插入pch头后写回
    $content = Get-Content $outputFile
    "#include `"pch.h`"" | Set-Content $outputFile
    $content | Add-Content $outputFile
    Write-Host "Generated: $outputFile"
}