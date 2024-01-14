@echo off

set PROGRAM="%~1"

:: Без аргументов
echo Test 1
%PROGRAM% > nul
if not errorlevel 1 goto err
echo No arguments

:: Мало аргументов
echo Test 2
%PROGRAM% "input.txt" "output.txt" > nul
if not errorlevel 1 goto err
echo Not enough arguments

:: Много аргументов
echo Test 3
%PROGRAM% "input.txt" "output.txt" "gg" "aa" "12345" > nul
if not errorlevel 1 goto err
echo Too much arguments

:: Несуществующий файл
echo Test 4
%PROGRAM% "input.txt" "output.txt" "gg" "aa" > nul
if not errorlevel 1 goto err
echo No such file

:: Замена "i" на "x"
echo Test 5
%PROGRAM% "Test.txt" "%TEMP%\output.txt" "i" "x" > nul
if errorlevel 1 goto err
fc "Test-out.txt" "%TEMP%\output.txt" > nul
if errorlevel 1 goto err
echo Test 5 passed

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1