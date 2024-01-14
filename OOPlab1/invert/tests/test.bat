@echo off

set PROGRAM_PATH="%~1"

rem Неверные аргументы командной строки
%PROGRAM_PATH% tests\ 23fg > %TEMP%\wrong-args.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\wrong-args.txt wrong-args.expect.txt
if ERRORLEVEL 1 goto err

rem Несуществующий входной файл
%PROGRAM_PATH% non-existing-file.txt > %TEMP%\wrong-file.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\wrong-file.txt wrong-file.expect.txt
if ERRORLEVEL 1 goto err

rem Неверные численные данные
%PROGRAM_PATH% wrong-data1.txt > %TEMP%\wrong-data1.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\wrong-data1.txt wrong-data.expect.txt
if ERRORLEVEL 1 goto err

rem Неверный формат входных данных
%PROGRAM_PATH% wrong-format1.txt > %TEMP%\wrong-format1.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\wrong-format1.txt wrong-format.expect.txt
if ERRORLEVEL 1 goto err

rem Неверный формат с пустыми строками
%PROGRAM_PATH% wrong-format2.txt > %TEMP%\wrong-format2.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\wrong-format2.txt wrong-format.expect.txt
if ERRORLEVEL 1 goto err

rem Вырожденная матрица (с нулевой строкой)
%PROGRAM_PATH% degenerate1.txt > %TEMP%\degenerate1.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\degenerate1.txt degenerate.expect.txt
if ERRORLEVEL 1 goto err

rem Вырожденная матрица (с линейно зависимыми первой и второй строкой)
%PROGRAM_PATH% degenerate2.txt > %TEMP%\degenerate2.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\degenerate2.txt degenerate.expect.txt
if ERRORLEVEL 1 goto err

rem Корректные данные
%PROGRAM_PATH% matrix1.txt > %TEMP%\matrix1.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\matrix1.txt matrix1.expect.txt
if ERRORLEVEL 1 goto err

%PROGRAM_PATH% matrix2.txt > %TEMP%\matrix2.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\matrix2.txt matrix2.expect.txt
if ERRORLEVEL 1 goto err

echo All tests successfully passed
exit 0

:err
echo Testing failed
exit 1
