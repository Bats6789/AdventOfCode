@echo off

if "%1"=="" (
	echo ERROR: Enter a day
	exit /B 1
)

if exist Day%1 (
	echo ERROR: Specify a day that does not exist already
	exit /B 1
)

REM Setup folder
mkdir Day%1

REM Copy files
copy CMakeLists.txt Day%1
copy Part1.c Day%1
copy Part1.c Day%1\Part2.c
copy ..\python\Day%1\*.txt Day%1

REM setup build
cd Day%1
mkdir build
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug -G"Unix Makefiles"

copy build\compile_commands.json .

exit /B 0
