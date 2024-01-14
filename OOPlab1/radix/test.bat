@echo off

set PROGRAM="%~1"

:: ��� ����������
echo Test 1
%PROGRAM% > nul
if not errorlevel 1 goto err
echo No arguments

:: ������� ����� ����������
echo Test 2
%PROGRAM% "" > nul
if not errorlevel 1 goto err
echo Too much arguments

:: ��������� �������
echo Test 3
%PROGRAM% "Matrix.txt" > "%TEMP%\output.txt"
if errorlevel 1 goto err
fc "Matrix-out.txt" "%TEMP%\output.txt" > nul
if errorlevel 1 goto err
echo Test 3 passed

:: ����������� �������
echo Test 4
%PROGRAM%  > "%TEMP%\output.txt"
if not errorlevel 1 goto err
fc "MatrixDetNull-out.txt" "%TEMP%\output.txt" > nul
if errorlevel 1 goto err
echo Test 4 passed

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1echo off