@echo off
REM 

REM 
if not exist build (
    mkdir build
)

REM 
cd build

REM 
cmake ..

REM 
cmake --build .

REM
cd ..
