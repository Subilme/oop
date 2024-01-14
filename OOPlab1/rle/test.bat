@echo off

set PROGRAM="%~1"

:: Без аргументов
echo Test 1
%PROGRAM% > nul
if not errorlevel 1 goto err
echo No arguments

:: Мало аргументов
echo Test 2
%PROGRAM% "pack" "input.txt" > nul
if not errorlevel 1 goto err
echo Not enough arguments

:: Много аргументов
echo Test 3
%PROGRAM% "pack" "input.txt" "output.txt" "gg" > nul
if not errorlevel 1 goto err
echo Too much arguments

:: Несуществующий файл
echo Test 4
%PROGRAM% "pack" "input.txt" "output.txt" > nul
if not errorlevel 1 goto err
echo No such file

::Некорректный режим
echo Test 5
%PROGRAM% "p" "input.txt" "output.txt" > nul
if not errorlevel 1 goto err
echo "Incorrect mode"

echo Test 6
%PROGRAM% "pack" "Test1.txt" "%TEMP%\output.txt" > nul
if errorlevel 1 goto err
fc /B "Test1-out.txt" "%TEMP%\output.txt" > nul
if errorlevel 1 goto err
echo Test 6 passed

echo Test 7
%PROGRAM% "unpack" "Test1-out.txt" "%TEMP%\output.txt" > nul
if errorlevel 1 goto err
fc /B "Test1.txt" "%TEMP%\output.txt" > nul
if errorlevel 1 goto err
echo Test 7 passed

echo Test 8
%PROGRAM% "unpack" "Test2.txt" "%TEMP%\output.txt" > nul
if errorlevel 1 goto err
fc /B "Test2-out.txt" "%TEMP%\output.txt" > nul
if errorlevel 1 goto err
echo Test 8 passed

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1