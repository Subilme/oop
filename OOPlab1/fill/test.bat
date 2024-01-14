@echo off
g++ fill.cpp -o fill.exe

echo simple correct input, expected correct coloring
fill.exe simple_correct_input.txt test1_output.txt
fc test1_output.txt expected_test1_output.txt
echo ------------------------------------------------------------------------

echo input with no starting points, expected no changes
fill.exe no_starting_point_input.txt test2_output.txt
fc test2_output.txt expected_test2_output.txt
echo ------------------------------------------------------------------------

echo empty input, expected no changes
fill.exe empty_input.txt test3_output.txt
fc test3_output.txt expected_test3_output.txt
echo ------------------------------------------------------------------------

echo input with broken border, expected filling outside that border
fill.exe broken_border_input.txt test4_output.txt
fc test4_output.txt expected_test4_output.txt
echo ------------------------------------------------------------------------

echo wrong number of parameters, expected "Wrong command line arguments"
fill.exe simple_correct_input.txt
echo ------------------------------------------------------------------------

echo not existing input file, expected "Error on parsing input file"
fill.exe not_existing_input.txt test5_output.txt
echo ------------------------------------------------------------------------